#include <bits/stdc++.h>
using namespace std;

#ifndef NODECLASS_H_
#define NODECLASS_H_

class RBT_Node;

/*
	Initializing a node class for a Heap node.
*/

class HeapNode{
public:
	int buildingNum;
    int executed_time;
    int total_time;
    RBT_Node* rbt_node;

    HeapNode();

    HeapNode(int curr_buildingNum,int curr_executed_time,int curr_total_time){
        buildingNum = curr_buildingNum;
        executed_time = curr_executed_time;
        total_time = curr_total_time;
    	rbt_node = NULL;
    }
};

/*
	Initializing a node class for a Red-Black tree node.
*/

class RBT_Node{
public:
	int val;
	bool red;
	RBT_Node* left;
	RBT_Node* right;
	RBT_Node* parent;
	HeapNode* heap_node;

	RBT_Node();

	RBT_Node(int buildingNum){
		val = buildingNum;
		red = true;
		left = NULL;
		right = NULL;
		parent = NULL;
		heap_node = NULL;
	}
};




#endif /* NODECLASS_H_ */
