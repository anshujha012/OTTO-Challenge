//Anshu Sharma
//March 3rd 2020
//Waypoint.h
//This file contains the class definition for the Waypoint class.

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>

#define MAXWAYPOINTS 100
#define MAXWAYPOINTSETS 100

class Waypoint {

private:

	int waypoint_num;
	int x;
	int y;
	int penalty;
	int total_waypoints;
	
public:

	//Constructor + Destructor
	Waypoint(void);
	~Waypoint(void);

	//Accessors
	const int GetWaypoint_Num(void);
	const int GetX(void);
	const int GetY(void);
	const int GetPenalty(void);
	const int GetTotal_Waypoints(void);

	//Mutators
	bool SetWaypoint_Num(int new_num);
	bool SetX(int new_x);
	bool SetY(int new_y);
	bool SetPenalty(int new_penalty);
	bool SetTotal_Waypoints(int new_total_waypoints);

	void print_waypoint(void);
};
