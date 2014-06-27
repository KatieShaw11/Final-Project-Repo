//
//  Trigger.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/23/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "Trigger.h"



bool getNextTriggerDataLine(ifstream& ifstr, string& inputLine) //helper function for reading lines excluding empty lines to make files more readable; to replace getlines
{
    inputLine = "";
    while (inputLine.length()<= 0)
    {
        if(!getline(ifstr, inputLine))
        {
            return false;
        }
    }
    
    return true;
}

string Trigger::toString()
{
    stringstream ss;
    ss << nesCurrentRoomID << endl;
    ss << nesVerb << " " << nesNoun << endl;
    ss << neededRoomItem << " " << neededItem << endl;
    ss << newDescription << endl;
    return ss.str();
}

bool Trigger::readTrigger(ifstream& str)
{
    string inputLine;
    
    if(getNextTriggerDataLine(str, inputLine)) // room ID
    {
        stringstream(inputLine) >> nesCurrentRoomID;
        //cout << "ID: " << nesCurrentRoomID << endl; //testing
    }
    else
        return false;
    
    if(getNextTriggerDataLine(str, inputLine)) // Command
    {
        stringstream(inputLine) >> nesVerb >> nesNoun;
        //cout << "command: verb: "<< nesVerb << " Noun: " << nesNoun << endl; //testing

    }
    else
        return false;
    
    if(getNextTriggerDataLine(str, inputLine)) // item
    {
        neededItem = inputLine;
        //cout << "item: " << neededItem << endl; //testing

    }
    else
        return false;
    
    
    if(getNextTriggerDataLine(str, inputLine)) // room item
    {
        neededRoomItem = inputLine;
        //cout << "roomItem: "  << neededRoomItem << endl; //testing

    }
    else
        
        return false;
    
    
    if(getNextTriggerDataLine(str, inputLine)) // Result
        stringstream(inputLine) >> resultNewDirection >> resultNewRoom;
    else
        return false;

    
    if(getNextTriggerDataLine(str, inputLine)) // New Description
        newDescription = inputLine;
    else
        return false;
    
    if(getNextTriggerDataLine(str, inputLine)) // Trigger Response (what prints out when it's fired)
        trigResponse = inputLine;
    else
        return false;
    
    //cout << name << " " << description << " " << weight << endl; //for testing
    
    return true;
}

bool findInInventory(const vector<string> &Items, long begin, long end, string Item) //RECURSION for searching inventory for whether a needed item for a trigger is in the inventory
{
    if(Items.size()<= 0)
        return false;
    
    //end condition
    
    if (begin == end)
    {
        if (Items[begin] == Item)
            return true;
        else
            return false;
    }
    
    //recursive call
    
    return findInInventory(Items, begin, (begin+end)/2, Item) ||
           findInInventory(Items, 1+(begin+end)/2, end, Item);
}
void Trigger::TEST()
{
    vector <string> tempVec;
    //tempVec.push_back("Apple");
    //tempVec.push_back("Charles");
    //tempVec.push_back("Petre");
    //tempVec.push_back("bob");
    cout<< "Testing: " << findInInventory(tempVec, 0, tempVec.size()-1, "jjj");
}

bool Trigger::checkTTrigger(string Verb, string Noun, vector<string> & InvenItems, vector<string> &RoomItems)
{
    //TESTING
    /*
    cout << "Noun: " << Noun << " Necessary noun: " << nesNoun << endl;
    cout << "Verb: " << Verb << " Necessary verb: " << nesVerb << endl;
    cout << "Needed item: " << neededItem << endl;
    cout << "NeededRoomitem: " << neededRoomItem << endl;
     */
    if (nesVerb.length() > 1) // 1 because I used a single double quote as a placeholder
    {
        if(Verb != nesVerb)
        {
            //cout << "\nreturning false from verb\n"; //testing
            return false;
        }
    }
    else if (neededItem.length()>1) // 1 because I used a single double quote as a placeholder
    {
        if(findInInventory (InvenItems, 0, InvenItems.size()-1, neededItem)==false)
        {
            //cout << "\nreturning false from size\n"; //testing
            return false;
        }
    }
    else if (Noun != nesNoun)
    {
        //cout << "\nreturning false from noun\n"; //testing
        return false;
    }
    else if (neededRoomItem.length()>1) // 1 because I used a single double quote as a placeholder
    {
        if(findInInventory (RoomItems, 0, RoomItems.size()-1, neededRoomItem)==false)
        {
            //FOR TESTING ONLY
            //cout << "Room items:";
            //for (int i = 0; i< RoomItems.size(); i++)
                //cout << "Room item at " << i << ": " << RoomItems[i];
            //cout << "neededRoomItem" << neededRoomItem;
            //cout << "\nreturning false from room inventory\n";
            return false;
        }
    }

    return true;
}


/////////////////////////////////////////// Accessors: //////////////////////////////////////////////

string Trigger::getNewDirection()
{
    return resultNewDirection;
}

int Trigger::getNewRoom()
{
    return resultNewRoom;
}

int Trigger::getNesCurrentRoomID() // necessary location
{
    return nesCurrentRoomID;
}

string Trigger::getNewDescription()
{
    return newDescription;
}
string Trigger::getTrigResponse()
{
    return trigResponse;
}
