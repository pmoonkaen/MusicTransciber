#ifndef _FINDNOTES_H_
#define _FINDNOTES_H_

#include<vector>
#define pdd std::pair<double,double>
#define pid std::pair<int,double>

struct FREQ{
    int numNote;
    double x, y;
    FREQ(){}
    FREQ(int nn, double xx, double yy){
        numNote=nn;x=xx;y=yy;
    }
};
class FNOTE{
private:
    static void clearall();
    static double finderrorx(double notefreq);
    static bool isequal(double notefreq, double freqtest);
    static void deleteHarmonic(double notefreq);
    static void findmax();
    static std::vector<FREQ> freq;
    static int checknote[100];
public:
    static bool getNotes(std::vector<pdd>& peaks, std::vector<int>& output);
};

#endif

