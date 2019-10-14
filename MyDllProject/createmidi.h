#ifndef CREATEMIDI
#define CREATEMIDI

#include<vector>
#define piv std::pair<int,std::vector<int> >

class CMIDI{
private:
    static int dev(double x, double y);
    static std::vector<unsigned char> outp;
    static void blanknote(int len);
public:
//    static void midiOut(char* path, const std::vector<piv>& result, const double tempo);
    static void midiOut(char* path, const std::vector<piv>& result, const double tempo);
};

#endif

