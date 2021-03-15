import os
import math
import matplotlib.pyplot as pt
import matplotlib
matplotlib.rcParams.update({'font.size': 20})
matplotlib.rcParams['mathtext.fontset'] = 'stix'
matplotlib.rcParams['font.family'] = 'STIXGeneral'
pt.rcParams['xtick.top'] = True
pt.rcParams['ytick.right'] = True

def RunStuff():
    os.system("./Corr.exe") 
    
def Convert(string):
    li = map(float, string.split(" "))
    line = []
    for lli in li:
        line.append(lli)
        
    return line

def ReadChi():
    Chi1 = []
    Chi2 = []
    
    r    = []
    i = 0.0
    with open("data.out","r") as dat:
        for line in dat:
            line = Convert(line)
            
            Chi1.append(line[0])
            Chi2.append(line[1])
            r.append(i+0.5)
            i += 1.0
            
    return Chi1, Chi2, r

def PlotChi(Chi1, Chi2, r):
    fig, ax = pt.subplots(1,1, figsize=(10,10))
    ax.plot(r, Chi1, 'b', label="simple estimator")
    ax.plot(r, Chi2, label="LS", color="orange")
    ax.set_xlabel(r"$r$")
    ax.set_ylabel(r"$\xi$")
    ax.set_xlim(0,20)
    ax.tick_params(which="both", direction="in")
    ax.legend(frameon=False, prop={'size': 20})
    
    pt.savefig(fname="xi.png",bbox_inches='tight', dpi=300)
    pt.show()
    
def PlotFields():
    XD = []
    YD = []
    XR = []
    YR = []
    
    with open("DD.txt","r") as dat, open("RR.txt","r") as rat:
        for line0, line1 in zip(dat, rat):
            line0 = Convert(line0)
            line1 = Convert(line1)
            XD.append(line0[0])
            YD.append(line0[1])
            
            XR.append(line1[0])
            YR.append(line1[1])
    
    fig, ax = pt.subplots(2,1, figsize=(10,10))
    ax[0].plot(XD, YD, "b.")
    ax[1].plot(XR, YR, "b.")
    
    pt.show()
    
if __name__ == "__main__":
    length = input("# N runs ?(y|n): ")
    Nsim = 1000 # Nice and high...
    rms1 = 0.0
    rms2 = 0.0
    
    if length == 'n':
        RunStuff()
        Chi1, Chi2, r = ReadChi()
    
        PlotChi(Chi1, Chi2, r)
        PlotFields()
        
        for k in range(len(r)):
            rms1 += Chi1[k]**2
            rms2 += Chi2[k]**2
            
        rms1 = math.sqrt(rms1/len(Chi1))
        rms2 = math.sqrt(rms2/len(Chi2))
    
        print("# rms 1 = {}".format(rms1))
        print("# rms 2 = {}".format(rms2))
            
        
    if length == 'y':
        RunStuff()
        Chi1, Chi2, r = ReadChi()
        Chi1tot = Chi1
        Chi2tot = Chi2 # Remember to normalize with N+1 because of this extra step
        for i in range(Nsim):
            print(i)
            RunStuff()
            Chi1, Chi2, r = ReadChi()
            
            for k in range(len(r)):
                Chi1tot[k] += Chi1[k]/(Nsim+1)
                Chi2tot[k] += Chi2[k]/(Nsim+1)
        
        PlotChi(Chi1tot, Chi2tot, r)
        
        for k in range(len(r)):
            rms1 += Chi1[k]**2
            rms2 += Chi2[k]**2
            
        rms1 = math.sqrt(rms1/len(Chi1))
        rms2 = math.sqrt(rms2/len(Chi2))
    
        print("# rms 1 = {}".format(rms1))
        print("# rms 2 = {}".format(rms2))
