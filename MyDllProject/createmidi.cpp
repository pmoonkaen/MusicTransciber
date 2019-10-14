#include "createmidi.h"

#include<cstdio>
#include<vector>
#include<iostream>
#include<fstream>
#define piv std::pair<int,std::vector<int> >

std::vector<unsigned char> CMIDI::outp;

int CMIDI::dev(double x, double y){
    int t=(int)(x/y);
    return t+((x/y-(double)t >= 0.5)?1:0);
}
void CMIDI::blanknote(int len){
    unsigned char trash[100];
    int tl=0;
    while(len>0){
        trash[tl++]=len%127+128;
        len/=127;
    }
    trash[0]-=128;
    outp.push_back(0);
    outp.push_back(144); //90
    outp.push_back(45);
    outp.push_back(0);
    for(--tl; tl>=0; tl--){
        outp.push_back(trash[tl]);
    }
    outp.push_back(128); //80
    outp.push_back(45);
    outp.push_back(0);
}
//void CMIDI::midiOut(char* path, const std::vector<piv>& result, const double tempo){
void CMIDI::midiOut(char* path, const std::vector<piv>& result, const double tempo){
    puts(path);
    std::ofstream midiout;
//    midiout.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    midiout.open(path, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!midiout.is_open()){
        printf("Error in opening midiOutput file\n");
        return ;
    }

    unsigned char trash[100]={77,84,104,100,  0,0,0,6,  0,0,  0,1,  0,96,  77,84,114,107};
    int tl=18;
    midiout.write((char*)trash,tl);

    //put size later
    outp.push_back(0);
    outp.push_back(0);
    outp.push_back(0);
    outp.push_back(0);

    //set tempo
    int tpermsec=CMIDI::dev(tempo*1000000,44100);
    outp.push_back(0);  //00
    outp.push_back(255); //FF
    outp.push_back(81); //51
    outp.push_back(3); //03
    outp.push_back(tpermsec/65536);
    outp.push_back((tpermsec%65536)/256);
    outp.push_back(tpermsec%256);

    //set time signature *4/4
    outp.push_back(0); //00
    outp.push_back(255); //FF
    outp.push_back(88); //58
    outp.push_back(4); //04
    outp.push_back(4);
    outp.push_back(2);
    outp.push_back(24);
    outp.push_back(8);

    //set intrument *piano
    outp.push_back(0);
    outp.push_back(192); //C0
    outp.push_back(0); //00=piano

    //start
    int len=0;
//    len=CMIDI::dev(96.0*result[0].first,tempo);
        //len to delta time
//            tl=0;
//            while(len>0){
//                trash[tl++]=len%127+128;
//                len/=127;
//            }
//            trash[0]-=128;
//        for(--tl; tl>=0; tl--){
//            outp.push_back(trash[tl]);
//        }
//        len=0;
    for(int i=0; i<result.size(); i++){
        if(i==result.size()-1)len=384;
        else len+=CMIDI::dev(96.0*(result[i+1].first-result[i].first),tempo);
        if(len<12)continue;
        if(result[i].second.empty()){
            blanknote(len);
            len=0;
            continue;
        }
        //note on
        for(int j=0; j<result[i].second.size(); j++){
            //if(!(i==0 && j==0))
                outp.push_back(0);
            if(j==0)outp.push_back(144); //90
            outp.push_back(result[i].second[j]+20); //C1=24
            int vol=127;
            if(result[i].second[j]<=34)vol=83;
            outp.push_back(vol); //7F
        }

        //note off
        //len to delta time
            tl=0;
            while(len>0){
                trash[tl++]=len%127+128;
                len/=127;
            }
            trash[0]-=128;
        for(--tl; tl>=0; tl--){
            outp.push_back(trash[tl]);
        }
        for(int j=0; j<result[i].second.size(); j++){
            if(j>0) outp.push_back(0);
            if(j==0)outp.push_back(128); //80
            outp.push_back(result[i].second[j]+20); //C1=24
            int vol=127;
            if(result[i].second[j]<=34)vol=83;
            outp.push_back(vol); //7F
        }

    }
//    //blank note
//    blanknote(192);

    //end
    outp.push_back(0);
    outp.push_back(255);
    outp.push_back(47);
    outp.push_back(0);

    //set chunk size
    int siz=outp.size()-4;
    for(int i=3; i>=0 && siz>0; i--,siz/=256){
        outp[i]=siz%256;
    }

    for(std::vector<unsigned char>::iterator it=outp.begin(); it!=outp.end(); it++){
        midiout.write((char*)&(*it),1);
    }
    midiout.close();
}

