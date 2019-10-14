#include "interval.h"
#include "errorval.h"
#include "dofft.h"
#include "findpeaks.h"
#include "findnoteint.h"

#include<cstdio>
#include<math.h>
#include<algorithm>
#include<deque>
#include<vector>

#define pdd std::pair<double,double>

std::vector<pdd> ITV::prevfreq, ITV::curfreq;
std::vector<pdd> ITV::afterfft, ITV::afterpeak;

//  soundinput - array of ITV::sound wave (amplitude/sample)
//  output - array of output (start time of each length)
bool ITV::isHarmonic(double notefreq, double freqtest){
    double freq=round(freqtest/notefreq)*notefreq;
    double right=((pow(2,1.0/24.0)*freq-freq))+freq;
    double left=freq-((freq-(pow(2,-1.0/24.0)*freq)));
    if(freq<=freqtest && freqtest<=right)
        return true;
    else if(freq>=freqtest && freqtest>=left)
        return true;
    return false;
}
bool ITV::compare(int percentNewnote){
    int maxCur=0;
    for(int i=0; i<12; i++){
        if(ITV::curfreq[i].first > ITV::curfreq[maxCur].first){
            maxCur=i;
        }
    }
    for(int i=0; i<12; i++){
        if(curfreq[i].first==0.0)
            continue;
        bool isnew=true;
        double maxAmp=0.0;
        for(int j=0; j<12; j++){
            if(prevfreq[j].first==0.0)
                continue;
            if(i==j || isHarmonic(prevfreq[j].second,curfreq[i].second) || isHarmonic(curfreq[i].second,prevfreq[j].second)){
                isnew=false;
                maxAmp=std::max(maxAmp,ITV::prevfreq[j].first);
            }
            if(fabs(curfreq[i].second-prevfreq[j].second)<=ffterror && curfreq[i].first<prevfreq[j].first && curfreq[i].first>=prevfreq[j].first*lowerpercent/100){
                isnew=false;
                maxAmp=std::max(maxAmp,ITV::prevfreq[j].first);
            }
        }
        if(isnew && curfreq[i].first >= curfreq[maxCur].first*percentNewnote/100){
            return false;
        }
        else if(!isnew && maxAmp < ITV::curfreq[i].first*maxpercent/100){
            return false;
        }
    }
    return true;
}
void ITV::getInterval(std::vector<short>& sound, std::vector<int>& output, const int smprate){
    output.clear();
    int i, initsmp=0;
    for(i=1; i<=length; i++){
        if(sound[initsmp]<sound[i])
            initsmp=i;
    }
    output.push_back(initsmp);
    i=initsmp;
    while(i+numsmp-1<sound.size()){
        ITV::curfreq.clear();
        double minAmp=runfft(i,i+numsmp-1,sound,ITV::afterfft,smprate,50.0);
        if(minAmp==-1.0)
            continue;
        getPeaks(ITV::afterfft,ITV::afterpeak,minAmp);
        FNOTEINT::getNotes(ITV::afterpeak,ITV::curfreq);
        if(i==initsmp || ITV::compare(75)==true){
            prevfreq.clear();
            minAmp=runfft(i,i+numsmp-1,sound,ITV::afterfft,smprate,30.0);
            getPeaks(ITV::afterfft,ITV::afterpeak,minAmp);
            FNOTEINT::getNotes(ITV::afterpeak,ITV::prevfreq);
            i+=numsmp;
            continue;
        }
        /*binary search*/
        int st=i, en=i+numsmp-1, mid;
        while(st<en){
            mid=((st+en)/2);
            ITV::curfreq.clear();
            double minAmp=runfft(std::max(i-numsmp,output.back()),mid,sound,ITV::afterfft,smprate,50.0);
            if(minAmp==-1.0){
                en=mid;
                continue;
            }
            getPeaks(ITV::afterfft,ITV::afterpeak,minAmp);
            FNOTEINT::getNotes(ITV::afterpeak,ITV::curfreq);
            if(compare(70)==true){
                st=mid+1;
            }
            else{
                en=mid;
            }
        }
        output.push_back(++st);
        initsmp=st;
        i=st;
    }
}


