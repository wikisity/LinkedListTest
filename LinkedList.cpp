/*********************
 * File: LinkedList.cpp
 * Author: Arnold Epanda
 * Date: 9/19/2016
 * Email: behlarnold@gmail.com

 * This c++ file contains LinkedList header file and an implementation
 * of all functions declared in the LinkedList header file. This file
 * basically defines a constructor and a destructor prototyped in LinkedList.h
 * Implement all the  methods declared in LinkedList.h
 ******************/

#include "LinkedList.h"
using namespace std;

//name: LinkedList (default constructor)
//pre: None
//post: new linked list where m_head points to NULL
LinkedList::LinkedList(){
  m_head = NULL;
  m_tail = NULL;
}

//name: LinkedList (destructor)
//pre: There is an existing linked list
//post: A linked list is deallocated (including nodes) to have no memory leaks
LinkedList::~LinkedList(){
  Clear();
}

//name: CreateNode
//pre: Takes in an int and a string
//post: Dynamically creates a new node with a pointer to the next item plus the int
// and string
Node* LinkedList::CreateNode(int newInt, string newPayload){
  Node* a_node = new Node;
  a_node->m_int = newInt;
  a_node->m_payload = newPayload;
  a_node->m_next = NULL;
  return a_node;  
}

//name: InsertEnd
//pre: Takes in an int and a string. Requires a linked list
//post: Adds a new node to the end of the linked list.
void LinkedList::InsertEnd(int newInt, string newPayload){
  if(IsEmpty())
    m_head = CreateNode(newInt, newPayload);
  else{
    Node* newNode = m_head;
    while(newNode->m_next != NULL){
      newNode = newNode->m_next;
    }
    newNode->m_next = CreateNode(newInt, newPayload);
  }
}

//name: Display
//pre: Outputs the linked list (raw or encrypted)
//post: None
void LinkedList::Display(){
  Node* currNode = m_head; //CurrNode and m_head point to the same location
  while(currNode->m_next != NULL){
    cout << currNode->m_payload << "->";
    currNode = currNode->m_next;
  }
  cout << currNode->m_payload << "->" << "END" << endl;
}

//name: Sort
//pre: Takes in a linked list
//post: Sorts the linked list by integer (either raw or decrypted)
void LinkedList::Sort(){
  //LinkedList made of 1 Node
  if(m_head->m_next == NULL)
    cout << "LinkedList sorted" << endl;
  else{
    //LinkedList made of several Nodes
    //Find the length of myLinkedList
    Node* ptrNode = m_head;
    int length = 1;
    while(ptrNode->m_next != NULL){
      ptrNode = ptrNode->m_next;
      length += 1;
    }
    //Find miminum in myLinkedList
    //Insert minimum at the end of a newList
    //delete minimum in old list and rearange it
    int countDeletion = 0;
    Node* newList = NULL; //newList points to the sorted LinkedList
    while(countDeletion < length){
      Node* ptrMin = m_head; //ptrMin points to the minimum
      Node* currPtr = m_head; //currPtr is used to traverse the list
      //Looking for the minimum
      while(currPtr->m_next != NULL){
	currPtr = currPtr->m_next;
	if(ptrMin->m_int > currPtr->m_int)
	  ptrMin = currPtr;
      }
      //Create a newList that will be sorted
      if(newList == NULL)
	newList = CreateNode(ptrMin->m_int, ptrMin->m_payload);
      else{
	Node* temp = newList; //temp is a temporary pointer
	while(temp->m_next != NULL){
	  temp = temp->m_next;
	}
	temp->m_next = CreateNode(ptrMin->m_int, ptrMin->m_payload);
	temp = NULL;
      }
      
      //fixPtr update previous pointer to point to prtMin->next
      //before a Node to which ptrMin points to is deleted
      Node* fixPtr = m_head;
      //Min is located a 1st Node of LinkedList
      if(fixPtr == ptrMin){
	m_head = ptrMin->m_next;
	ptrMin->m_int = 0;
	ptrMin->m_payload = "";
	delete ptrMin;
	ptrMin = NULL;
	currPtr = NULL;
	fixPtr = NULL;
	countDeletion += 1;
      }
      //Min is located at any other position than 1st Node
      else{
	while(fixPtr->m_next != ptrMin)
	  fixPtr = fixPtr->m_next;
	//Min is located at Tail
	if(ptrMin->m_next == NULL){
	  ptrMin->m_int = 0;
	  ptrMin->m_payload = "";
	  delete ptrMin;
	  ptrMin = NULL;
	  currPtr = NULL;
	  fixPtr->m_next = NULL;
	  fixPtr = NULL;
	  countDeletion += 1;
	}
	else{
	  //Min is anywhere in between of LinkedList
	  fixPtr->m_next = ptrMin->m_next;
          ptrMin->m_int = 0;
          ptrMin->m_payload = "";
          delete ptrMin;
          ptrMin = NULL;
          currPtr = NULL;
          fixPtr = NULL;
          countDeletion += 1;
	}
      }
    }
    m_head = newList; //Update m_head to point to the sorted list
    newList = NULL;
  } 
}

