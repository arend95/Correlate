###########################################################
DIRSRC	= ./src/
###########################################################
COMP 	= g++
CFLAGS 	= -O3 -std=c++11
CC 	= $(COMP) $(CFLAGS) -c
CO	= $(COMP) $(CFLAGS) -o
###########################################################
Corr.exe: Main.o Correlator.o
	$(CO) Corr.exe Main.o Correlator.o
###########################################################
Main.o: $(DIRSRC)Main.cpp Correlator.o
	$(CC) $(DIRSRC)Main.cpp -I$(DIRSRC)
Correlator.o: $(DIRSRC)Correlator.h $(DIRSRC)Correlator.cpp
	$(CC) $(DIRSRC)Correlator.cpp
###########################################################
clean:
	rm -f *~
	rm -f *.o
	rm -f *.exe
	rm -f *.out
	rm -f *.png
