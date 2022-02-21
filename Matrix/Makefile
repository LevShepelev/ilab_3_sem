
all: build run
	
build: ./include/Matrix.h
	g++ -Wall -c -g -O0 ./source/Matrix.cpp
	g++ ./source/Matrix.o -o ./source/Matrix
	g++ -c -g -Wall ./source/Test_maker.cpp
	g++ ./source/Test_maker.o -o ./source/Test_maker

run: build
	./source/Matrix < ./Tests/Test.txt
	