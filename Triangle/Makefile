
all: build run
	
build:
	g++ -c -g -O2 Triangle_crossing.cpp -c Triangles_functions.cpp -c ./Geometry/Plane.cpp -c ./Geometry/Line.cpp -c ./Geometry/Vector.cpp
	g++ Triangles_functions.o Triangle_crossing.o Plane.o Line.o Vector.o -o Triangle_crossing

run: build
	./Triangle_crossing < 10000.1.txt