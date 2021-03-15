#include "Correlator.h"

int main(int argc, char *argv[]) {
    Correlator cr;

    cr.CorrDD();
    cr.CorrRR();
    cr.CorrDR();
    
    cr.CalcChi();
    cr.WriteData();
    return 0;
}
