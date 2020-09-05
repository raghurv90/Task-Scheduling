#include <bits/stdc++.h>
#include "Building.h"
using namespace std;

#ifndef INPUT_PARSING_FUNCTIONS_H_
#define INPUT_PARSING_FUNCTIONS_H_


/*    Parsing the input command by replacing special character with a space and splitting the string with space delimiter.  */

vector<string> get_input_into_vector(string input_string){
	vector<string> string_into_vector;
	replace (input_string.begin(), input_string.end(), ':' , ' ');
    replace (input_string.begin(), input_string.end(), '(' , ' ');
    replace (input_string.begin(), input_string.end(), ')' , ' ');
    replace (input_string.begin(), input_string.end(), ',' , ' ');
    stringstream ss(input_string);
    string word;
    while(getline(ss,word,' ')){
      if(word.length() != 0){
    	  string_into_vector.push_back(word);
      }
    }
   return string_into_vector;
}

/*  	Performing the input function command, i.e. inserting a node or printing a triplet or printing active buildings in a given range */


string perform_command_function(vector<string> command, BuildingClass* Building){

	if(command[1] == "Insert"){
		Building->building_insert(stoi(command[2]),0,stoi(command[3]));
		return "";

	}else if(command[1] == "PrintBuilding" && command.size() == 3){

		HeapNode* result = Building->get_building_triplet(stoi(command[2]));
		if(result == NULL){
			return "(0,0,0)" ;
		}else{
			return "(" +  to_string(result->buildingNum)  + "," + to_string(result->executed_time)  + "," + to_string(result->total_time) + ")";
		}

	}else if(command[1] == "PrintBuilding" && command.size() == 4){

		string range_result = Building->print_active_buildings(stoi(command[2]),stoi(command[3]));
		if(range_result.length() == 0){
			return "(0,0,0)";
		}else{
			return range_result;
		}
	}
	return "";
}

/* 	 Adding a building back into the heap after constructing for 5 continuous days. */

void add_current_project_back(HeapNode* current_project,BuildingClass* Building){
	Building->heap_node_insert(current_project);
}

/* 	Ending the project by removing it from Red-Black tree when executed time equals total time.  */

string end_current_project(HeapNode* current_project, int day,BuildingClass* Building){
	Building->building_delete(current_project->rbt_node);
	return "(" + to_string(current_project->buildingNum) + "," + to_string(day) +  ")";
}

/* 	Getting a new project from the heap by getting the minimum in the heap  */

HeapNode* get_new_project(BuildingClass* Building){
	HeapNode* current_project = Building->heap_get_min();
	Building->heap_remove_min();
	return current_project;
}

#endif /* INPUT_PARSING_FUNCTIONS_H_ */
