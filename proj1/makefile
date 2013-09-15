SHELL = /bin/sh
CC = g++ -Wall -pedantic
CCO = $(CC) -o
CCC = $(CC) -c

all: program

program: main.o wordweights.o
	$(CCO) Retrieve main.o wordweights.o

wordweights.o: wordweights.cpp wordweights.h
	$(CCC) wordweights.cpp wordweights.h