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
void add_time(Otto &Robot, float travel_time, int penalty);

int total_sets = 0;

int main() {

	Waypoint Waypoints[MAXWAYPOINTSETS][MAXWAYPOINTS];
  Otto Robot;
  int x1, y1, penalty1, x2, y2 , x3, y3= 0;
  int path_route = 0;
  
  int waypoint_count = 0;

  parse_text_file(Waypoints);

  //Iterate the sets of waypoints
  for (int i = 0; i < total_sets; i++) {

    //Get how many waypoints are in this set
    waypoint_count = Waypoints[i][0].GetTotal_Waypoints();
    Robot.reset_otto();

    //Iterate the waypoints within the set
    for (int j = 0; j < waypoint_count; j++) {

      //Get adjacent point coordinates
      x1 = Waypoints[i][j].GetX();
      y1 =  Waypoints[i][j].GetY();  
      penalty1 = Waypoints[i][j].GetPenalty();

      //Get the next point's coordinates
      x2 = Waypoints[i][j+1].GetX();
      y2 = Waypoints[i][j+1].GetY(); 

      //Get the next point's next coordinates
      x3 = Waypoints[i][j+2].GetX();
      y3 = Waypoints[i][j+2].GetY(); 

      path_route = Robot.calculate_quickest_path(x1, y1, penalty1, x2, y2, x3, y3);
  
      if (path_route == 1) {

        //Best path is the adjacent point, move there
        add_time(Robot, Robot.calculate_elapsed_time(Robot.distance_to_point(x1, y1)), 0);
        Robot.move_to_point(x1, y1);
      } else if (path_route == 2) {

        //Best path is to skip the adjacent point, move there
        add_time(Robot, Robot.calculate_elapsed_time(Robot.distance_to_point(x1, y1)), penalty1);
        Robot.move_to_point(x2, y2);
      }
    }

    if (i > 0) {

      cout.setf(ios::fixed,ios::floatfield);
      cout.precision(3);
      cout << round(Robot.GetElapsed_Time() * 1000)/1000 << endl;
    }

  }

  return 1;
}

void add_time(Otto &Robot, float travel_time, int penalty) {

  Robot.increment_elapsed_time(travel_time + (float)penalty + WAYPOINTWAITTIME);
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

	string input = "sample_input_medium.txt";
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

double round(double val)
{
  if( val < 0 ) return ceil(val - 0.5);
  return floor(val + 0.5);
}
