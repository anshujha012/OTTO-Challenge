//Mike Sadowski
//June 29th, 2017
//Waypoint.cpp
//This file contains all of the method bodies for the Otto class.

/*

-start at (0,0) go to wp1, wp2, wp3, etc
-stop for 10s at every waypoint
-end at (100,100) and wait 10s

-if your OTTO went straight from waypoint 1 to waypoint 3, skipping waypoint 2, it would incur waypoint 2's penalty.
-cannot go backwards to hit waypoints
-if waypoint 3 lies directly between waypoints 1 and 2, your OTTO can go straight from 1 to 2, right over 3, without stopping. 
	Since it didn't stop to be loaded, waypoint 3's penalty will not be incurred.
-Because OTTO is a bit slow, it might be advantageous to skip some waypoints and incur their penalty, rather than actually manoeuvring to them. 
	Given a description of a course, determine OTTO's best (lowest) possible time.

-Grid = 100m x 100m
-Speed = 2 m/s

*/

#include "Otto.h"

using namespace std;

//Constructor + Destructor
Otto::Otto(void) {

	elapsed_time = 0;
	pos_x = 0;
	pos_y = 0;
}

Otto::~Otto(void) {

}

//Accessors
const int Otto::GetElapsed_Time(void) {

	return elapsed_time;
}

const int Otto::GetPos_X(void) {

	return pos_x;
}

const int Otto::GetPos_Y(void) {

	return pos_y;
}

//Mutators
bool Otto::SetElapsedTime(int new_num) {

	elapsed_time = new_num;
	return true;
}

bool Otto::SetPos_X(int new_num) {

	pos_x = new_num;
	return true;
}

bool Otto::SetPos_Y(int new_num) {

	pos_y = new_num;
	return true;
}

void Otto::increment_elapsed_time(int num) {

	elapsed_time += num;	
}

int Otto::distance_to_point(int x, int y) {

	//Calculate the distance between the robot's position and the future position
	//cout << GetPos_X() << "," << GetPos_Y() << " to " << x << "," << y << " " << endl;
	
	//cout << sqrt((pos_x - x)^2 + (pos_y - y)^2) << endl; 
	return sqrt((pos_x - x)^2 + (pos_y - y)^2);
}

void Otto::move_to_point(int x, int y) {

	SetPos_X(x);
	SetPos_Y(y);
}

int Otto::calculate_quickest_path(int x1, int y1, int penalty1, int x2, int y2) {

	int distance_to_point = 0.0;
	int distance_to_next_point = 0.0;
	float time_to_point = 0;
	float time_to_next_point = 0;

	distance_to_point = Otto::distance_to_point(x1,y1);
	distance_to_next_point = Otto::distance_to_point(x2,y2);

	//cout << "d1 = " << distance_to_point;
	//cout << "  d2 = " << distance_to_next_point << endl;
	

	time_to_point = calculate_elapsed_time(distance_to_point);
	time_to_next_point = calculate_elapsed_time(time_to_next_point);

	if(time_to_point < (time_to_next_point + penalty1)) {

		//Return 1 to move to the next waypoint
		cout << "Chose next\n";
		return 1;
	} else {

		//Return 2 to skip the next waypoint
		//Penalty + move time is less then the move time to the adjacent waypoint
		//If the two times are equal, we want to move to the furthest point to be efficient
		cout << "Chose skip\n";
		return 2;
	}
}

float Otto::calculate_elapsed_time(float distance) {

	//Robot moves 2m/s
	return (distance / 2);
}

void Otto::reset_otto(void) {

	move_to_point(0,0);
	SetElapsedTime(0);
}
