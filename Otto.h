//Mike Sadowski
//June 29th, 2017
//Otto.h
//This file contains the class definition for the Otto class.

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>

#define WAYPOINTWAITTIME 10

class Otto {

private:

	int elapsed_time;
	int pos_x;
	int pos_y;

public:

	//Constructor + Destructor
	Otto(void);
	~Otto(void);

	//Accessors
	const int GetPos_X(void);
	const int GetPos_Y(void);
	const int GetElapsed_Time(void);

	//Mutators
	bool SetPos_X(int new_num);
	bool SetPos_Y(int new_num);
	bool SetElapsedTime(int new_num);

	void increment_elapsed_time(int num);

	int distance_to_point(int x, int y);
	void move_to_point(int x, int y);
	int calculate_quickest_path(int x1, int y1, int penalty1, int x2, int y2);
	float calculate_elapsed_time(float distance);

	void reset_otto(void);
};
