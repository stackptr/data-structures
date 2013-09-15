SHELL = /bin/sh
CC = g++ -Wall -pedantic -std=c++0x -O0
CCO = $(CC) -g -o
CCC = $(CC) -c

all: program

program: compare.cpp cputime.h
	$(CCO) compare-containers compare.cpp

MyDS.o: MyDS.h MyDS.cpp vector.h list.h
	$(CCC) MyDS.cpp MyDS.h

clean:
	rm *.o
