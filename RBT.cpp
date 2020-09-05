
#include <bits/stdc++.h>
#include "Building.h"
using namespace std;

/* LL rotation */

void BuildingClass::balance_rotate_left(RBT_Node* child, RBT_Node* node_parent){
	RBT_Node* grand_parent = node_parent->parent;
	RBT_Node* temp = child->left;
	if(grand_parent == NULL){
	  root = child;
	  root->parent = NULL;
	  root->red = false;
	  root->left = node_parent;
	  root->right = child->right;
	  child->right->parent = root;
	  node_parent->parent = root;
	}else{
	   if(grand_parent->left == node_parent){
		   grand_parent->left = child;
	   }else{
		   grand_parent->right = child;
	   }
	   child->parent = grand_parent;
	   node_parent->parent = child;
	   child->left = node_parent;
	}
	node_parent->right = temp;
	if(temp != NULL){temp->parent = node_parent;}
}

/* RR rotation */

void BuildingClass::balance_rotate_right(RBT_Node* child, RBT_Node* node_parent){
	RBT_Node* grand_parent = node_parent->parent;
	RBT_Node* temp = child->right;
	if(grand_parent == NULL){
      root = child;
	  root->parent = NULL;
	  root->red = false;
	  root->right = node_parent;
	  root->left = child->left;
	  child->left->parent = root;
	  node_parent->parent = root;
	}else{
		if(grand_parent->left == node_parent){
		  grand_parent->left = child;
		}else{
		  grand_parent->right = child;
	    }
		child->parent = grand_parent;
		node_parent->parent = child;
		child->right = node_parent;
	}
	node_parent->left = temp;
	if(temp != NULL){temp->parent = node_parent;}
}

/* 	Connecting parent node to NULL, so as to delete a node	*/

void BuildingClass::parent_null_link(RBT_Node* rbt_node){
	RBT_Node* parent_node = rbt_node->parent;
	if(parent_node == NULL){root = NULL;return;}
	if(parent_node->left == rbt_node){
		parent_node->left = NULL;
	}else{
		parent_node->right = NULL;
	}
}

/* 	getting parent's other child of given node	*/

RBT_Node* BuildingClass::RBT_get_sibling(RBT_Node* rbt_node){
	return (rbt_node->parent->left == rbt_node) ? rbt_node->parent->right : rbt_node->parent->left;
}

/*		Colour Balancing of a given node after deletion of node		*/

