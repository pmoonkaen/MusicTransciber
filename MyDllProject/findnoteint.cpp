#include "errorval.h"
#include "findnoteint.h"
#include "notedata.h"

#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<list>
#include<algorithm>

#define pdd std::pair<double,double>
#define lpddit std::list<pdd>::iterator

std::list<pdd> FNOTEINT::freq;
pdd FNOTEINT::checknote[12];
void FNOTEINT::clearall(){
    FNOTEINT::freq.clear();
    memset(FNOTEINT::checknote,0,sizeof(FNOTEINT::checknote));
}
bool FNOTEINT::isequal(double notefreq, double freqtest){
    if(notefreq<=freqtest && freqtest<=pow(2,1.0/24.0)*notefreq)
        return true;
    else if(notefreq>=freqtest && freqtest>=pow(2,-1.0/24.0)*notefreq)
        return true;
    return false;
}
pdd FNOTEINT::deleteHarmonic(double notefreq){
    pdd mAmp=pdd(0.0,0.0);
    for(lpddit it=freq.begin(); it!=freq.end(); it++){
        if(isequal(round(it->first/notefreq)*notefreq,it->first)){
            mAmp=std::max(mAmp,pdd(it->second,it->first));
            lpddit it2=it;it--;
            FNOTEINT::freq.erase(it2);
        }
    }
    return mAmp;
}
int FNOTEINT::searchNote(double notefreq){
    int l=4, r=87, mid;
    while(l<r){
        mid=(l+r)/2;
        if(notefreq<=notelist.numNoteToFreq(mid))r=mid;
        else l=mid+1;
    }
    if(l==4 || notelist.numNoteToFreq(l)-notefreq<notefreq-notelist.numNoteToFreq(l-1))
        return l;
    else
        return l-1;
}

//  peaks = after findpeaks
bool FNOTEINT::getNotes(std::vector<pdd>& peaks, std::vector<pdd>& output){
    if(peaks.empty())
        return false;
    output.clear();
    FNOTEINT::clearall();
    int i, j;
    for(std::vector<pdd>::iterator it=peaks.begin(); it!=peaks.end(); it++){
        if(it->first > maxX)
            continue;
        FNOTEINT::freq.push_back(pdd(it->first,it->second));
    }
    lpddit it=FNOTEINT::freq.begin();
    while(it->first<notelist.numNoteToFreq(4)){
        it->first=notelist.numNoteToFreq(4);
        j++;
    }
    for(i=4; i<88; i++){
        while(it!=FNOTEINT::freq.end() && isequal(it->first,notelist.numNoteToFreq(i))){
            it->first=notelist.numNoteToFreq(i);
            it++;
        }
    }
    while(it!=FNOTEINT::freq.end()){
        it->first=notelist.numNoteToFreq(87);
        it++;
    }
    while(!freq.empty()){
        pdd amp=pdd(freq.front().second,freq.front().first);
        int numnote=searchNote(amp.second);
        freq.pop_front();
        amp=std::max(amp,deleteHarmonic(amp.second));
        checknote[(numnote-4)%12]=std::max(checknote[(numnote-4)%12],amp);
    }
    for(i=0; i<12; i++){
        output.push_back(checknote[i]);
    }
    FNOTEINT::clearall();
    return true;
}



