/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of CUBuilding structs to      */
/*     represet communication paths between buildings             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;
/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CUBuildingNetwork::CUBuildingNetwork() {
    /* finished. do not touch. */
    head = NULL;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CUBuildingNetwork::isEmpty()
{
/* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: Add a new building to the network
 *   between the building *previous and the Building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    //If there is no previous building (First building)
    if( (previous == NULL) && (head == NULL)){
        //cout << "NEW ELEMENT " << endl;
        //add building to the beginning of the list
        CUBuilding* building = new CUBuilding;
        building->name = buildingName;
        building->totalRoom = numOfroom;
        building->next = NULL;

        //set the head pointer to first element in linked list
        head = building;

        cout << "adding: " << building->name << " (HEAD) " << endl;

    //It is added at the front and there is already a head
    } else if ( (head != NULL) && (previous == NULL)) {
        //add building to the beginning of the list
        CUBuilding* building = new CUBuilding;
        building->name = buildingName;
        building->totalRoom = numOfroom;
        building->next = head;

        //set the head this building now
        head = building;

        cout << "adding: " << building->name << " (HEAD) " << endl;

    
     //otherwise, it is added in between buildings
    } else if( !(previous->next == NULL) ) {
        //cout << "INSERTING AFTER PREVIOUS ELEMENT " << endl;
        
        //set the values for this building
        CUBuilding* building = new CUBuilding;
        building->name = buildingName;
        building->totalRoom = numOfroom;

        //store the next pointer to the pointer the other building was pointing to as next
        building->next = previous->next;

        //set the next pointer for the previous building to this building
        previous->next = building;


        cout << "adding: " << building->name << " (prev:  " << previous->name << ")" << endl;

    //otherwise, it is after another building AND at the end (next == null)
    } else if (previous->next == NULL) {
        //cout << "INSERTING AT END " << endl;

        //set the values for this building
        CUBuilding* building = new CUBuilding;
        building->name = buildingName;
        building->totalRoom = numOfroom;

        //set the next pointer for the previous building to point to this building
        previous->next = building;

        //Set the next pointer to null (no building after it)
        building->next = NULL;
  
        cout << "adding: " << building->name << " (prev:  " << previous->name << ")" << endl;
    }

    //printNetwork();

}


/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    addBuildingInfo(NULL,"FLMG", 2);
    addBuildingInfo(searchForBuilding("FLMG"),"DLC", 10);
    addBuildingInfo(searchForBuilding("DLC"),"ECOT", 6);
    addBuildingInfo(searchForBuilding("ECOT"),"CASE", 5);
    addBuildingInfo(searchForBuilding("CASE"),"AERO", 4);
    addBuildingInfo(searchForBuilding("AERO"),"RGNT", 9);
    
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    //Search for the building with the string name

    //Set a temporary pointer to the head
    CUBuilding* temp = head;
    CUBuilding* returnPointer = NULL;
    bool found = false;

    //While the value has not been found and the pointer is not null
    while(!found && temp != NULL){
        //Check if the pointer is pointing to the building with the name we specified
        if(temp->name == buildingName){
            found = true;
            returnPointer = temp;

        //otherwise move to the next pointer
        } else {
            temp = temp->next;
        }
    }

    return returnPointer;
}


/*
 * Purpose: Relay messages by traversing the list
 * @param string receiver
 * @param string msg
 */
void CUBuildingNetwork::transmitRoomInfo(string receiver) {
    //Variables
    CUBuilding* curr;
    curr = head;
    bool found = true;

    //No list
    if(isEmpty()){
        cout << "Empty list" << endl;
        found = false;
    } else {
        //No such name
        while(curr->name != receiver){
            if(curr->next == NULL){
                found = false; 
                cout << "Building not found";
                break;
            } else {
                curr = curr->next;
            }
        }
    }
        
    curr = head;
    if(found) {
        //Traverse linked list from head node to node named with name receiver
        while(curr->name != receiver){
            curr->message = "available room at " + curr->name + " is " + to_string(curr->totalRoom);
            curr->numberMessages++;
            cout << curr->name << " [# messages received: " << curr->numberMessages << "] received: " << curr->message << endl;
            curr = curr->next;
        }

        curr->message = "available room at " + curr->name + " is " + to_string(curr->totalRoom);
        curr->numberMessages++;
        cout << curr->name << " [# messages received: " << curr->numberMessages << "] received: " << curr->message << endl;
    }
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    //Variables
    CUBuilding* curr;
    curr = head;
    
    if(head == NULL){
        cout << "== CURRENT PATH == " << endl;
        cout << "nothing in path" << endl;
        cout << "===" << endl;
    } else {
        //Start at head
        cout << "== CURRENT PATH == " << endl;
        while(curr != NULL){
            cout << curr->name << "(" << curr->totalRoom << ") -> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
        cout << "===" << endl;
    }
}
