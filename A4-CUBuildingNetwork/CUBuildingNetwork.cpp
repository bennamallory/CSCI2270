/****************************************************************/
/*                CUBuildingNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CUBuildingNetwork */
/*     This class uses a linked-list of Building structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CUBuildingNetwork.hpp"
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
 * Purpose: Add a new building to the network between the building *previous and the building that follows it in the network.
 * @param previous name of the Building that comes before the new Building
 * @param buildingName name of the new Building
 * @param numOfroom
 * @return none
 */
void CUBuildingNetwork::addBuildingInfo(CUBuilding* previous, string buildingName, int numOfroom) {
    // if we are passed an empty list, just create a new head node, and return

    if (head == NULL)
    {
        cout << "adding: " << buildingName << " (HEAD)" << endl;
        head = new CUBuilding;
        head->name = buildingName;
        head->numberMessages = 0;
        head->totalRoom = numOfroom;

        head->next = NULL;
    }
    // if it's not empty, we need to search for previous and append our node there.
    else if(previous == NULL )
    {
        cout << "adding: " <<buildingName<< " (HEAD)" << endl;
        CUBuilding *c = new CUBuilding;
        c->name = buildingName;
        c->numberMessages = 0;
        c->next = head;
        c->totalRoom = numOfroom;

        head = c;
    }else{
        cout << "adding: " << buildingName << " (prev: " << previous->name << ")" << endl;
        CUBuilding *newBuilding = new CUBuilding;
        newBuilding->name = buildingName;
        newBuilding->numberMessages = 0;
        newBuilding->next = previous->next;
        newBuilding->totalRoom = numOfroom;

        previous->next = newBuilding;
    }
}

/*
 * Purpose: populates the network with the predetermined buildings
 * @param none
 * @return none
 */
void CUBuildingNetwork::loadDefaultSetup()
{
    int num_buildings = 6;
    string buildings[] = {"FLMG", "DLC", "ECOT", "CASE", "AERO", "RGNT"};
    int rooms[] = {2,10,6,5,4,9};
    head = NULL;
    CUBuilding* prev = NULL;
    for(int i = 0; i < num_buildings; i++)
    {
        addBuildingInfo(prev, buildings[i],rooms[i]);
        prev = searchForBuilding(buildings[i]);
    }
}

/*
 * Purpose: Search the network for the specified building and return a pointer to that node
 * @param buildingName name of the building to look for in network
 * @return pointer to node of buildingName, or NULL if not found
 *
 */
CUBuilding* CUBuildingNetwork::searchForBuilding(string buildingName)
{
    // Search until the head is NULL, or we find the building
    CUBuilding* ptr = head;
    while (ptr != NULL && ptr->name != buildingName)
    {
        ptr = ptr->next;
    }
    // Return the node, or NULL
    return ptr;
}

/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CUBuildingNetwork::printNetwork() {
    cout << "== CURRENT PATH ==" << endl;
    // If the head is NULL
    CUBuilding* ptr = head;
    if (ptr == NULL)
        cout << "nothing in path" << endl;

    // Otherwise print each node, and then a NULL
    else
    {
        while (ptr != NULL)
        {
            cout << ptr->name << "(" << ptr->totalRoom << ")" <<" -> ";
            ptr = ptr->next;
        }
        //cout << ptr->name << " -> ";
        cout << "NULL" << endl;
    }
    cout << "===" << endl;
  }

/*
 * Purpose: delete the building in the network with the specified name.
 * @param buildingName name of the building to delete in the network
 * @return none
 */
void CUBuildingNetwork::deleteCUBuilding(string buildingName) {
    //TODO: Complete this function
    bool found = true;

    //Check if the node is the head
    string headName = head->name;
    
    if(buildingName == headName){
        //set the head pointer to the next node
        found = true;
        CUBuilding* oldHead = head;
        head = head->next;

        //delete the node
        delete oldHead;

    } else {
        //traverse list to find node with buildingName
        CUBuilding* crawler = head;
        CUBuilding* deleteNode = head->next;

        //search and stop at node
        while(deleteNode->name != buildingName){
            //if you are at the last node and it is not the last
            if(deleteNode->next == NULL){
                found = false;
                break;
            } else {
                found = true;
                crawler = crawler->next;
                deleteNode = deleteNode->next;
            }
        }

        if(found){
            //set the current node to point to the node after the deleted node
            crawler->next = deleteNode->next;

            //delete the node
            delete deleteNode;
        }

    }

    if(found == false){
        cout << "Building does not exist." << endl;
    }

}

