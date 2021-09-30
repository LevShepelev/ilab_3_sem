
all: build run
	
build:
	g++ -c -g -O0 Triangle_crossing.cpp
	g++ -Wall Triangle_crossing.o -o Triangle_crossing
	
run: build
	./Triangle_crossing < Test.txt