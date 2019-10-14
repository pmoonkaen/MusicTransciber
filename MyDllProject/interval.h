#ifndef INTERVAL
#define INTERVAL

#include<vector>
#include<deque>
#define pdd std::pair<double,double>
#define pid std::pair<int,double>

class ITV{
private:
    static bool compare(int percentNewnote);
    static bool isHarmonic(double notefreq, double freqtest);
public:
    static std::vector<pdd> prevfreq, curfreq;
    static std::vector<pdd> afterfft, afterpeak;
    static void getInterval(std::vector<short>& sound, std::vector<int>& output, const int smprate);
};

#endif



