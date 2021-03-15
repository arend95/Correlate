#include "Correlator.h"

int main(int argc, char *argv[]) {
    Correlator cr;
    
    cr.Corr12(cr.XD, cr.YD, cr.XD, cr.YD, cr.DD);
    cr.Corr12(cr.XR, cr.YR, cr.XR, cr.YR, cr.RR);
    cr.Corr12(cr.XD, cr.YD, cr.XR, cr.YR, cr.DR);
    
    cr.CalcChi();
    cr.WriteData();
    return 0;
}
