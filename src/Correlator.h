#include <iostream>
using namespace std;

#include <fstream>
#include <iomanip>

#include <vector>
#include <cmath>
#include <numeric> 
#include <cstdlib>

#ifndef __Correlator_h
#define __Correlator_h

class Correlator {
private:
    int N;
    int rmin;
    int rmax;
    int dr;
    
    vector<float> XD, YD;
    vector<float> XR, YR;
    vector<float> DD, RR, DR;
    
    vector<float> Chi1, Chi2;
    
public:
    Correlator();
    
    void ReadXY();
    void GenerateRR();
    
    void CorrDD();
    void CorrRR();
    void CorrDR();
    
    void CalcChi();
    
    void WriteData();
};

#endif
    
    
