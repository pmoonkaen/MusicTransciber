#ifndef _DOFFT_H_
#define _DOFFT_H_

#include<vector>
#define pdd std::pair<double,double>

double runfft(const int startint, const int endint, const std::vector<short> &sound, std::vector<pdd> &output, const int smprate, double amppercent);

#endif

