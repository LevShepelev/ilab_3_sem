
all: build run
	
build: Matrix.h
	g++ -Wall -c -g -O0 Matrix.cpp
	g++ Matrix.o -o Matrix
	g++ -c -g -Wall Test_maker.cpp
	g++ Test_maker.o -o Test_maker

run: build
	./Matrix < Test.txt
	