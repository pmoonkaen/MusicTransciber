#ifndef FINDTEMPO
#define FINDTEMPO

#include<vector>

class TEMPO{
private:
    static long long tmp[100001][2];
public:
    static double gettempo(const std::vector<int>& myinterval);
};

#endif

