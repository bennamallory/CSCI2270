#include <iostream>
#include <fstream>
#include "MovieTree.hpp"

using namespace std;

LLMovieNode* getLLMovieNode(int r, std::string t, int y, float q)
{
	LLMovieNode* lmn = new LLMovieNode();
	lmn->ranking = r;
	lmn->title=t;
	lmn->year =y;
	lmn->rating =q;
	lmn->next =NULL;
	return lmn;
}
/* ------------------------------------------------------ */
MovieTree::MovieTree()
{
	root = NULL;
}
/* ------------------------------------------------------ */

/*
Purpose: helper function to recursively destruct the entire tree
@param: pointer to the root of the tree
@return: none
*/
void deleteTreeHelper(TreeNode *node){
	//Tree is empty (base case)
    if (node == NULL){
      return;
    }

    //recursively call the left subtree
    deleteTreeHelper(node->leftChild);

    //recursively call the right subtree
    deleteTreeHelper(node->rightChild);

	//once you reach the node, make sure to deallocate associated linked list

	//create a crawler to help deletion
	LLMovieNode* crawler;

	//while the head of the list is not null, delete
    while(node->head != NULL){
        //cout << "deleting: " << node->head->title << endl;
        crawler = node->head->next;
        delete node->head;
        node->head = crawler;
    }

    //delete node after deleting LL
    delete node;
}

MovieTree::~MovieTree()
{
	//deallocate memory of each tree node and LL
	deleteTreeHelper(root);

}

void _grader_inorderTraversal(TreeNode * root) {
	if (root == NULL) {
		return;
	}

	_grader_inorderTraversal(root->leftChild);
	cout << root->titleChar << " ";
	_grader_inorderTraversal(root->rightChild);
}


void MovieTree::inorderTraversal() {
	_grader_inorderTraversal(root);
	cout << endl;
}

TreeNode* searchCharHelper(TreeNode* curr, char key)
{
    if (curr == NULL)
        return curr;
    else if(curr->titleChar == key)
        return curr;
    else if (curr->titleChar > key)
        return searchCharHelper(curr->leftChild, key);
    else
        return searchCharHelper(curr->rightChild, key);
}


TreeNode* MovieTree::searchCharNode(char key)
{
    return searchCharHelper(root, key);
}

/*
Purpose: helper function to recursively print the movies in alphabetical order of titles
@param: pointer to the root of the tree
@return: none
*/
void showMovieCollHelper(TreeNode* node){
	//print every movie in the data structure in alphabetical order of titles 
	if (node == NULL) {
		return;
	}

	//start at the root and traverse to left most node, print LL for each node
	showMovieCollHelper(node->leftChild);
	cout << "Movies starting with letter: " << node->titleChar << endl;
	
	//traverse LL
	LLMovieNode* crawler = node->head;
	while(crawler != NULL){
		cout << " >> " << crawler->title << " " << crawler->rating << endl;
		crawler = crawler->next;
	}

	//traverse to right
	showMovieCollHelper(node->rightChild);
}

void MovieTree::showMovieCollection(){
	showMovieCollHelper(root);
}

/* ---------------------INSERT MOVIE && HELPER FUNCTIONS --------------------------------- */

TreeNode* getTreeNode(char tChar, LLMovieNode* movie)
{
	TreeNode* newTreeNode = new TreeNode();
	newTreeNode->head = movie;
	newTreeNode->leftChild = NULL;
	newTreeNode->rightChild = NULL;
	newTreeNode->titleChar = tChar;
	newTreeNode->parent = NULL;
	return newTreeNode;
}

/*
Purpose: helper function to recursively find movie
@param: TreeNode* node, char findTitleChar
@return: node that has a particular first character
*/
TreeNode* findNode(TreeNode* node, char findTitleChar){
  //if the node is not null (it is not the end or an empty tree)
  if(node != NULL){
    //check if the node's title is the search key
    if(node->titleChar == findTitleChar){
      return node;
    
    //check if title is previous in alphabet, if so traverse left
    } else if (findTitleChar < node->titleChar){
      return findNode(node->leftChild,findTitleChar);

    //check if title is later in alphabet, if so traverse right
    } else if (findTitleChar > node->titleChar) {
      return findNode(node->rightChild,findTitleChar);

    //if not found, returns null
    } else {
      return NULL;
    }
  }
  return NULL;
}