void BuildingClass::RBT_node_balancing(RBT_Node* rbt_node){
	if(rbt_node->parent == NULL){return;}
	if(rbt_node->red == false){
	   RBT_Node* parent_node = rbt_node->parent;
       RBT_Node* sibling = RBT_get_sibling(rbt_node);

/*if current node is left child of parent*/
       if(rbt_node->parent->left == rbt_node){
    	   if(sibling->red == false){

/* sibling is black & no children for sibling */
    	       	if(sibling->left == NULL && sibling->right == NULL){
    	      	   if(parent_node->red == true){
    	  			   parent_node->red = false;
         			   sibling->red = true;
   	       		   }else{
   	       			   sibling->red = true;
   	       			   RBT_node_balancing(parent_node);
   	       		   }
/*	sibling has zero red children	*/
    	       	}else if((sibling->left != NULL && sibling->right != NULL) && (sibling->left->red == false && sibling->right->red == false)){
    	       	   if(parent_node->red == true){
    	   		      parent_node->red = false;
          		      sibling->red = true;
    	       	   }else{
    	       		  sibling->red = true;
   	       		      RBT_node_balancing(parent_node);
    	       	   }
/*	 sibling has one red and its a far child from given node */
    	       	}else if((sibling->left != NULL && sibling->left->red == true) && (sibling->right == NULL || (sibling->right != NULL && sibling->right->red == false))){
     	       	   bool temp = sibling->left->red;
     	           sibling->left->red = sibling->red;
    	       	   sibling->red = temp;
    	       	   balance_rotate_right(sibling->left,sibling);
    	           RBT_node_balancing(rbt_node);
/*  sibling's child towards current node is red child*/
    	        }else if(sibling->right != NULL && sibling->right->red == true){
    	           bool temp = parent_node->red;
    	           parent_node->red = sibling->red;
        	       sibling->red = temp;
        	       balance_rotate_left(sibling,parent_node);
        	       sibling->right->red = false;
    	        }
    	   }else{
/* sibling is red */
    		   bool temp = parent_node->red;
    		   parent_node->red = sibling->red;
    		   sibling->red = temp;
    		   balance_rotate_left(sibling,parent_node);
    		   RBT_node_balancing(rbt_node);
    	   }
/*if current node is right child of parent*/
       }else{
    	   if(sibling->red == false){
/* sibling is black & no children for sibling  */
    	       if(sibling->left == NULL && sibling->right == NULL){
    	      	   if(parent_node->red == true){
    	  			   parent_node->red = false;
    	               sibling->red = true;
    	      	   }else{
             		   sibling->red = true;
    	   			   RBT_node_balancing(parent_node);
    	      	   }
/*	sibling has zero red children	*/
               }else if((sibling->left != NULL && sibling->right != NULL) && (sibling->left->red == false &&  sibling->right->red == false)){
            	   if(parent_node->red == true){
            		   parent_node->red = false;
                       sibling->red = true;
            	   }else{
            		   sibling->red = true;
       	   			   RBT_node_balancing(parent_node);
            	   }
/*	 sibling has one red and its a far child from given node */
               }else if((sibling->right != NULL && sibling->right->red == true) && (sibling->left == NULL || (sibling->left != NULL && sibling->left->red == false))){
            	   bool temp = sibling->right->red;
    	           sibling->right->red = sibling->red;
    	       	   sibling->red = temp;
    	       	   balance_rotate_left(sibling->right,sibling);
    	       	   RBT_node_balancing(rbt_node);
/*  sibling's child towards current node is red child*/
    	       }else if(sibling->left != NULL && sibling->left->red == true){
    	       	   bool temp = parent_node->red;
    	       	   parent_node->red = sibling->red;
    	           sibling->red = temp;
    	           balance_rotate_right(sibling,parent_node);
    	           sibling->left->red = false;
    	       }
/*	 sibling is red		*/
    	   }else{
    	      bool temp = parent_node->red;
    	      parent_node->red = sibling->red;
    	      sibling->red = temp;
    	      balance_rotate_right(sibling,parent_node);
    	      RBT_node_balancing(rbt_node);
    	   }
       }
	}
}

RBT_Node* BuildingClass::RBT_get_inorder_predecessor(RBT_Node* rbt_node){
     return (rbt_node->right == NULL) ? rbt_node : RBT_get_inorder_predecessor(rbt_node->right);
}

/* Binary Search delete from Red-Black Tree */

void BuildingClass::RBT_node_delete(RBT_Node* rbt_node){
	if(rbt_node->left == NULL && rbt_node->right == NULL){
		RBT_node_balancing(rbt_node);
		parent_null_link(rbt_node);
	}else if(rbt_node->left == NULL || rbt_node->right == NULL){
		RBT_Node* duplicate_node = (rbt_node->left == NULL) ? rbt_node->right : rbt_node->left ;
		rbt_node->val = duplicate_node->val;
		rbt_node->heap_node = duplicate_node->heap_node;
		rbt_node->heap_node->rbt_node = rbt_node;
		RBT_node_balancing(duplicate_node);
		parent_null_link(duplicate_node);
	}else{
		RBT_Node* predecessor_node = RBT_get_inorder_predecessor(rbt_node->left);
		rbt_node->val = predecessor_node->val;
		rbt_node->heap_node = predecessor_node->heap_node;
		rbt_node->heap_node->rbt_node = rbt_node;
		RBT_node_delete(predecessor_node);
	}
}

/* 	Changing colour of nodes after rotations	*/

