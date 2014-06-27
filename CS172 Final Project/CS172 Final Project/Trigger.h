//
//  Trigger.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/23/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__Trigger__
#define __CS172_Final_Project__Trigger__

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

#endif /* defined(__CS172_Final_Project__Trigger__) */

class Trigger
{
public:
    
    bool readTrigger(ifstream& str);
    
    void doResult();
    
    int getNesCurrentRoomID(); // necessary location
    string getNesVerb();
    string getNesNoun();
    vector <string> getNeededItems();
    vector <string> getNeededRoomItems();
    string toString();
    string getNewDirection();
    int getNewRoom();
    string getNewDescription();
    string getTrigResponse();
    
    bool checkTTrigger(string Noun, string Verb, vector<string> & InvenItems, vector<string> &RoomItems);

    
    void TEST();
private:
    int nesCurrentRoomID; // necessary location
    string nesVerb;
    string nesNoun;
    string neededItem;
    string neededRoomItem;
    string newDescription;
    string trigResponse;
    
    //int resultRoom;    // I changed it.
    //int resultRoomState;
    
    string resultNewDirection;
    int resultNewRoom;

};

/*
 4
 row boat
 oars
 boat
 5 0
*/