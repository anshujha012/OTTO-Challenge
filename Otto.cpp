//Mike Sadowski
//June 29th, 2017
//Otto.cpp
//This file contains all of the method bodies for the Otto class.

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

int Otto::calculate_quickest_path(int x1, int y1, int penalty1, int x2, int y2) {

	float next_to_skip_distance = 0.0;
	float current_to_skip_distance = 0.0;
	
	float time_next_to_skip = 0;
	float time_to_skip = 0;

	if (pos_x == 100 && pos_y == 100) {

		//Otto is finished the course if the current point is 100,100
		return 0;
	}

	//Calculate distance between the next point and the point after that
	next_to_skip_distance = Otto::distance_between_points(x1, y1, x2, y2);

	//Calculate the distance between the current point to the skip point
	current_to_skip_distance = Otto::distance_to_point(x2,y2);

	//Calculate the time it takes to skip the next point
	time_to_skip = calculate_elapsed_time(current_to_skip_distance);

	//Calculate the time it takes to get from the next point to its next point
	time_next_to_skip = calculate_elapsed_time(next_to_skip_distance);
		
	if (time_next_to_skip <= (time_to_skip + penalty1)) {
	
		//The time it takes to skip the point and the penalty for skipping is higher then the time it takes to go through the point
		return 1;
	} else {

		//The time it takes to skip the point and the penalty for skipping is lower then the time it takes to go through the point
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
