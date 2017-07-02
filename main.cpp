//Mike Sadowski
//June 29th, 2017
//main.cpp
//This file contains all of the driver methods for the robot

//valgrind --leak-check=yes ./main

#include "Waypoint.h"
#include "Otto.h"

#include <iostream>     
#include <sstream>     
#include <string>

using namespace std;

//Text file functions
void parse_text_file(Waypoint (&Waypoints)[MAXWAYPOINTSETS][MAXWAYPOINTS]);
string tokenize_string(string *s);
void set_waypoint_info(Waypoint &Waypoints, int waypoint_num, int x, int y, int penalty, int total_waypoints);
void read_stdin(void);

void add_time(Otto &Robot, float travel_distance, int penalty);

void drive_otto(void);

int total_sets = 0;
string input = "";

int main() {

  Waypoint Waypoints[MAXWAYPOINTSETS][MAXWAYPOINTS];
  Otto Robot;
  int x1, y1, penalty1, x2, y2 = 0;
  int path_route = 0;
  int i, j = 0;
  
  int waypoint_count = 0;

  read_stdin();
  parse_text_file(Waypoints);

  //Iterate the sets of waypoints
  for (i = 0; i < total_sets; i++) {

    //Get how many waypoints are in this set
    waypoint_count = Waypoints[i][0].GetTotal_Waypoints();
    Robot.reset_otto();

    //Iterate the waypoints within the set
    for (j = 0; j < waypoint_count; j++) {

      //Get adjacent point coordinates
      x1 = Waypoints[i][j].GetX();
      y1 =  Waypoints[i][j].GetY();  
      penalty1 = Waypoints[i][j].GetPenalty();

      //Get the next point's coordinates
      x2 = Waypoints[i][j+1].GetX();
      y2 = Waypoints[i][j+1].GetY();

      path_route = Robot.calculate_quickest_path(x1, y1, penalty1, x2, y2);
  
      if (path_route == 1) {

        //Best path is the adjacent point, move there
        add_time(Robot, Robot.calculate_elapsed_time(Robot.distance_to_point(x1, y1)), 0);
        Robot.move_to_point(x1, y1);
      } else if (path_route == 2) {

        //Best path is to skip the adjacent point, move to the immediate point after
        add_time(Robot, Robot.calculate_elapsed_time(Robot.distance_to_point(x2, y2)), penalty1);
        Robot.move_to_point(x2, y2);
      }
    }

    if (i > 0) {

      //Otto has finished the waypoint set, print his time
      cout.setf(ios::fixed,ios::floatfield);
      cout.precision(3);
      cout << round(Robot.GetElapsed_Time() * 1000)/1000 << endl;
    }
  } 

  return 1;
}

void add_time(Otto &Robot, float travel_distance, int penalty) {

  Robot.increment_elapsed_time(travel_distance + (float)penalty + WAYPOINTWAITTIME);
}

//Text file Functions
void parse_text_file(Waypoint (&Waypoints)[MAXWAYPOINTSETS][MAXWAYPOINTS]) {

  istringstream line_contents(input);
  string token = "";
  int waypoint_set_index = 0;
  int waypoint_index = 0;
  int total_waypoints = 0;
  
  while (getline(line_contents, token)) {

    if(token.find(" ") == string::npos) {

      if(waypoint_set_index != 0) {

          //Append the (100,100) to the end of the list
          set_waypoint_info(Waypoints[waypoint_set_index][waypoint_index], waypoint_index+1, ENDPOINTX, ENDPOINTY, 0, total_waypoints);
        } 

        //A new set of waypoints is going to be saved
        waypoint_set_index++;
        waypoint_index = 0; 

        //Add 1 to make up for the added (100,100)
        total_waypoints = atoi(token.c_str()) + 1;
        total_sets++;
      } else {

          //Insert waypoint into array for current set index, then increase the waypoint index to insert next waypoint
          set_waypoint_info(Waypoints[waypoint_set_index][waypoint_index], waypoint_index+1, atoi(tokenize_string(&token).c_str()), 
              atoi(tokenize_string(&token).c_str()), atoi(tokenize_string(&token).c_str()), total_waypoints);
          waypoint_index++;
        }
    }
}

void set_waypoint_info(Waypoint &Waypoints, int waypoint_num, int x, int y, int penalty, int total_waypoints) {

  Waypoints.SetWaypoint_Num(waypoint_num);
  Waypoints.SetX(x);
  Waypoints.SetY(y);
  Waypoints.SetPenalty(penalty);
  Waypoints.SetTotal_Waypoints(total_waypoints);
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
  if( val < 0 ) 
    return ceil(val - 0.5);

  return floor(val + 0.5);
}

void read_stdin(void) {
  
   string line = "";

  while(cin) {

    if(getline(cin, line)) {
            
      input.append(line);
      input.append("\n");
    }
  }
}
