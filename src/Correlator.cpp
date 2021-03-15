#include "Correlator.h"

Correlator::Correlator() {
    this->N    = 3000;
    this->rmin = 0;
    this->rmax = 20;
    this->dr   = 1;
    
    Chi1.assign(rmax, 0.0);
    Chi2.assign(rmax, 0.0);

    ReadXY();
    GenerateRR();
}

void Correlator::ReadXY() {
    ifstream inFile;
    inFile.open("xy.txt");
    string valuex, valuey;
    
    if (inFile) {
        while (inFile >> valuex >> valuey) {
            float valx = atof(valuex.c_str());
            float valy = atof(valuey.c_str());
            
            XD.push_back(valx);
            YD.push_back(valy);
        }
    }
    inFile.close();
}

void Correlator::GenerateRR() {
    float min = 64;
    float max = 448;
    srand( (unsigned)time( NULL ) );
    
    for(int i=0; i<N; i++) {
        float tempx = (float) rand()/RAND_MAX;
        float tempy = (float) rand()/RAND_MAX;
            
        XR.push_back(tempx*(max-min) + min);
        YR.push_back(tempy*(max-min) + min);
    }
}

void Correlator::Corr12(vector<float> &X1, vector<float> &Y1, vector<float> &X2, vector<float> &Y2, vector<float> &XX) {
    XX.assign(rmax, 0.0);
    
    for(int i=0; i<N-1; i++) {
        
        for(int j=i+1; j<N; j++) {
            float dx = X1[i] - X2[j];
            float dy = Y1[i] - Y2[j];
            
            float sep = sqrt(dx*dx + dy*dy);
            
            for(int k=rmax-1; k>=0; k--) {
                if(sep > k && sep < k+1) {
                    XX[k] += 2; // Keep in mind each pair is counted twice
                    break;
                }
            }
        }
    }
}

void Correlator::CalcChi() {
    for(int i=0; i<rmax; i++) {
        Chi1[i] = DD[i]/RR[i] - 1.0;
        Chi2[i] = (DD[i] - 2.0*DR[i] + RR[i])/RR[i];
    }
}

void Correlator::WriteData() {
    ofstream Out;
    ofstream RR;
    ofstream DD;
    Out.open("data.out");
    RR.open("RR.txt");
    DD.open("DD.txt");
    
    for(int i=0; i<rmax; i++) {
        Out << Chi1[i] << " " << Chi2[i] << endl;
    }
    
    for(int i=0; i<N; i++) {
        RR << XR[i] << " " << YR[i] << endl;
        DD << XD[i] << " " << YD[i] << endl;
    }
    Out.close();
    RR.close();
    DD.close();
}