//name: IsEmpty
//pre: Takes in a linked list
//post: Checks to see if the linked list is empty or not
bool LinkedList::IsEmpty(){
  bool isEmpty = 1; 
  if(m_head != NULL)
    isEmpty = 0;

  return isEmpty;
}

//name: Decrypt
//pre: Takes in a linked list
//post: Returns a linked list where any nodes where the int is NOT a perfect square
// or perfect cube is thrown out. Also, returns the square root (for perfect squares)
// or cubed root (for perfect cubes).
// For example, "121 candy" goes in - "11 candy" comes out.
LinkedList LinkedList::Decrypt(){
  LinkedList newList;
  Node* currNode = m_head;
  while(currNode != NULL){
    //Current Node is a Perfect square
    //The value of the Node is now the sqrt of the actual value
    if(IsPerfectSquare(currNode->m_int)){
      currNode->m_int = round(sqrt(currNode->m_int));
      newList.InsertEnd(currNode->m_int, currNode->m_payload);
      currNode = currNode->m_next;
    }
    else{
      //Current Node is a Perfect Cube
      //The value of the Node is now the cbrt of the actual value
      if(IsPerfectCube(currNode->m_int)){
	currNode->m_int = round(cbrt(currNode->m_int));
	newList.InsertEnd(currNode->m_int, currNode->m_payload);
	currNode = currNode->m_next;
      }
      else
	//Current Node is not a perfect square and is not a perfect cube
	currNode = currNode->m_next;
    }
  }
 
  return newList;
}

//name: isPerfectSquare
//pre: Takes in an integer
//post: Returns if it is a perfect square or not
bool LinkedList::IsPerfectSquare(int n){
  if(n < 0)
    return false;
  int root(round(sqrt(n)));
  return n == (root * root);
}

//name: isPerfectCube
//pre: Takes in an integer
//post: Returns if it is a perfect cube or not
bool LinkedList::IsPerfectCube(int n){
  if(n < 0)
    return false;
  int root(round(cbrt(n)));
  return n == (root * root * root);
}

//name Clear
//pre: Takes in a linked list
//post: Clears out the linked list (all nodes too)
void LinkedList::Clear(){
  Node* currPtr = m_head;
  while(currPtr->m_next != NULL){
    m_head = currPtr->m_next;
    currPtr->m_int = 0;
    currPtr->m_payload = "";
    delete currPtr;
    currPtr = m_head; 
  }
  currPtr = NULL;
  m_head->m_int = 0;
  m_head->m_payload = "";
  delete m_head;
  m_head = NULL; //At this point the LinkedList is cleared(all Nodes too)
}
