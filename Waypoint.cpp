//Anshu Sharma
//March 3rd 2020
//Waypoint.cpp
//This file contains all of the method bodies for the Waypoint class.

#include "Waypoint.h"

using namespace std;

Waypoint::Waypoint(void) {
	waypoint_num = 0;
	x = 0;
	y = 0;
	penalty = 0;
}

Waypoint::~Waypoint(void) {

}

//Accessors
const int Waypoint::GetWaypoint_Num(void) {

	return waypoint_num;
}

const int Waypoint::GetX(void) {

	return x;
}

const int Waypoint::GetY(void) {

	return y;
}

const int Waypoint::GetPenalty(void) {

	return penalty;
}

const int Waypoint::GetTotal_Waypoints(void) {

	return total_waypoints;
}


//Mutators
bool Waypoint::SetWaypoint_Num(int new_waypoint_num) {

	waypoint_num = new_waypoint_num;
	return true;
}

bool Waypoint::SetX(int new_x) {

	x = new_x;
	return true;
}

bool Waypoint::SetY(int new_y) {

	y = new_y;
	return true;
}

bool Waypoint::SetPenalty(int new_penalty) {

	penalty = new_penalty;
	return true;
}

bool Waypoint::SetTotal_Waypoints(int new_total_waypoints) {
	
	total_waypoints = new_total_waypoints;
	return true;
}

void Waypoint::print_waypoint(void) {

	cout << "Waypoint Number:" << GetWaypoint_Num() << " ";
	cout << "X:" << GetX() << " ";
	cout << "Y:" << GetY() << " ";
	cout << "Penalty:" << GetPenalty() << endl;
}


