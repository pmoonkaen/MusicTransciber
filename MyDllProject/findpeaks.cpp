#include<cstdio>
#include<math.h>
#include<algorithm>
#include<vector>

#define type1 double
#define ptt std::pair<type1,type1>

bool getPeaks(const std::vector<ptt>& fftarray, std::vector<ptt>& output, double minAmp){
    if(fftarray.empty())
        return false;
    output.clear();
    int i,j ;
    for(i=1; i<fftarray.size(); i++){
        double maxnear;
        if(i==0)
            maxnear=fftarray[i+1].second;
        else if(i==fftarray.size()-1)
            maxnear=fftarray[i-1].second;
        else
            maxnear=std::max(fftarray[i+1].second,fftarray[i-1].second);

        if(fftarray[i].second < maxnear || fftarray[i].second < minAmp)
            continue;
        bool ismax=true;
        double left=pow(2,-1.0/30.0)*fftarray[i].first;
        double right=pow(2,1.0/30.0)*fftarray[i].first;
        for(j=i-1; j>=0 && fftarray[j].first >= left; j--){
            if(fftarray[i].second < fftarray[j].second){
                ismax=0;
                break;
            }
        }
        for(j=i+1; j<=fftarray.size() && fftarray[j].first <= right; j++){
            if(fftarray[i].second < fftarray[j].second){
                ismax=0;
                break;
            }
        }
        if(ismax==true){
            output.push_back(fftarray[i]);
        }
    }
    return true;
}

