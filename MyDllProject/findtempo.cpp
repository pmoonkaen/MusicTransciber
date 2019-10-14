#include "errorval.h"
#include "findtempo.h"

#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>

long long TEMPO::tmp[100001][2];

double TEMPO::gettempo(const std::vector<int>& myinterval){
    memset(TEMPO::tmp,0,sizeof(TEMPO::tmp));
    int maxinterval=0, num=0;
    double tempo=120.0;
    for(int i=0; i<myinterval.size(); i++){
        int val;
        if(i==0){
            val=myinterval[i];
        }
        else{
            val=myinterval[i]-myinterval[i-1];
        }
        TEMPO::tmp[val/lofint][0]++;
        TEMPO::tmp[val/lofint][1]+=val;
        maxinterval=std::max(maxinterval,val/lofint);
    }
    for(int i=0; i<=maxinterval; i++){
        int current=0;
        long long sum=0;
        for(int j=-1; j<=1; j++){
            current+=TEMPO::tmp[i+j][0];
            sum+=TEMPO::tmp[i+j][1];
        }
        if(num<current){
            num=current;
            tempo=(double)sum/current;
        }
    }
    while(tempo > maxtempo){
        tempo/=2;
    }
    while(tempo < mintempo){ //prefer max bpm
        tempo*=2;
    }
    return tempo;
}

