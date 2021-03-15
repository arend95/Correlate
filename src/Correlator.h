#include <iostream>
using namespace std;

#include <fstream>
#include <iomanip>
#include <time.h>

#include <vector>
#include <cmath>
#include <numeric> 
#include <cstdlib>

#ifndef __Correlator_h
#define __Correlator_h

class Correlator {
public:
    int N;
    int rmax;
    
    vector<float> XD, YD;
    vector<float> XR, YR;
    vector<float> DD, RR, DR;
    
    vector<float> Chi1, Chi2;
    
    Correlator();
    
    void ReadXY();
    void GenerateRR();
    
    void Corr12(vector<float> &X1, vector<float> &Y1, vector<float> &X2, vector<float> &Y2, vector<float> &XX);

    void CalcChi();
    
    void WriteData();
};

#endif
