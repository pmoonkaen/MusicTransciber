#include "main.h"

#include "errorval.h"
#include "notedata.h"
#include "wavread.h"
#include "interval.h"
#include "dofft.h"
#include "findpeaks.h"
#include "findnotes.h"
#include "findtempo.h"
#include "createmidi.h"

#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<vector>
#include<math.h>

#define DLL_EXPORT

#define pdd std::pair<double,double>
#define piv std::pair<int,std::vector<int> >
#define e215 32768.0 //2^15

std::vector<short> sound;
std::vector<int> myinterval, notearray;
std::vector<pdd> afterfft, afterpeak;
std::vector<piv> result;

double dofft(int startint, int endint, int smprate){
    afterfft.clear();
    int disfromstart;
    //setting interval data
    disfromstart = (endint-startint)/10;
    if(disfromstart < 500)
        disfromstart = (endint-startint)/5;
    if(disfromstart > maxdis){
        disfromstart = maxdis;
    }
    startint = startint + disfromstart;
    endint = endint - disfromstart;
    if(endint-startint > maxlength){
        endint = startint + maxlength;
    }

    //do fft
    return runfft(startint,endint,sound,afterfft,smprate,50.0);
}

extern "C"{
    __declspec(dllexport) bool wavToMidi(char* wavpath, char* midipath){
        int i, smprate;
        double tempo;

        /*check midiOut*/
        FILE* midiout=fopen(midipath, "w");
        if(midiout==NULL){
            printf("Error in opening midiOutput file.\n");
            return false;
        }
        fclose(midiout);

        /*getsound*/
        smprate=openWave(wavpath,sound);
        if(smprate==-1)
            return false;

        /*interval determining*/
        ITV::getInterval(sound,myinterval,smprate);
        myinterval.push_back(sound.size()); //add end val
        tempo=TEMPO::gettempo(myinterval);

        /*note analyzing*/
        for(i=0; i<myinterval.size()-1; i++){
            double minAmp=dofft(myinterval[i],myinterval[i+1],smprate);
            if(minAmp==-1.0)
                continue;
            getPeaks(afterfft,afterpeak,minAmp);
            FNOTE::getNotes(afterpeak,notearray);
            result.push_back(piv(myinterval[i],notearray));
        }

        CMIDI::midiOut(midipath,result,tempo);
        FILE* fout=fopen("mididata.txt","w");

        if(fout==NULL){
            printf("Error in opening output.txt\n");
            return false;
        }
        for(std::vector<piv>::iterator it=result.begin(), it3; it!=result.end(); it++){
            it3=it;it3++;
            if(it3==result.end())break;
            fprintf(fout,"%d\t%d\t%d\t", it->first, it3->first, it->second.size());
            for(std::vector<int>::iterator it2=it->second.begin(); it2!=it->second.end(); it2++){
                fprintf(fout,"%d\t", *it2);
            }
            fprintf(fout,"\n");
        }
        fclose(fout);
        return true;
    }
}
