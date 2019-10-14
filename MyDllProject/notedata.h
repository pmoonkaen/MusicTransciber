#ifndef _NOTEDATA_H_
#define _NOTEDATA_H_

#include<math.h>
#include<cstring>
#include<cstdio>

class notedata{
public:
    char name[12][3];
    double freq[12][7];
    double numNoteToFreq(int num){
        return freq[(num-4)%12][(num-4)/12];
    }
    notedata(){
        for(int i=4;i<88;i++){
            freq[(i-4)%12][(i-4)/12]=pow(2.0,(i-49.0)/12.0)*440.0;
        }
        strcpy(name[0],"C");
        strcpy(name[1],"C#");
        strcpy(name[2],"D");
        strcpy(name[3],"D#");
        strcpy(name[4],"E");
        strcpy(name[5],"F");
        strcpy(name[6],"F#");
        strcpy(name[7],"G");
        strcpy(name[8],"G#");
        strcpy(name[9],"A");
        strcpy(name[10],"A#");
        strcpy(name[11],"B");
    }
};

extern notedata notelist;

#endif

