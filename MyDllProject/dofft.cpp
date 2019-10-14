#include "dofft.h"
#include "fft.h"
#include "complex.h"
#include "errorval.h"

#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<vector>
#define pdd std::pair<double,double>
#define pow215 32768.0 //2^15

double runfft(const int startint, const int endint, const std::vector<short> &sound, std::vector<pdd> &output, const int smprate, double amppercent){
    output.clear();
    //do fft
    int i;
    int log2len=1<<(32-__builtin_clz(endint-startint+1));
    complex *wavform=(complex*)malloc(sizeof(complex)*log2len);
    for(i=0; i<=endint-startint; i++){
        wavform[i]=complex(sound[i+startint]/pow215);
    }
    for(; i<log2len; i++){
        wavform[i]=complex(0);
    }

    if(!CFFT::Forward(wavform,log2len)){
        return -1.0;
    }
    //convert to (x,y) (output)
    double time=(double)log2len/smprate, minAmp=-1.0;
    for(i=0; i<log2len/8 ; i++){
        output.push_back( pdd(i/time, sqrt(wavform[i].norm()) ) );
        minAmp=std::max(minAmp,output.back().second);
    }
    free(wavform);
    return minAmp*amppercent/100;
}

