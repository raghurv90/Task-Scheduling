#include <bits/stdc++.h>
#include "nodeClass.h"
using namespace std;

#ifndef HEAP_H_
#define HEAP_H_

class BuildingClass{
public:

  int heap_curr_size = 0;
  HeapNode* heap[2000];
  RBT_Node* root = NULL;

  void heap_swap_nodes(HeapNode** parent_ptr,HeapNode** child_ptr);

  void heapify(int child_index);

  void min_heapify(int parent_index);

  HeapNode* heap_get_min();

  void heap_remove_min();

  void heap_node_insert(HeapNode* heapNode);

  void balance_rotate_left(RBT_Node* child, RBT_Node* node_parent);

  void balance_rotate_right(RBT_Node* child, RBT_Node* node_parent);

  void change_colours(RBT_Node* rbt_node,RBT_Node* node_child);

  void parent_null_link(RBT_Node* rbt_node);

  RBT_Node* RBT_get_sibling(RBT_Node* rbt_node);

  void RBT_node_balancing(RBT_Node* rbt_node);

  RBT_Node* RBT_get_inorder_predecessor(RBT_Node* rbt_node);

  void RBT_node_delete(RBT_Node* rbt_node);

  void RBT_adjust_colour(RBT_Node* rbt_node);

  void RBT_node_insert(RBT_Node* rbt_node);

  RBT_Node* RBT_node_parent_search(RBT_Node* rbt_node,int target);

  void building_insert(int curr_buildingNum,int curr_executed_time, int curr_total_time);

  void building_delete(RBT_Node* buildingNode);

  RBT_Node* RBT_search_val(RBT_Node* rbt_node, int target_buildingNum);

  HeapNode* get_building_triplet(int buildingNum);

  string print_active_buildings(int buildingNum1,int buildingNum2);

  string inorder_traversal_range(RBT_Node* rbt_node,int buildingNum1,int buildingNum2, string result);

  string update_result(RBT_Node* rbt_node,string result_string);

/*
   // #Print functions used for testing

  queue<RBT_Node*> q;

  string heap_print();

  string RBT_print_inorder(RBT_Node* rbt_node,string res);

  string RBT_print_level_order(string res);

  string RBT_print();

*/
};


#endif /* HEAP_H_ */
