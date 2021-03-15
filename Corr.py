import os
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
    
if __name__ == "__main__":
    RunStuff()
    Chi1, Chi2, r = ReadChi()
    PlotChi(Chi1, Chi2, r)
