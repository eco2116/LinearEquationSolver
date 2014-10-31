# Evan O'Connor - eco2116
# CS3251 - Homework 1

# Makefile

CXX = g++
CXXFLAGS = -g -Wall $(INCLUDES)

LDFLAGS = -g -lstdc++

main: main.o matrix.o
main.o: main.cpp matrix.h
matrix.o: matrix.cpp matrix.h

.PHONY: clean
clean:
	rm -f *.o core main

.PHONY: all
all: clean main

