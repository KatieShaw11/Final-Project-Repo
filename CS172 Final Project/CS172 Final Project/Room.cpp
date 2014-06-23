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

void Room::saveRoom()
{
    ofstream saveFile("/Users/katidid/Documents/COMP SCI 172/Final Project/CS172 Final Project/SaveGameFile.txt");
    if (!saveFile.is_open())
    {
        cout << "File does not exist.";
    }
    else
    {
            saveFile << ID << endl;
            for (int i = 0; i < items.size(); i++)
            {
                saveFile << items[i] << endl;
            }
            saveFile << description << endl;
    }
    saveFile.close();
}

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

string Room::getDescription()
{
    stringstream descriptionWithItems;
    descriptionWithItems << description << " Items: ";
    for (int i = 0; i < items.size(); i++)
    {
        descriptionWithItems << items[i] << ", ";
    }
    return descriptionWithItems.str();
    //return description;
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

int Room::getState()
{
    return state;
}
