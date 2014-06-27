//
//  Room.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/4/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "Room.h"
using namespace std;

bool getNextDataLine(ifstream& ifstr, string& inputLine) //helper function for reading lines excluding empty lines to make files more readable; to replace getlines
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

void Room::parseDirections(string directionLine)
{
    bool word = true; // as opposed to number (index)
    long spaceIndex = 0;
    int tempNum;
    while (true)
    {
        //cout << "parse:\""<<  directionLine << "\"" << endl; //For testing
        
        if (word) //directions
        {
            spaceIndex = directionLine.find(" ");
            adjacentRoomDirections.push_back(directionLine.substr(0, spaceIndex));
            directionLine = directionLine.substr(spaceIndex+1);
        }
        
        if (word == false) //directions indices
        {
            spaceIndex = directionLine.find(" ");
            if(spaceIndex<0)
            {
                stringstream(directionLine) >> tempNum;
                adjacentRooms.push_back(tempNum);
                break;
            }
            stringstream(directionLine.substr(0, spaceIndex)) >> tempNum;
            adjacentRooms.push_back(tempNum);
            directionLine = directionLine.substr(spaceIndex+1);
        }
        
        if (word == true)
            word = false;
        else
            word = true;
    }
    
}

void Room::parseItems(string itemLine)
{
    long spaceIndex = 0;
    if (itemLine != "NO ITEM")
    {
        while (true)
        {
            //cout << "\""<<  itemLine << "\"" << endl; //For testing

            spaceIndex = itemLine.find(" ");
            if(spaceIndex<0)
            {
                items.push_back(itemLine);
                break;
            }
            items.push_back(itemLine.substr(0, spaceIndex));
            itemLine = itemLine.substr(spaceIndex+1);
        }
    }
}

bool Room::readRoomFromFile(ifstream& str)
{
    string inputLine;
    
    if(getNextDataLine(str, inputLine)) // ID#
    {
       stringstream(inputLine) >> ID; // stringstream converts to ints
    }
    else
        return false;
    
    if(getNextDataLine(str, inputLine)) //ITEMS
    {
        parseItems(inputLine);
        //items.push_back(inputLine); For when there was only 1 item per room
    }
    else
        return false;
    
    if(getNextDataLine(str, inputLine)) //DESCRIPTION
        description = inputLine;
    else
        return false;
    
    //int adjacentRoomID;
    string direction;
    if(getNextDataLine(str, inputLine)) //DIRECTIONS
    {
        parseDirections(inputLine);
        //stringstream(inputLine) >> adjacentRoomID >> direction;
        //adjacentRooms.push_back(adjacentRoomID);
        //adjacentRoomDirections.push_back(direction);
        
        /*
        // FOR TESTING:
        cout << "\nROOMS' DIRECTIONS\n";
        cout << "Room ID: " << ID << endl;
        for (int i = 0; i < adjacentRooms.size(); i++)
        {
            cout << adjacentRoomDirections[i] << " " << adjacentRooms[i] << endl;
        }
         */
    }
    else
        return false;
    
    if(getNextDataLine(str, inputLine)) //STATE
    {
        int State;
        stringstream(inputLine) >> State;
        state = State;
    }
       
    else
        return false;
    
    
    
    return true;
}

void Room::saveRoom(ofstream & ofs)
{
    ofs << ID << endl;
    if(items.size()==0)
        ofs << "NO ITEM";
    else
    {
        ofs << items[0];
        for (int i = 1; i < items.size(); i++)
        {
            ofs << " " << items[i];
        }
    }
    
    ofs << endl << description << endl;
    
    if (adjacentRooms.size() <= 0)
        ofs << "";
    else
    {
        ofs << adjacentRoomDirections[0] << " " << adjacentRooms[0];
        for (int i = 1; i < adjacentRoomDirections.size(); i++)
        {
            ofs << " " << adjacentRoomDirections[i] << " " << adjacentRooms[i];
        }
    }
    
    ofs << endl << state << endl;

}

/*
 0
 note axe
 To the east you can see a great lake in the distance, and beyond it a castle. On the north shore you can make out a forest, and to the south you see only rolling grasslands, although you can just see a dark shape on one of the hills. Behind you, to the west, is an insurmountable mountain range.
 east 1
 0
 */

void Room::printRoom()
{
    cout << ID << endl;
    cout << description << endl;
    for (int i = 0; i < items.size(); i++)
    {
        cout << items[i] << endl;
    }
}



bool Room::removeItem(string movingItem)
{
    bool isHere = false;
    
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i] == movingItem)
        {
            isHere = true;
            items.erase(items.begin()+i);
            break;
        }
    }
    return isHere;
}

void Room::addItemToRoom(string movingItem)
{
    items.push_back(movingItem);
}



int Room::go(string Direction)
{
    for (int i = 0; i < adjacentRoomDirections.size(); i++)
    {
        if (adjacentRoomDirections[i] == Direction)
        {
            return adjacentRooms[i];
        }
    }
    return -1;
}



bool Room::checkTrigger(string Verb, string Noun, vector<string> &CarriedItems, vector<Trigger> Triggers) //triggers from main
{
    for (int i = 0; i < Triggers.size(); i++)
    {
        if (Triggers[i].getNesCurrentRoomID() != ID)
            continue; // return to the beginning of the loop; looking for only when the IDs are the same
        
        if (Triggers[i].checkTTrigger(Verb, Noun, CarriedItems, items) == false)
        {
            cout << "\nreturning false from checkTrigger\n";
            
        }
        else
        {
            adjacentRoomDirections.push_back(Triggers[i].getNewDirection());
        
            for (int i = 0; i< adjacentRoomDirections.size(); i++)
                cout << "adjacent room directions: " << adjacentRoomDirections[i] << endl;
        
            adjacentRooms.push_back(Triggers[i].getNewRoom());
        
            for (int i = 0; i< adjacentRooms.size(); i++)
                cout << "adjacent rooms: " << adjacentRooms[i] << endl;
            
            if (Triggers[i].getNewDescription().length() > 1) // 1 b/c I used a single double quote as a placeholder
                description = Triggers[i].getNewDescription();
            
            if(Triggers[i].getTrigResponse().length() > 0)
                cout << Triggers[i].getTrigResponse();
        
            return true;
        }
    }
    return false;
}


/////////////////////////////////////////// Accessors: //////////////////////////////////////////////

int Room::getID()
{
    return ID;
}

int Room::getState()
{
    return state;
}

string Room::getDescription()
{
    stringstream descriptionWithItems;
    descriptionWithItems << description << " Items you see: ";
    for (int i = 0; i < items.size(); i++)
    {
        descriptionWithItems << items[i] << ", ";
    }
    return descriptionWithItems.str();
    //return description;
}
