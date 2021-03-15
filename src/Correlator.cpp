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
    int numax = 55; // 55 ~ sqrt(3000), uniform distribution
    float incr = (max-min)/numax; 
    
    for(int i=0; i<numax; i++) {
        float temp = min + incr*i;
        XR.push_back(temp);
        YR.push_back(temp);
    }
}
        

void Correlator::CorrDD() {
    DD.assign(rmax, 0.0);
    for(int i=0; i<N-1; i++) {
        
        for(int j=i+1; j<N; j++) {
            float dx = XD[i] - XD[j];
            float dy = YD[i] - YD[j];
            
            float sep = sqrt(dx*dx + dy*dy);
            
            for(int k=rmax-1; k>=0; k--) {
                if(sep > k && sep < k+1) {
                    DD[k] += 2; // Keep in mind each pair is counted twice
                    break;
                }
            }
        }
    }
}

void Correlator::CorrRR() {
    RR.assign(rmax, 0.0);
    for(int i=0; i<N-1; i++) {
        
        for(int j=i+1; j<N; j++) {
            float dx = XR[i] - XR[j];
            float dy = YR[i] - YR[j];
            
            float sep = sqrt(dx*dx + dy*dy);
            
            for(int k=rmax-1; k>=0; k--) {
                if(sep > k && sep < k+1) {
                    RR[k] += 2; // Keep in mind each pair is counted twice
                    break;
                }
            }
        }
    }
}

void Correlator::CorrDR() {
    DR.assign(rmax, 0.0);
    for(int i=0; i<N-1; i++) {
        
        for(int j=i+1; j<N; j++) {
            float dx = XD[i] - XR[j];
            float dy = YD[i] - YR[j];
            
            float sep = sqrt(dx*dx + dy*dy);
            
            for(int k=rmax-1; k>=0; k--) {
                if(sep > k && sep < k+1) {
                    DR[k] += 2; // Keep in mind each pair is counted twice
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
    ofstream Output;
    Output.open("data.out");
    
    for(int i=0; i<rmax; i++) {
        Output << Chi1[i] << " " << Chi2[i] << endl;
    }
    Output.close();
}
