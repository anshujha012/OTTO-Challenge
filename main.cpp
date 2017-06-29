//Mike Sadowski
//June 29th, 2017
//main.cpp
//This file contains all of the driver methods for the robot

//valgrind --leak-check=yes ./main
//sample_input_medium.txt

#include "Waypoint.h"
#include "Otto.h"

using namespace std;

//Text file Functions
void parse_text_file(Waypoint (&Waypoints)[MAXWAYPOINTSETS][MAXWAYPOINTS]);
string get_text_file_name();
void open_text_file(string filename, ifstream &file);
string tokenize_string(string *s);

int main() {

	Waypoint Waypoints[MAXWAYPOINTSETS][MAXWAYPOINTS];
  Otto Robot;
  int x1, y1, penalty1, x2, y2 = 0;
  int path_route = 0;
  float elapsed_time = 0.0;

  parse_text_file(Waypoints);


  for (int i = 0; i < MAXWAYPOINTSETS; i++) {
  	for (int j = 0; j < MAXWAYPOINTSETS; j++) {

      if (Waypoints[i][j].GetWaypoint_Num() > 0) {

        if (Waypoints[i][j].GetWaypoint_Num() == 1) {

          //Waypoints[i][j].print_waypoint();
          //Save Otto's info and reset him for next set of waypoints once a new set is reached
          cout << "-------------------" << endl;
          cout << "Robot: " << Robot.GetPos_X() << "," << Robot.GetPos_Y() << endl;
          //cout << Robot.GetElapsed_Time() << endl;
          Robot.reset_otto();
        } 

        x1 = Waypoints[i][j].GetX();
        y1 =  Waypoints[i][j].GetY();
        penalty1 = Waypoints[i][j].GetPenalty();
        
        if(Waypoints[i][j+1].GetWaypoint_Num() != 0) {

          //Get the next point after the adjacent one's coords
          x2 = Waypoints[i][j+1].GetX();
          y2 = Waypoints[i][j+1].GetY();
        } else {

          //Reached the end of the set list, next point is (100,100)
          x2 = 100;
          y2 = 100;
        }    
          
        cout << x1 << "," << y1 << " " << penalty1 << "  Next point: " << x2 << "," << y2 << endl;
        //path_route = Robot.calculate_quickest_path(x1, y1, penalty1, x2, y2);

        /*if(path_route == 1) {

          Robot.move_to_point(x1, y1);
        } else if (path_route == 2) {

          Robot.move_to_point(x2, y2);
        }*/


        /*if (x2 != 100 && y2 != 100) {

          //Decide which point to move to next
          //1 = adjacent point, 2 = skip the adjacent point and go to the next one
          path_route = Robot.calculate_quickest_path(x1, y1, penalty1, x2, y2);
          if(path_route == 1) {

            //Move to adjacent point, no penalty
            Robot.move_to_point(x1, y1);
            
            //elapsed_time += WAYPOINTWAITTIME + Robot.calculate_elapsed_time(Robot.distance_to_point(x1,y1));        
          } else if (path_route == 2) {

            //Skip the adjacent point, move to next one and incur the penalty
            Robot.move_to_point(x2, y2); 
            
            //elapsed_time += WAYPOINTWAITTIME + Robot.calculate_elapsed_time(Robot.distance_to_point(x2,y2)) + penalty1;    
          }     
        } else {

          //Last point is 100,100 so just move there and wait 10s. No penalty
          Robot.move_to_point(x2, y2);
          
          //elapsed_time += WAYPOINTWAITTIME + Robot.calculate_elapsed_time(Robot.distance_to_point(x2,y2));
        }*/
        //cout << "Robot: " << Robot.GetPos_X() << "," << Robot.GetPos_Y() << endl;
      }
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

	string input = "sample_input_small.txt";
	//string input = "";
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
