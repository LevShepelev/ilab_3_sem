
all: build run
	
build:
	g++ -Wall -c -g -O0 Matrix.cpp
	g++ Matrix.o -o Matrix

run: build
	./Matrix < Test.txt