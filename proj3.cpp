/*********************
 * File: proj3.cpp
 * Project: CMSC 202 Project 3, Fall 2016
 * Author: Arnold Epanda
 * Date: 9/19/2016
 * Section 4
 * Email: aepanda1@umbc.edu

 * This c++ file inlcudes LinkedList.h, proj3.h files and an implementation
 * of all functions declared in the proj3.h file. This project aims to
 * implement a game called 'spy game' which is basically an application that
 * can read a file and decrypt its hidden message. A file contains unknown  
 * number of messages and a message is made up of an integer and a string. 
 * One goal is to figure out which message is 'fake' and which one is 'real'. 
 * Also I don't know how long a message will be, then I decided to use a 
 * LinkedList as data structure to save and process the message. I aim to display
 * a real clue/decrypt message and a real clue is simply message(where the numbers 
 * made of perfect square and perfect cube have been sorted)
 ******************/

#include "LinkedList.h"
#include "proj3.h"

int main () {
  LinkedList list;
  mainMenu(list);
  return 0;
}

void readFile(LinkedList &list){
  char fileName[] = ""; //Variable to save a file name
  int num;//Variable to save a messgae's number
  string message; //To save my message
  fstream iStream; //File object to manipulate files

  if(list.IsEmpty()){
    cout << endl;
    cout << "What is the file name?:" << endl;
    cin >> fileName;
    iStream.open(fileName);
    if(iStream){
      //File is open
      while(iStream >> num){
        iStream >> message;
        list.InsertEnd(num, message);
      }
      cout << "New message loaded" << endl;
      iStream.close();
    }
    //File does not exist
    else
      cout << "Message load failed" << endl;

  }
  else{
    //A message was loaded, Prompt user for options
    int choice = 0; //User options
    bool isExit = 0; //Once User makes a choice then exit
    do{
      do{
	cout << endl;
	cout << "Do you want to: " << endl;
	cout << "1. Overwrite the message" << endl;
	cout << "2. Append the message" << endl;
	cout << "3. Cancel" << endl;
	cin >> choice;
      }while(choice < 1 || choice > 3);

      switch(choice){
      case 1:
	list.Clear();
	cout << endl;
	cout << "Previous message cleared" << endl;
	cout << "What is the file name?:" << endl;
	cin >> fileName;
	iStream.open(fileName);
	if(iStream){
	  while(iStream >> num){
	    iStream >> message;
	    list.InsertEnd(num, message);
	  }
	  cout << "New Message loaded" << endl;
	  iStream.close();
	}
	else{
	  cout << "Message load failed" << endl;
	}
	isExit = 1;
	break;

      case 2:
	cout << endl;
	cout << "What is the file name?:" << endl;
        cin >> fileName;
	iStream.open(fileName);
        if(iStream){
          while(iStream >> num){
            iStream >> message;
            list.InsertEnd(num, message);
          }
          cout << "Message appended" << endl;
          iStream.close();
        }
        else{
          cout << "Message load failed" << endl;
	}
	isExit = 1;
	break;
	
      case 3:
	isExit = 1;
      }

    }while(isExit == 0);
  }
}

void mainMenu(LinkedList &list){
  int option = 0;
  bool isExit = 0;
  do {
    do {
      cout << endl;
      cout << "What would you like to do?: " << endl;
      cout << "1. Load a new encrypted message" << endl;
      cout << "2. Display a raw message" << endl;
      cout << "3. Display an encrypted message" << endl;
      cout << "4. Exit" << endl;
      cin >> option;
    }while(option < 1 || option > 4);

    switch(option){
      
    case 1:
      readFile(list);
      break;
    case 2:
      displayMessage(list);
      break;
      
    case 3:
      displayEncrypt(list);
      break;
      
    case 4:
      exitLinked(list);
      isExit = 1;
    }
  }while(isExit == 0);
}

void displayMessage(LinkedList &list){
  if(list.IsEmpty())
    cout << "You have not loaded an Encrypted message yet." << endl;
  else{
    cout << endl;
    cout << "Payload of list are: " << endl;
    list.Display();
    list.Sort();
    cout << endl;
    cout << "Paylaod of list are: " << endl;
    list.Display();
  }
}

void exitLinked(LinkedList &list){
  cout << endl;
  cout << "Have a nice day!" << endl;
}

void displayEncrypt(LinkedList &list){
  if(list.IsEmpty())
    cout << "You have not loaded an Encrypted message yet." << endl;
  else{
    cout << endl;
    cout << "Payload of list are: " << endl;
    LinkedList list2 = list.Decrypt();
    list2.Sort();
    list2.Display();
  }
}

