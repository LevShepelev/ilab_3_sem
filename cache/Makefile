
all: build run
	
build:
	g++ -c -g -O0 cache.cpp
	g++ -Wall cache.o -o cache
	g++ -c Cache_tester.cpp
	g++ -Wall Cache_tester.o -o Cache_tester
	g++ -c -g -O0 Ideal_cache.cpp
	g++ -Wall Ideal_cache.o -o Ideal_cache
	
run1: build
	./Cache_tester ./cache
	 
run2: build 
	./Cache_tester ./Ideal_cache

run3: build
	./cache