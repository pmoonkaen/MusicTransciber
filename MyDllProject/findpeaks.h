#ifndef FINDPEAKS
#define FINDPEAKS

#include<vector>
#define ptt std::pair<double,double>

bool getPeaks(const std::vector<ptt>& fftarray, std::vector<ptt>& output, double minAmp);

#endif