/*
Purpose: helper function to recursively add a tree node
@param: TreeNode* currNode, int ranking, string title, int year, float rating
@return: currNode (root)
*/
TreeNode* insertNodeHelper(TreeNode* currNode, int ranking, string title, int year, float rating) {
  char insertTitleChar = title.at(0);
  
  //Scenario 1: either the tree is empty (first call to insertHelper)
  //OR when weve reached the appropriate place to add new node
  if(currNode == nullptr){
    //dynamically allocates 1 node and returns ptr to that node

	//create a node for the new Movie (LL)
	LLMovieNode* newMovieNode = getLLMovieNode(ranking,title,year,rating);

	//create a new node for the tree
    return getTreeNode(insertTitleChar,newMovieNode);
  
  //Case 2 (title is greater than current node value in the alphabet, set right node)
  } else if (insertTitleChar > currNode->titleChar){
	  TreeNode* rightChild = insertNodeHelper(currNode->rightChild,ranking,title,year,rating);
      currNode->rightChild = rightChild;
	  rightChild->parent = currNode;
  
  //Case 3 (title is less than current node value in the alphabet, set left node)
  } else if (insertTitleChar < currNode->titleChar){
	  TreeNode* leftChild = insertNodeHelper(currNode->leftChild,ranking,title,year,rating);
      currNode->leftChild = leftChild;
	  leftChild->parent = currNode;
  }
  return currNode;
}

void insertLLNode(TreeNode* node,int ranking, string title, int year, float rating){
	//create the movie node for LL
	LLMovieNode* insertNode = getLLMovieNode(ranking,title,year,rating);

	//if the head is null, add this node as the head of LL
	if(node->head == NULL){
		node->head = insertNode;
	
	//Check to see if inserting at the front of the list
	} else if(insertNode->title < node->head->title){
		//insert at the head of the list and update head
		insertNode->next = node->head;
		node->head = insertNode;
		
	//Inserting in middle or at end
	//Find the afterMe pointer to find correct placement 
	} else {
		//traverse to find the correct spot to insert  -- find afterMe pointer
		LLMovieNode* afterMe = node->head;

		//find afterMe
		//checking if afterMe is not null and insertNode is alphabetical
		while(afterMe->next != NULL && !(insertNode->title > afterMe->title && insertNode->title < afterMe->next->title)){
			afterMe = afterMe->next;
		}

		//inserting node
		//set insertNode's next to the pres node
		insertNode->next = afterMe->next;

		//set the prev node to point to inserted node
		afterMe->next = insertNode;
	}
}

void MovieTree::insertMovie(int ranking, string title, int year, float rating){
	char insertTitleChar = title.at(0);
	
	//Find node with same first letter as title
	TreeNode* foundNode = findNode(root,insertTitleChar);

	//if the node is NULL, it was not found, need to add node
	if(foundNode == NULL){
		//insert new node
		root = insertNodeHelper(root,ranking,title,year,rating);
	
	//otherwise, you found the node, add movie to the LL
	} else {
		insertLLNode(foundNode,ranking,title,year,rating);
	}

}
/* --------------------- ^^^^ INSERT MOVIE HELPER FUNCTIONS ^^^ --------------------------------- */




/* ---------------------REMOVE MOVIE HELPER FUNCTIONS ------------------------------------------- */

LLMovieNode* findMovieRecordLL(TreeNode* node, string title){
    //Set a temporary pointer to the head
    LLMovieNode* temp = node->head;
    LLMovieNode* returnPointer = NULL;
    bool found = false;

    //While the value has not been found and the pointer is not null
    while(!found && temp != NULL){
        //Check if the pointer is pointing to the movie with the name we specified
        if(temp->title == title){
            found = true;
            returnPointer = temp;
			//cout << returnPointer->title << endl;

        //otherwise move to the next pointer
        } else {
            temp = temp->next;
        }
    }

    return returnPointer;
}

TreeNode* getMinValueNode(TreeNode* currNode){

    if(currNode->leftChild == NULL){
      return currNode;
    }
    return getMinValueNode(currNode->leftChild);
}