void BuildingClass::change_colours(RBT_Node* rbt_node,RBT_Node* node_child){
	rbt_node->red = false;
	node_child->red = true;
}

/* 	Adjusting Double Red in Red-Black Tree	*/

void BuildingClass::RBT_adjust_colour(RBT_Node* rbt_node){
  if(rbt_node->parent->red == true){
	 RBT_Node* node_parent = rbt_node->parent;
	 RBT_Node* node_uncle = (node_parent->parent->left == node_parent) ? node_parent->parent->right : node_parent->parent->left;
	 if(node_uncle != NULL && node_uncle->red == true){
		 node_parent->red = false;
		 node_uncle->red = false;
		 if(node_parent->parent->parent != NULL){
			node_parent->parent->red = true;
			RBT_adjust_colour(node_parent->parent);
		 }
	 }else{
/* LL Rotation	*/
		 if(node_parent->left == rbt_node && node_parent->parent->left == node_parent){
		 	balance_rotate_right(node_parent,node_parent->parent);
		 	change_colours(node_parent,node_parent->right);
/* RR Rotation	*/
		 }else if(node_parent->right == rbt_node && node_parent->parent->right == node_parent){
	   	    balance_rotate_left(node_parent,node_parent->parent);
	   	    change_colours(node_parent,node_parent->left);
/* LR Rotation	*/
		 }else if(node_parent->right == rbt_node && node_parent->parent->left == node_parent){
    		balance_rotate_left(rbt_node,node_parent);
    		balance_rotate_right(rbt_node,rbt_node->parent);
    		change_colours(rbt_node,rbt_node->right);
/* RL Rotation	*/
	 	 }else if(node_parent->left == rbt_node && node_parent->parent->right == node_parent){
		 	balance_rotate_right(rbt_node,node_parent);
		 	balance_rotate_left(rbt_node,rbt_node->parent);
		 	change_colours(rbt_node,rbt_node->left);
	 	 }
	 }
  }
}

/*	 Checking where new node to be inserted and returning parent	*/

RBT_Node* BuildingClass::RBT_node_parent_search(RBT_Node* rbt_node, int target){
	if(rbt_node->val < target){
		return (rbt_node->right == NULL) ? rbt_node : RBT_node_parent_search(rbt_node->right,target);
	}else{
		return (rbt_node->left == NULL) ? rbt_node : RBT_node_parent_search(rbt_node->left,target);
	}
}

/*	 BST insert into a red-black tree and then checking for double red	*/

void BuildingClass::RBT_node_insert(RBT_Node* rbt_node){
	if(root == NULL){
		rbt_node->red = false;
		root = rbt_node;
		return;
	}
	RBT_Node* parent = RBT_node_parent_search(root, rbt_node->val);
	rbt_node->parent = parent;
	if(parent->val > rbt_node->val){
		parent->left = rbt_node;
	}else{
		parent->right = rbt_node;
	}

	RBT_adjust_colour(rbt_node);
}

/*
 *
 *  // Helper functions to print red-black tree if required

   string BuildingClass::RBT_print_inorder(RBT_Node* rbt_node,string res){
	if(rbt_node == NULL){return "";}
	if(rbt_node->left != NULL){res = RBT_print_inorder(rbt_node->left,res);}
	res +=  to_string(rbt_node->val) + " ";
	if(rbt_node->right != NULL){res = RBT_print_inorder(rbt_node->right,res);}
	return res;
}

string BuildingClass::RBT_print_level_order(string res){
	while(!q.empty()){
		int count = q.size();
		while(count != 0){
			if(q.front()->left != NULL){q.push(q.front()->left);}
			if(q.front()->right != NULL){q.push(q.front()->right);}
			res += to_string(q.front()->val) + " ";
			res += (q.front()->red ) ? "red " : "black ";
			q.pop();
			count--;
		}
		res += "\n";
	}
	return res;
}

string BuildingClass::RBT_print(){
	string res = "";
    return RBT_print_inorder(root,res);
    q.push(root);
   return  RBT_print_level_order(res);
}

*/
