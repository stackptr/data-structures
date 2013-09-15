SHELL = /bin/sh
CC = g++ -Wall -pedantic
CCO = $(CC) -o
CCC = $(CC) -c

all: recurse driver

recurse: main.cpp
	$(CCO) recurse main.cpp

driver: driver.cpp vector.h stack.h
	$(CCO) program driver.cpp

clean:
	rm -rf *o recurse driver