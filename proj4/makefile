SHELL = /bin/sh
CC = g++ -Wall -pedantic
CCO = $(CC) -g -o
CCC = $(CC) -c

all: program

program: word.o wordlist.o main.o
	$(CCO) Retrieve main.o wordlist.o word.o

main.o: main.cpp
	$(CCC) main.cpp

wordlist.o: wordlist.cpp wordlist.h bst.h
	$(CCC) wordlist.cpp

word.o: word.cpp word.h
	$(CCC) word.cpp

clean:
	rm *.o
