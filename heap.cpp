#include <bits/stdc++.h>
#include "Building.h"
using namespace std;

/* 	Swapping two nodes	*/

void BuildingClass::heap_swap_nodes(HeapNode** parent_ptr,HeapNode** child_ptr){
	    HeapNode* temp = *parent_ptr;
	    *parent_ptr = *child_ptr;
	    *child_ptr = temp;
}

/* 	Recursively Heapifying the heap after comparing parent and child executed times after insertion of node at the bottom	*/

void BuildingClass::heapify(int child_index){
	if(child_index == 0){return;}
	int parent_index = (child_index - 1)/2;
    if(heap[parent_index]->executed_time > heap[child_index]->executed_time){
         heap_swap_nodes(&heap[parent_index],&heap[child_index]);
	     heapify(parent_index);
    }else if(heap[parent_index]->executed_time == heap[child_index]->executed_time){
	     if(heap[parent_index]->buildingNum > heap[child_index]->buildingNum){
	      	heap_swap_nodes(&heap[parent_index],&heap[child_index]);
	        heapify(parent_index);
	     }
	 }
}


/* 		Comparing parent node with its children nodes and swapping the nodes if required		*/

void BuildingClass::min_heapify(int parent_index){
    int left_index = 2*parent_index + 1;
    int right_index = 2*parent_index + 2;
    int swap_index;

/*	 If both left and right child exists	*/
    if(left_index < heap_curr_size && right_index < heap_curr_size){

/*	 parent executed time greater than either of children executed time	*/

        if(heap[parent_index]->executed_time > heap[left_index]->executed_time || heap[parent_index]->executed_time > heap[right_index]->executed_time){

        	if(heap[parent_index]->executed_time > heap[left_index]->executed_time && heap[parent_index]->executed_time > heap[right_index]->executed_time){
        		if(heap[left_index]->executed_time == heap[right_index]->executed_time){
        			swap_index = (heap[left_index]->buildingNum < heap[right_index]->buildingNum)? left_index :right_index;
        		}else{
        			swap_index = (heap[left_index]->executed_time < heap[right_index]->executed_time)? left_index : right_index;
        		}
        		heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
        		min_heapify(swap_index);
        	}else if(heap[parent_index]->executed_time > heap[left_index]->executed_time){
        		swap_index = left_index;
        		heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
          		min_heapify(swap_index);
        	}else if(heap[parent_index]->executed_time > heap[right_index]->executed_time){
        		swap_index = right_index;
        		heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
           		min_heapify(swap_index);
            }

/*	 parent executed time greater than either of children executed time	*/

        }else if(heap[parent_index]->executed_time == heap[left_index]->executed_time || heap[parent_index]->executed_time == heap[right_index]->executed_time){

        	if(heap[parent_index]->executed_time == heap[left_index]->executed_time && heap[parent_index]->executed_time == heap[right_index]->executed_time){

        		if(heap[parent_index]->buildingNum > heap[left_index]->buildingNum && heap[parent_index]->buildingNum > heap[right_index]->buildingNum){
        			swap_index = (heap[left_index]->buildingNum < heap[right_index]->buildingNum) ? left_index : right_index;
        			heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
        			min_heapify(swap_index);
        		}else if(heap[parent_index]->buildingNum > heap[left_index]->buildingNum){
        			swap_index = left_index;
        			heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
        			min_heapify(swap_index);
        		}else if(heap[parent_index]->buildingNum > heap[right_index]->buildingNum){
        			swap_index = right_index;
        			heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
        			min_heapify(swap_index);
        		}

        	}else if(heap[parent_index]->executed_time == heap[left_index]->executed_time){
        		if(heap[parent_index]->buildingNum > heap[left_index]->buildingNum){
        		    swap_index = left_index;
        	     	heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
            		min_heapify(swap_index);
        		}
        	}else if(heap[parent_index]->executed_time == heap[right_index]->executed_time){
        		if(heap[parent_index]->buildingNum > heap[right_index]->buildingNum){
           		    swap_index = right_index;
           		    heap_swap_nodes(&heap[parent_index],&heap[swap_index]);
              		min_heapify(swap_index);
        		}
        	}
        }

/* 	only left child exists and right child doesn't exist in heap	*/

    }else if(left_index < heap_curr_size && right_index >= heap_curr_size){
        if(heap[parent_index]->executed_time > heap[left_index]->executed_time){
            heap_swap_nodes(&heap[parent_index],&heap[left_index]);
            min_heapify(left_index);
        }else if(heap[parent_index]->executed_time == heap[left_index]->executed_time){
        	if(heap[parent_index]->buildingNum > heap[left_index]->buildingNum){
        	    heap_swap_nodes(&heap[parent_index],&heap[left_index]);
                min_heapify(left_index);
        	}
        }

/* 	only right child exists and left child doesn't exist in heap	*/

    }else if(right_index < heap_curr_size && left_index >= heap_curr_size){
        if(heap[parent_index]->executed_time > heap[right_index]->executed_time){
           heap_swap_nodes(&heap[parent_index],&heap[right_index]);
           min_heapify(right_index);
        }else if(heap[parent_index]->executed_time == heap[right_index]->executed_time){
             if(heap[parent_index]->buildingNum > heap[right_index]->buildingNum){
           	    heap_swap_nodes(&heap[parent_index],&heap[right_index]);
                min_heapify(right_index);
             }
        }
    }
}

/* return min value in the heap	*/

HeapNode* BuildingClass::heap_get_min(){
	return heap[0];
}

/* remove min value in the heap	*/

void BuildingClass::heap_remove_min(){
    heap_swap_nodes(&heap[0],&heap[--heap_curr_size]);
    min_heapify(0);

}

/*	Inserting node into a heap	*/

void BuildingClass::heap_node_insert(HeapNode* heapNode){
	int curr_index = heap_curr_size++;
	heap[curr_index] = heapNode;
	heapify(curr_index);
}

/*
 *
 * // Print function to print the heap

string BuildingClass::heap_print(){
	string res;
	for(int i=0;i<heap_curr_size;i++){
	res+= "{" + to_string(heap[i]->buildingNum) + "," + to_string(heap[i]->executed_time) + "," + to_string(heap[i]->total_time) + "}";
	}
	return res;
}
*/


