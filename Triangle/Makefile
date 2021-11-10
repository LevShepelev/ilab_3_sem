
all: build run
	
build:
	g++ -c  -O2 Triangle_crossing.cpp -c Triangles_functions.cpp -c Plane.cpp -c Line.cpp -c Vector.cpp
	g++ Triangles_functions.o Triangle_crossing.o Plane.o Line.o Vector.o -o Triangle_crossing

run: build
	./Triangle_crossing < Test_1.txt