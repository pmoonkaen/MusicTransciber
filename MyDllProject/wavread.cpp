#include "wavread.h"

#include<stdio.h>
#include<string.h>
#include<vector>
#include<fstream>

int openWave(char *wavpath, std::vector<short>& wavdata) {
    std::ifstream fin;
    fin.open(wavpath, std::ios::in | std::ios::binary);
    if(!fin.is_open()){
        printf("Error in opening wave file\n");
        return -1;
    }
    char chunkID[5], format[5], subChunk1ID[5], subChunk2ID[5], trash;
    short compressCode, channel, blockAlign, bitPerSamp;
    int chunkSize, subChunk1Size, subChunk2Size, sampleRate, byteRate;

    /*file chunk*/
    fin.read((char*)chunkID,sizeof(char)*4);chunkID[4]='\0';
    fin.read((char*)&chunkSize,sizeof(int));
    fin.read((char*)format,sizeof(char)*4);format[4]='\0';
    if(strcmp(chunkID,"RIFF")!=0 || strcmp(format,"WAVE")!=0){
        printf("Wrong format WAVE file\n");
        return -1;
    }

    /*fmt sub chunk*/
    fin.read((char*)subChunk1ID,sizeof(char)*4);subChunk1ID[4]='\0';
    fin.read((char*)&subChunk1Size,sizeof(int));
    fin.read((char*)&compressCode,sizeof(short));
    fin.read((char*)&channel,sizeof(short));
    fin.read((char*)&sampleRate,sizeof(int));
    fin.read((char*)&byteRate,sizeof(int));
    fin.read((char*)&blockAlign,sizeof(short));
    fin.read((char*)&bitPerSamp,sizeof(short));
    //extra
    for(int i=0; i<subChunk1Size-16; i++){
        fin.read((char*)&trash,sizeof(char));
    }

    /*data sub chunk*/
    while(true){
        fin.read((char*)subChunk2ID,sizeof(char)*4);subChunk2ID[4]='\0';
        fin.read((char*)&subChunk2Size,sizeof(int));
        if(strcmp(subChunk2ID,"data")==0)
            break;
        for(int i=0; i<subChunk2Size; i++){
            fin.read((char*)&trash,sizeof(char));
        }
    }

    wavdata.clear();
    for(int i=0; i<subChunk2Size/2; i++){
        short amp;
        fin.read((char*)&amp,sizeof(short));
        wavdata.push_back(amp);
        //if multichannel
        for(int j=0; j<channel-1; i++, j++){
            fin.read((char*)&amp,sizeof(short));
        }
    }
    fin.close();
    return sampleRate;
}