/*
* Purpose: Creates a loop from last node to the building specified.
* @param buildingName name of the building to loop back
* returns the last node before loop creation (to break the loop)
*/
CUBuilding* CUBuildingNetwork::createLoop(string buildingName) {
    //Variables
    CUBuilding* lastNode = head;
    CUBuilding* intNode = head;
    bool found = true;

    //Find last node
    while(lastNode->next != NULL){
        lastNode = lastNode->next;
    }

    //Find intermediate node
    while(intNode->next != NULL){
        //if find the intermediate node, stop the search
        if(intNode->name == buildingName){
            found = true;
            break;
        //otherwise not found
        } else {
            found = false;
            intNode = intNode->next;
        }
    }


    //If you found the intermediate, link the last node to it
    if(found && lastNode != intNode){
        lastNode->next = intNode;
    //otherwise return the last node
    } else if(lastNode == intNode) {
        lastNode->next = lastNode; 
        return lastNode;
    } else {
        return lastNode;
    }
    
}

/*
 * Purpose: deletes all buildings in the network starting at the head building.
 * @param: none
 * @return: none
 */
void CUBuildingNetwork::deleteEntireNetwork()
{
    //Delete every node in the linked list and set the head to NULL
    //Print each node you are deleting as you delete
    CUBuilding* crawler;
    while(head != NULL){
        cout << "deleting: " << head->name << endl;
        crawler = head->next;
        delete head;
        head = crawler;
    }

    cout << "Deleted network" << endl;
}

/*
 * Purpose: to detect loop in the linkedlist
 * @return: true if loop is detected.
 */
bool CUBuildingNetwork::detectLoop() {
    //TODO: Complete this function
    CUBuilding* crawler = head;
    bool isLoop = false;

    //REFERENCE: https://www.youtube.com/watch?v=MFOAbpfrJ8g (from writeup)
    //If no list
    if(head == NULL){
        return false; 

    //Detect loop in the list
    } else {
        CUBuilding* fast = head->next;
        CUBuilding* slow = head;

        //Traverse through list to identify if a cycle is present
        while(fast != NULL && fast->next != NULL && slow != NULL){
            //If at the same node, we know it is cycle
            if(fast == slow){
                isLoop = true;
                return isLoop;
            }
            fast = fast->next->next;
            slow = slow->next;

        }
        isLoop = false;

    }

    return isLoop;
    
}

/*
 * Purpose: Take the chunk of nodes from start index to end index
 *          Move that chunk at the end of the List
 * @param: start index, end index
 * @return: none
 */
void CUBuildingNetwork:: readjustNetwork(int start_index, int end_index)
{
    //List is empty
    if(head == NULL){
        cout << "Linked List is Empty" << endl;
    } else {
            
        //Count the number of nodes -- counting 
        CUBuilding* crawler = head;
        int maxIndex = 0;
        while(crawler->next != NULL){
            maxIndex++;
            crawler = crawler->next;
        }

        //end smaller than zero, larger than number of nodes, larger than index of last element
        if(end_index < 0 || end_index > maxIndex+1 || end_index >= maxIndex){
            cout << "Invalid end index" << endl;

        //start larger than the max index, smaller than zero 
        } else if(start_index > maxIndex || start_index < 0){
            cout << "Invalid start index" << endl;

        //start larger than end
        } else if(start_index > end_index){
            cout << "Invalid indices" << endl;

        //Perform the switch
        } else {

            //If start index is the head
            if(start_index == 0){
                CUBuilding* endNode = head;
                CUBuilding* startNode = head;

                //traverse to the end node
                for(int j=0; j < end_index; j++){
                    endNode = endNode->next;
                }

                //find the end of the list
                CUBuilding* endList = head;
                while(endList->next != NULL){
                    endList = endList->next;
                }
                
                //set the end list node to point the start_index node
                endList->next = startNode;
                
                //set new head to endList node
                head = endNode->next;
                
                //set endNode to null
                endNode->next = NULL;



            //Not the start index
            } else {
                //find the start node and end node
                CUBuilding* prevStart = head;
                CUBuilding* startNode = head->next;
                CUBuilding* endNode = head;
                CUBuilding* endList = head;
                

                //find start node and the node before it
                for(int k=0; k < start_index-1; k++){
                    prevStart = prevStart->next;
                    startNode = startNode->next;
                }

                //find end node
                for(int m=0; m < end_index; m++){
                    endNode = endNode->next;
                }

                //find the end of the list
                while(endList->next != NULL){
                    endList = endList->next;
                }

                //set node before the start node to the node after the end node
                prevStart->next = endNode->next;

                //set end to start of new
                endList->next = startNode;

                //set endNode to null
                endNode->next = NULL;
            
            }
        }
    }

}
