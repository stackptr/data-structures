SHELL = /bin/sh
CC = g++ -Wall -pedantic
CCO = $(CC) -o
CCC = $(CC) -c

all: program

program: main.o wordlist.o
	$(CCO) Retrieve main.o wordlist.o

test2: test2.o wordlist.o dll.o
	$(CCO) test2 test2.o wordlist.o

wordlist.o: wordlist.cpp wordlist.h dll.h
	$(CCC) wordlist.cpp wordlist.h

test: test.cpp dll.h
	$(CCO) test test.cpp