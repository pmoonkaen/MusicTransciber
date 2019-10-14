#ifndef _FINDNOTEINT_H_
#define _FINDNOTEINT_H_

#include "notedata.h"
#include<vector>
#include<list>
#define pdd std::pair<double,double>

class FNOTEINT{
private:
    static void clearall();
    static bool isequal(double notefreq, double freqtest);
    static pdd deleteHarmonic(double notefreq);
    static int searchNote(double notefreq);
    static std::list<pdd> freq;
    static pdd checknote[12];
public:
    static bool getNotes(std::vector<pdd>& peaks, std::vector<pdd>& output);
};

#endif

