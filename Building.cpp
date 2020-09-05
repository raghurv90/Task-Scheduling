#include <bits/stdc++.h>
#include "Building.h"
using namespace std;

/* Adding building both into heap and Red-Black tree */

void BuildingClass::building_insert(int curr_buildingNum,int curr_executed_time, int curr_total_time){

    HeapNode* temp_heap_Node = new HeapNode(curr_buildingNum,curr_executed_time,curr_total_time);
	RBT_Node* temp_RBT_Node = new RBT_Node(curr_buildingNum);

	temp_heap_Node->rbt_node = temp_RBT_Node;
	temp_RBT_Node->heap_node = temp_heap_Node;

	heap_node_insert(temp_heap_Node);
	RBT_node_insert(temp_RBT_Node);

}

/* 	Deleting from Red black tree when construction is completed		*/

void BuildingClass::building_delete(RBT_Node* buildingNode){
	RBT_node_delete(buildingNode);
}

/*	Recursive Search for value of a node in Red-Black Tree	*/

RBT_Node* BuildingClass::RBT_search_val(RBT_Node* rbt_node, int target_buildingNum){
	if(rbt_node == NULL){
		return NULL;
	}
	if(rbt_node->val == target_buildingNum){
		return rbt_node;
	}else if(rbt_node->val > target_buildingNum){
		return (rbt_node->left != NULL) ? RBT_search_val(rbt_node->left,target_buildingNum) : NULL;
	}else{
		return (rbt_node->right != NULL) ? RBT_search_val(rbt_node->right,target_buildingNum) : NULL;
	}
}


HeapNode* BuildingClass::get_building_triplet(int buildingNum){
	return (RBT_search_val(root,buildingNum) != NULL) ? RBT_search_val(root,buildingNum)->heap_node : NULL;
}

/*	Inorder Traversal in Red Black Tree and getting the resulting string for building range	*/

string BuildingClass::update_result(RBT_Node* rbt_node,string result_string){
	if(rbt_node == NULL){return "";}
	result_string += "(" + to_string(rbt_node->heap_node->buildingNum) + "," + to_string(rbt_node->heap_node->executed_time) + "," + to_string(rbt_node->heap_node->total_time)+ "),";
	return result_string;
}


string BuildingClass::inorder_traversal_range(RBT_Node* rbt_node, int buildingNum1, int buildingNum2, string result_string){
	if(rbt_node == NULL){return result_string;}
	if(rbt_node->left != NULL){
		if(rbt_node->left->val >= buildingNum1 && rbt_node->left->val <= buildingNum2){
			result_string = inorder_traversal_range(rbt_node->left, buildingNum1, buildingNum2, result_string);
		}
	}
	if(rbt_node->val >= buildingNum1 && rbt_node->val <= buildingNum2){
	    result_string = update_result(rbt_node,result_string);
	}
	if(rbt_node->right != NULL){
		if(rbt_node->right->val >= buildingNum1 && rbt_node->right->val <= buildingNum2){
			result_string = inorder_traversal_range(rbt_node->right, buildingNum1, buildingNum2, result_string);
		}
	}
	return result_string;
}

string BuildingClass::print_active_buildings(int buildingNum1,int buildingNum2){
	string result_string = "";
	string final_result = inorder_traversal_range(root,buildingNum1,buildingNum2,result_string);
	if(final_result.length() != 0){final_result.pop_back();}
	return final_result;
}


