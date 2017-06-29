//Mike Sadowski
//June 29th, 2017
//Otto.cpp
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
const float Otto::GetElapsed_Time(void) {

	return elapsed_time;
}

const int Otto::GetPos_X(void) {

	return pos_x;
}

const int Otto::GetPos_Y(void) {

	return pos_y;
}

//Mutators
bool Otto::SetElapsedTime(float new_num) {

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

void Otto::increment_elapsed_time(float num) {

	elapsed_time += num;	
}

float Otto::distance_to_point(int x, int y) {

	//Calculate the distance between the robot's position and the future position
	return distance_between_points(pos_x, pos_y, x, y);

}

void Otto::move_to_point(int x, int y) {

	SetPos_X(x);
	SetPos_Y(y);
}

int Otto::calculate_quickest_path(int x1, int y1, int penalty1, int x2, int y2, int penalty2, int x3, int y3) {

	float distance_to_point = 0.0;
	float distance_to_next_point = 0.0;
	//float distance_to_next_next_point = 0.0;
	float time_to_point = 0;
	float time_to_next_point = 0;
	//float time_to_next_next_point = 0;

	/*float distance1 = 0.0;
	float distance2 = 0.0;
	float time1 = 0.0;
	float time2 = 0.0;*/

	//Calculate the time it will take to get to the next point and the point after that from current position
	distance_to_point = Otto::distance_to_point(x1,y1);
	distance_to_next_point = Otto::distance_to_point(x2,y2);	
	time_to_point = calculate_elapsed_time(distance_to_point);
	time_to_next_point = calculate_elapsed_time(distance_to_next_point);

	//Calculate if the next point's next is closer than the next point 
	/*distance_to_next_next_point = distance_between_points(x2, y2, x3, y3);
	time_to_next_next_point = calculate_elapsed_time(distance_to_next_next_point);

	distance1 = distance_between_points(x1, y1, x3, y3);
	distance2 = distance_between_points(x2, y2, x3, y3);

	time1 = calculate_elapsed_time(distance1) + (float)penalty2;
	time2 = calculate_elapsed_time(distance2) + (float)penalty1;
*/
	if (time_to_point < (time_to_next_point + penalty1)){

		//Return 1 to move to the next waypoint
		return 1;
	} else {
		//Return 2 to skip the next waypoint
		return 2;
	}
}

float Otto::calculate_elapsed_time(float distance) {

	//Robot moves 2m/s
	return (distance / 2);
}

void Otto::reset_otto(void) {

	move_to_point(0, 0);
	SetElapsedTime(0);
}

float Otto::distance_between_points(int x1, int y1, int x2, int y2) {

	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}
