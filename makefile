all:
	g++ -Wall Otto.cpp Waypoint.cpp main.cpp -o main

clean:
	rm -f main