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
void set_waypoint_info(Waypoint &Waypoints, int waypoint_num, int x, int y, int penalty, int total_waypoints);

int total_sets = 0;

int main() {

	Waypoint Waypoints[MAXWAYPOINTSETS][MAXWAYPOINTS];
  Otto Robot;
  int x1, y1, penalty1, x2, y2 = 0;
  int path_route = 0;
  float elapsed_time = 0.0;
  int waypoint_count = 0;

  parse_text_file(Waypoints);

  //Iterate the sets of waypoints
  for (int i = 0; i < total_sets; i++) {

    //Get how many waypoints are in this set
    waypoint_count = Waypoints[i][0].GetTotal_Waypoints();

    //Iterate the waypoints within the set
    for (int j = 0; j < waypoint_count; j++) {

      if (Waypoints[i][j].GetWaypoint_Num() == 1) {

        //Reset Otto to (0,0) and t=0 since this is the first waypoint within the set
        Robot.reset_otto();
      }

      //Get adjacent point coordinates
      x1 = Waypoints[i][j].GetX();
      y1 =  Waypoints[i][j].GetY();  
      penalty1 = Waypoints[i][j].GetPenalty();

      //Get the next point's coordinates
      x2 = Waypoints[i][j+1].GetX();
      y2 = Waypoints[i][j+1].GetY(); 

      path_route = Robot.calculate_quickest_path(x1, y1, penalty1, x2, y2);
  
      //elapsed_time = Robot.calculate_elapsed_time(Robot.distance_to_point(x1, y1));

      if (path_route == 1) {

        //Best path is the adjacent point, move there
        //Elapsed time is 10s for the wait + the walking time, no penalty
        Robot.move_to_point(x1, y1);
      } else if (path_route == 2) {

        Robot.move_to_point(x2, y2);
      }
      
      if (Robot.GetPos_X() == 0 && Robot.GetPos_Y() == 0) {

        cout << "FINISHED\n";
      }

      //Waypoints[i][j].print_waypoint();
      //cout << x1 << "," << y1 << " " << penalty1 << "  Next point: " << x2 << "," << y2 << "  " << elapsed_time << endl;

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
  int total_waypoints = 0;

	open_text_file(filename, text_file);

    while (getline(text_file, line_contents)) {

        //Find the line with only 1 number on it, that is the new set of waypoints
        if(line_contents.find(" ") == std::string::npos) {

          if(waypoint_set_index != 0) {

            //Append the (100,100) to the end of the list
            set_waypoint_info(Waypoints[waypoint_set_index][waypoint_index], waypoint_index+1, ENDPOINTX, ENDPOINTY, 0, total_waypoints);
            //cout << "adding 100,100\n";
          } 

        	//A new set of waypoints is going to be saved
        	waypoint_set_index++;
        	waypoint_index = 0; 

          //Add 1 to make up for the added (100,100)
          total_waypoints = atoi(line_contents.c_str()) + 1;
          total_sets++;
        } else {
	
        	//Insert waypoint into array for current set index, then increase the waypoint index to insert next waypoint
          set_waypoint_info(Waypoints[waypoint_set_index][waypoint_index], waypoint_index+1, atoi(tokenize_string(&line_contents).c_str()), 
              atoi(tokenize_string(&line_contents).c_str()), atoi(tokenize_string(&line_contents).c_str()), total_waypoints);
        	waypoint_index++;
        }
    }

	text_file.close();
}

void set_waypoint_info(Waypoint &Waypoints, int waypoint_num, int x, int y, int penalty, int total_waypoints) {

  Waypoints.SetWaypoint_Num(waypoint_num);
  Waypoints.SetX(x);
  Waypoints.SetY(y);
  Waypoints.SetPenalty(penalty);
  Waypoints.SetTotal_Waypoints(total_waypoints);
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