// This function deletes the Node with 'titleChar' as it's key.
TreeNode* deleteNode(TreeNode *currNode, char titleChar){

  if(currNode == NULL) {
    return NULL;

  } else if(titleChar < currNode->titleChar) {
    currNode->leftChild = deleteNode(currNode->leftChild, titleChar);
	//currNode->leftChild->parent = currNode;

  } else if(titleChar > currNode->titleChar) {
    currNode->rightChild = deleteNode(currNode->rightChild, titleChar);
	//currNode->rightChild->parent = currNode;
  
  // We found the node with the value
  } else {
    //No child
    if(currNode->leftChild == NULL && currNode->rightChild == NULL) {
        //delete the node
        delete currNode;

        //return null to replace its value for the root linked to it above
        return NULL;
    
	//Only right child
	} else if(currNode->leftChild == NULL) {
        //store the right child of the node to be deleted
        TreeNode* p_right = currNode->rightChild;
		p_right->parent = currNode->parent;

        //delete the current node
        delete currNode;

        //link the right node to the root of the node we deleted (links back together)
        return p_right;

	//TODO Case : Only left child 
	} else if(currNode->rightChild == NULL){
       //store the left child of the node to be deleted
        TreeNode* p_left = currNode->leftChild;
		p_left->parent = currNode->parent;

        //delete the current node
        delete currNode;

        //link the left node to the root of the node we deleted (links back together)
        return p_left;

	//Both left and right child
    } else {
		///Replace with Minimum from right subtree
		//store the minimum from right subtree (will use to replace currNode)
		TreeNode* r_s_m = getMinValueNode(currNode->rightChild);
		
		//change the value of the currNode 
		currNode->titleChar = r_s_m->titleChar;
		currNode->head = r_s_m->head;

		//delete the r_s_m node instead of the actual node to be deleted (already changed its value)
		//go to the right subtree and find r_s_m node to delete (call deleteNode to catch cases above)
		currNode->rightChild = deleteNode(currNode->rightChild,r_s_m->titleChar);
    }
  }
	return currNode;
}

void deleteMovieNodeLL(TreeNode* node, string title){
	string headTitle = node->head->title;
	
	//check if it is head
	if(title == headTitle){
		//set the head pointer to the next node
		LLMovieNode* oldHead = node->head;

		if(node->head->next == NULL){
			node->head = NULL;
		} else {
			node->head = node->head->next;
		}
		//delete the node
		delete oldHead;

	//Not the head, traverse to find and delete
	} else {
		//delete the node
		bool found = true;
		LLMovieNode* crawler = node->head;
		LLMovieNode* deleteNode = node->head->next;

		while(deleteNode->title != title){
			if(deleteNode->next == NULL){
				found = false;
				break;
			} else {
				found = true;
				crawler = crawler->next;
				deleteNode = deleteNode->next;
			}
		}

		//if we found the node, set the previous node to the one after delete node
		if(found){
			crawler->next = deleteNode->next;
			delete deleteNode;
		}
	}
}


void MovieTree::removeMovieRecord(string title){
	//find node with title char
	char insertTitleChar = title.at(0);
	TreeNode* foundNode = findNode(root,insertTitleChar);

	//Node with that char doesn't exist
	if(foundNode == NULL){
		cout << "Movie not found." << endl;
	} else {
		//find the LLNode within this tree node
		LLMovieNode* foundMovieNode = findMovieRecordLL(foundNode,title);

		//Movie does not exist
		if(foundMovieNode == NULL){
			cout << "Movie not found." << endl;

		//found the movie
		} else {
			//delete the node of the LL
			deleteMovieNodeLL(foundNode,title);

			//check to see if it results in an empty LL (if so, replace tree node with min of right subtree)
			if(foundNode->head == NULL){
				//delete the tree node
				root = deleteNode(root,insertTitleChar);
			}
		}
	}
}

/* --------------------- ^^ REMOVE MOVIE HELPER FUNCTIONS ^^  ----------------------------------- */






/* --------------------- LEFT ROTATION HELPER FUNCTIONS ------------------------------------------- */

//WHEN X IS ROOT

void MovieTree::leftRotation(TreeNode* curr){	
	//rotate the node curr left
	TreeNode* x = curr;
	TreeNode* xp = curr->parent;
	TreeNode* y = curr->rightChild;
	bool isRoot = false;


	//check if x is root
	if(x->parent == NULL){
		//x is root, make y root
		//cout << "x is root" << endl;
		root = y;
		isRoot = true;
	}

	//check if x has right child -- if not, no rotations
	if(x->rightChild != NULL){
		//set parent pointers
		//parent of x becomes the parent of y
		y->parent = xp;

		//parent of x becomes y
		x->parent = y;

		//Set the subtree pointers
		//left subtree of y becomes right subtree of x
		if(y->leftChild != NULL){
			x->rightChild = y->leftChild;
			x->rightChild->parent = x;
		} else {
			x->rightChild = NULL;
		}

		//x and its descendants become left subtree of y
		y->leftChild = x;

		//if x was the left subtree of xp, make y the left subtree of x
		if(!isRoot){
			if(xp->leftChild == x){
				xp->leftChild = y;

			//if x was the right subtree of xp, make y the right subtree of x
			} else if (xp->rightChild == x){
				xp->rightChild = y;
			}
		}
	}
}

/* --------------------- ^^ LEFT ROTATION HELPER FUNCTIONS ^^  ----------------------------------- */
