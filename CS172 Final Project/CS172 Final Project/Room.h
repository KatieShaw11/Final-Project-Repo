//
//  Room.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/4/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__Room__
#define __CS172_Final_Project__Room__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Item.h"
#include "InventoryS.h"
#include "Trigger.h"
using namespace std;


class Room
{
private:
    int ID;
    vector <string> items;
    string name;
    string description;
    vector<int> adjacentRooms;
    vector<string> adjacentRoomDirections;
    void parseItems(string);
    void parseDirections(string directionLine);
    int state; // 0: normal,unlocked; 1: "locked"
    
public:
    bool removeItem(string item); // checks if item is in room and removes it if it is (to be placed in inventory, NOT included)
    bool readRoomFromFile(ifstream& str);
    void printRoom();
    void saveRoom(ofstream & ofs);
    string getDescription();
    int getState();
    void addItemToRoom(string movingItem);
    
    bool checkTrigger(string Verb, string Noun, vector<string> &CarriedItems, vector<Trigger> Triggers);
    
    int go(string Direction); // moves between rooms
    int getID();

};

#endif /* defined(__CS172_Final_Project__Room__) */
