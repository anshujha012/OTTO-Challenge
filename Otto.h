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

class Otto {

private:

	int pos_x;
	int pos_y;

public:

	//Constructor + Destructor
	Otto(void);
	~Otto(void);

	//Accessors
	const int GetPos_X(void);
	const int GetPos_Y(void);

	//Mutators
	bool SetPos_X(int new_num);
	bool SetPos_Y(int new_num);
};
