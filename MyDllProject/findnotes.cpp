#include "errorval.h"
#include "findnotes.h"
#include "notedata.h"

#include<cstdio>
#include<cstring>
#include<math.h>
#include<vector>
#include<algorithm>

#define pdd std::pair<double,double>
#define pid std::pair<int,double>

std::vector<FREQ> FNOTE::freq;
int FNOTE::checknote[100];
void FNOTE::clearall(){
    FNOTE::freq.clear();
    memset(FNOTE::checknote,0,sizeof(FNOTE::checknote));
}
bool FNOTE::isequal(double notefreq, double freqtest){
    if(notefreq<=freqtest && freqtest<=pow(2,1.0/24.0)*notefreq)
        return true;
    else if(notefreq>=freqtest && freqtest>=pow(2,-1.0/24.0)*notefreq)
        return true;
    return false;
}
void FNOTE::deleteHarmonic(double notefreq){
    for(int i=FNOTE::freq.size()-1; i>=0; i--){
        if(isequal(round(notelist.numNoteToFreq(FNOTE::freq[i].numNote)/notefreq)*notefreq,notelist.numNoteToFreq(FNOTE::freq[i].numNote))){
            FNOTE::freq.erase(FNOTE::freq.begin()+i);
        }
        else if(notelist.numNoteToFreq(FNOTE::freq[i].numNote)<notefreq)
            break;
    }
}
void FNOTE::findmax(){
    int maxAmp=0;
    for(int i=1; i<FNOTE::freq.size(); i++){
        if(FNOTE::freq[maxAmp].y<FNOTE::freq[i].y)
            maxAmp=i;
    }
//    printf("%d = %lf %lf --- %d %lf\n", maxAmp, freq[maxAmp].x, freq[maxAmp].y, freq[maxAmp].numNote, notelist.numNoteToFreq(freq[maxAmp].numNote));
    FNOTE::checknote[FNOTE::freq[maxAmp].numNote]=1;
    deleteHarmonic(notelist.numNoteToFreq(FNOTE::freq[maxAmp].numNote));
}

//  peaks = after findpeaks
bool FNOTE::getNotes(std::vector<pdd>& peaks, std::vector<int>& output){
    if(peaks.empty())
        return false;
    output.clear();
    FNOTE::clearall();
    int i, j;
    for(std::vector<pdd>::iterator it=peaks.begin(); it!=peaks.end(); it++){
        if(it->first > maxX)
            continue;
        FNOTE::freq.push_back(FREQ(0,it->first,it->second));
    }
    j=0;
    while(FNOTE::freq[j].x<notelist.numNoteToFreq(4)){
        FNOTE::freq[j].numNote=4;
        j++;
    }
    for(i=4; i<88; i++){
        while(isequal(FNOTE::freq[j].x,notelist.numNoteToFreq(i))){
            FNOTE::freq[j].numNote=i;
            j++;
        }
    }
    while(j<FNOTE::freq.size()){
        FNOTE::freq[j].numNote=87;
        j++;
    }
    while(!FNOTE::freq.empty()){
        findmax();
    }
    for(i=4; i<88; i++){
        if(FNOTE::checknote[i]==0)continue;
        if(FNOTE::checknote[i]==2 && FNOTE::checknote[i+12]==1){
            FNOTE::checknote[i]=1;
            FNOTE::checknote[i+12]=0;
        }
        if(FNOTE::checknote[i]==1){
            output.push_back(i);
            if(FNOTE::checknote[i+12]==1)
                FNOTE::checknote[i+12]=0;
        }
    }
    FNOTE::clearall();
    return true;
}


