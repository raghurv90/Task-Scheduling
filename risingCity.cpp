#include <bits/stdc++.h>
#include <fstream>
#include "input_parsing_functions.h"
#include "Building.h"
using namespace std;

int main(int argc, char* argv[]) {

	int day=0; 		/*   @day = global counter */
	string line;
    vector<string> input_command;
    HeapNode* current_project = NULL;			/* @current_project = Current building that is being constructed */
    int current_project_executed_days = 0;
    BuildingClass* Building = new BuildingClass;

    ifstream input_file(argv[1]);
    ofstream output_into_file;
    output_into_file.open("output_file.txt");


 	while(input_file.peek()!=EOF || Building->root != NULL){

/* If there's no active construction building, get a new building to work on */

 		 if(current_project == NULL && Building->heap_curr_size != 0){
 			current_project = get_new_project(Building);
 		 }

 /* Increment the executed time for the active current project */

    	if(current_project != NULL){
    		++(current_project->executed_time);
 			current_project_executed_days++;
    	}

/* Get next input command from the external input file and
   perform the command when the global counter equals the day of the next command  */

    	if(input_file.peek()!=EOF && input_command.empty()){
    		 getline(input_file,line);
             input_command = get_input_into_vector(line);
   	    }

    	if(!input_command.empty() && day == stoi(input_command[0])){
    		string printable_data = perform_command_function(input_command, Building);
    	    if(printable_data.length() != 0){
    		    output_into_file << printable_data <<endl;
    	   }
    	   input_command.clear();
    	}

/* check if the construction is completed and end the building construction
   or if currently worked on the construction for 5 days, add it back to the buildings heap  	*/

 		if(current_project != NULL && (current_project->executed_time == current_project->total_time)){
 			string completed_tuple = end_current_project(current_project,day,Building);
 			output_into_file << completed_tuple <<endl;
 			current_project = NULL;
 			current_project_executed_days = 0;
 		}else if(current_project != NULL && current_project_executed_days == 5){
 			add_current_project_back(current_project,Building);
 		    current_project = NULL;
 		    current_project_executed_days = 0;
 		}

	  day++;
	}
 	output_into_file.close();
	return 0;
}
