//Mike Sadowski
//June 29th, 2017
//main.cpp
//This file contains all of the driver methods for the robot

//valgrind --leak-check=yes ./main
//sample_input_medium.txt

#include "Waypoint.h"

using namespace std;

//Text file Functions
void parse_text_file(Waypoint (&Waypoints)[MAXWAYPOINTSETS][MAXWAYPOINTS]);
string get_text_file_name();
void open_text_file(string filename, ifstream &file);
string tokenize_string(string *s);

int main() {

	Waypoint Waypoints[MAXWAYPOINTSETS][MAXWAYPOINTS];

  	parse_text_file(Waypoints);

  	for (int i = 0; i < MAXWAYPOINTSETS; i++) {
  		for (int j = 0; j < MAXWAYPOINTSETS; j++) {
  			if (Waypoints[i][j].GetWaypoint_Num() > 0)
	    		Waypoints[i][j].print_waypoint(); 
  		}	   	
    }

  	return 1;
}

//Text file Functions
void parse_text_file(Waypoint (&Waypoints)[MAXWAYPOINTSETS][MAXWAYPOINTS]) {

	string filename = get_text_file_name();
	ifstream text_file;
	string line_contents;
	int waypoint_set_index = 0;
	int waypoint_index = 0;

	open_text_file(filename, text_file);

    while (getline(text_file, line_contents)) {

        //Find the line with only 1 number on it, that is the new set of waypoints
        if(line_contents.find(" ") == std::string::npos) {

        	//A new set of waypoints is going to be saved
        	waypoint_set_index++;
        	waypoint_index = 0; 
        } else {
	
        	//Insert waypoint into array for current set index, then increase the waypoint index to insert next waypoint
        	Waypoints[waypoint_set_index][waypoint_index].SetWaypoint_Num(waypoint_index+1);
        	Waypoints[waypoint_set_index][waypoint_index].SetX(atoi(tokenize_string(&line_contents).c_str()));
        	Waypoints[waypoint_set_index][waypoint_index].SetY(atoi(tokenize_string(&line_contents).c_str()));
        	Waypoints[waypoint_set_index][waypoint_index].SetPenalty(atoi(tokenize_string(&line_contents).c_str()));
        	waypoint_index++;
        }
    }

	text_file.close();
}

string get_text_file_name() {

	string input = "sample_input_large.txt";
	//cout << "Text file name (include '.txt'): \n> ";
 	//getline(cin, input);
 	return input;
}

void open_text_file(string filename, ifstream &file) {

	file.open(filename);
	if (!file) {
    	cerr << "> Unable to open file: " << filename << endl;
		exit(1);
	} 
}

string tokenize_string(string *s) {

	size_t pos = 0;
	string token = "";

	//create a substring from the start of the string to the space
    pos = s->find(" ");
    token = s->substr(0, pos);
    
    //Erase the substring
    s->erase(0, pos + 1);

    return token;
}
