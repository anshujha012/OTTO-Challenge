all:
	g++ -Wall Otto.cpp Waypoint.cpp main.cpp -o solution_executable

clean:
	rm -f solution_executable