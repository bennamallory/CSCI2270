#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include<fstream>
#include <sstream>

using namespace std;

// MovieNode: node struct that will be stored in the MovieTree BST
MovieNode* getMovieNode(int rank, string t, int y, float r) {
    MovieNode* nn = new MovieNode;
    nn->title = t;
    nn->ranking = rank;
    nn->year = y;
    nn->rating = r;
    return nn;
}

MovieTree::MovieTree() {
  //constructor (initalize member variables of the class to default)
  root = NULL;
}

/*
Purpose: helper function to recursively destruct the entire tree
@param: pointer to the root of the tree
@return: none
*/
void deleteTree(MovieNode *node)
{   
    //Tree is empty (base case)
    if (node == NULL){
      return;
    }

    //recursively call the left subtree
    deleteTree(node->left);

    //recursively call the right subtree
    deleteTree(node->right);

    //delete nodes as they traverse
    delete node;
}

MovieTree::~MovieTree() {
  //destructor -- free all the memory that was allocated
  deleteTree(root);
  
}

/*
Purpose: helper function to recursively traverse through the tree
@param: pointer to the root of the tree
@return: none
*/
void InOrderTraversePrintInv(MovieNode *node)
{
  //if the node is null, return (end of tree or tree is empty)
  if (node == NULL) {
    cout << "Tree is Empty. Cannot print" << endl;
    return;
  }

  //traverse all the way to the left (check helps avoid ends print "tree is empty")
  if(node->left != NULL){
    InOrderTraversePrintInv(node->left);
  }

  //print out the data (root == second)
  cout << "Movie: " << node->title << " " << node->rating << endl;

  //traverse all the way to the right  (check helps avoid ends print "tree is empty")
  if(node->right != NULL){
    InOrderTraversePrintInv(node->right);
  }

}

void MovieTree::printMovieInventory() {
  InOrderTraversePrintInv(root);
}


/*
Purpose: helper function to recursively add movie node
@param: MovieNode * currNode, int ranking, string title, int year, float rating
@return: currNode
*/
MovieNode* addMovieNodeHelper(MovieNode * currNode, int ranking, string title, int year, float rating) {
  //Scenario 1: either the tree is empty (first call to insertHelper)
  //OR when weve reached the appropriate place to add new node
  if(currNode == nullptr){
    //dynamically allocates 1 node and returns ptr to that node
    return getMovieNode(ranking,title,year,rating);
  
  //Case 2 (title is greater than current node value in the alphabet, set right node)
  } else if (title > currNode->title){
      currNode->right = addMovieNodeHelper(currNode->right,ranking,title,year,rating); //entry A
  
  //Case 3 (title is less than current node value in the alphabet, set left node)
  } else if (title < currNode->title){
      currNode->left = addMovieNodeHelper(currNode->left,ranking,title,year,rating); //entry B
  }
  return currNode;
}

void MovieTree::addMovieNode(int ranking, string title, int year, float rating) {
  //send the root and data to the addMovieNodeHelper function
  root = addMovieNodeHelper(root,ranking,title,year,rating);
}



/*
Purpose: helper function to recursively find movie
@param: MovieNode* node, string title
@return: node that movie is found at
*/
MovieNode * findMovieHelper(MovieNode* node, string title){
  //if the node is not null (it is not the end or an empty tree)
  if(node != NULL){
    //check if the node's title is the search key
    if(node->title == title){
      return node;
    
    //check if title is previous in alphabet, if so traverse left
    } else if (title < node->title){
      return findMovieHelper(node->left,title);

    //check if title is later in alphabet, if so traverse right
    } else if (title > node->title) {
      return findMovieHelper(node->right,title);

    //if not found, returns null
    } else {
      return NULL;
    }
  }
  return NULL;
}


void MovieTree::findMovie(string title) {
  //find the movie with given title and print out its information
  MovieNode* foundMovie = findMovieHelper(root,title);
  if(foundMovie == NULL){
    cout << "Movie not found." << endl;
  } else {
    cout << "Movie Info:" << endl;
    cout << "==================" << endl;
    cout << "Ranking:" << foundMovie->ranking << endl;
    cout << "Title  :" << foundMovie->title << endl;
    cout << "Year   :" << foundMovie->year << endl;
    cout << "rating :" << foundMovie->rating << endl;
  }

}


/*
Purpose: helper function to help find and print out specific movie
@param: MovieNode* node, float rating, int year
@return: node 
*/
void queryMoviesHelper(MovieNode* node, float rating, int year){
  //traverse
  //if the node is null, return (end of tree or tree is empty)
  if (node == NULL) {
    cout << "Tree is Empty. Cannot query Movies" << endl;
    return;
  }

  //ROOT
  //print out the data (root)
  if(node->rating >= rating && node->year > year){
      cout << node->title << "(" << node->year << ") " << node->rating << endl;
  }

  //LEFT
  //traverse all the way to the left (check helps avoid ends print "tree is empty")
  if(node->left != NULL){
    queryMoviesHelper(node->left,rating,year);
  }

  //RIGHT
  //traverse all the way to the right  (check helps avoid ends print "tree is empty")
  if(node->right != NULL){
    queryMoviesHelper(node->right,rating,year);
  }

  //return node;
}

void MovieTree::queryMovies(float rating, int year) {
  //print all movies whose rating is at least as good as the input paramter rating and that are newer than year
  //Use PREORDER
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  queryMoviesHelper(root,rating,year);
}


/*
Purpose: helper function to find sum of all nodes
@param: MovieNode* node
@return: sum of all nodes
*/
float sumHelper(MovieNode* node){
  float totalSum = 0;
  
  //TRAVERSE
  //if the node is null, (end of tree or tree is empty)
  if (node == NULL) {
    return 0.0;
  }

  totalSum = node->rating + sumHelper(node->left) + sumHelper(node->right);

  return totalSum;
}


/*
Purpose: helper function to find the number of nodes
@param: MovieNode* node
@return: count of all nodes
*/
int numNodesHelper(MovieNode* node){
  int totalNodes = 1;
  
  //TRAVERSE
  //if the node is null, (end of tree or tree is empty)
  if (node == NULL) {
    return 0;
  }

  totalNodes = totalNodes + numNodesHelper(node->left) + numNodesHelper(node->right);

  return totalNodes;
}


void MovieTree::averageRating() {
  float sum = sumHelper(root);
  //cout << "SUM " << sum << endl;
  int numNodes = numNodesHelper(root);
  //cout << "numNODES " << numNodes << endl;
  float averageRate = sum/numNodes;

  if(sum == 0.0){
    cout << "Average rating:0.0" << endl;
  } else {
    cout << "Average rating:" << averageRate << endl;
  }

}

/*
Purpose: helper function to recursively find nodes at a particular level
@param: MovieNode* node, int level
@return: none
*/
void printLevelNodesHelper(MovieNode* node, int level){
  //if tree is empty (return null, if traverse too far, return null)
  if(node == NULL){
    return;
  }

  //base case -- iterate down in depth until you reach correct level and print
  if(level == 0){
    cout << "Movie: " << node->title << " " << node->rating << endl;
  } else {
    //recursive calls to find nodes at proper depth
    printLevelNodesHelper(node->left,level-1);
    printLevelNodesHelper(node->right,level-1);
  }
}

void MovieTree::printLevelNodes(int level) {
  //print all nodes in the tree from left to right that are exactly at depth = k from root
  //if level is more than max depth, just exit
  printLevelNodesHelper(root,level);
}
