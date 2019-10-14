#ifndef _MAIN_H_
#define _MAIN_H_

#if defined DLL_EXPORT
#define MAIN_API __declspec(dllexport)
#else
#define MAIN_API __declspec(dllimport)
#endif

double dofft(int startint, int endint, int smprate);
extern "C"{
    MAIN_API bool wavToMidi(char* wavpath, char* midipath);
}
#endif
