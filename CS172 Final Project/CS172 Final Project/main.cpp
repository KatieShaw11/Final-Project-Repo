//
//  main.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/4/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include <vector>
#include "Item.h"
#include "Room.h"

#define FILENAME "/Users/katidid/Documents/COMP SCI 172/Final Project Repo/CS172 Final Project/Rooms test.txt"
#define INVENFILENAME "/Users/katidid/Documents/COMP SCI 172/Final Project Repo/CS172 Final Project/Full Inventory.txt"
#define TRIGFILENAME "/Users/katidid/Documents/COMP SCI 172/Final Project Repo/CS172 Final Project/Triggers.txt"
#define SAVELOADFILE "/Users/katidid/Documents/COMP SCI 172/Final Project Repo/CS172 Final Project/SaveGameFile.txt"

// save/load file defined in Room.h
#define MAXWEIGHT 20
using namespace std;

string makeUpperCase (string INPUT);
void inventoryCommand(vector<string>& INVENTORY, double& TOTALWEIGHT);
void getAllRooms(vector <Room>& Rooms, string FileName);
void getAllTriggers(vector <Trigger> &Triggers);
void saveGame(vector <Room>& Rooms, int CurrentID, vector <string>& Inventory);
void loadGame(vector <Room>& Rooms, int &CurrentID, vector <string>& Inventory);
double calcTotalWeight(vector<string>& INVENTORY);
void helpCommand();



int main()
{
    //Trigger test;
    //test.TEST();
    //return 1;
    
    string input;
    bool gameOn = true;
    long position;
    string verb;
    string noun;
    double totalWeight = 0;
    
    vector<string> inventory;
    
    ifstream inventoryFile(INVENFILENAME);
    
    InventoryS::readFromFile(inventoryFile);
    
    Room* currentRoom;
    vector <Room> rooms;
    getAllRooms(rooms, FILENAME);
    
    vector <Trigger> triggers;
    getAllTriggers(triggers);
    cout << triggers[0].toString(); //tests
    
    currentRoom = &rooms[0];

    
    while (gameOn) // This is the game! This loop will run until quit time.
    {
        cout << "\n>";
        getline(cin, input);
        position = input.find(' ');
        if (position == string::npos) // string::npos means there is no position
        {
            verb = input;
            //cout << "verb:" << verb << "." << endl;

        }
        else
        {
            verb = input.substr(0, position);
            noun = input.substr(position + 1);
            //cout << "verb:" << verb << "." << endl; // For testing purposes
            //cout << "noun:" << noun << "." << endl;
        }
        
        
        
        /////// Verb/noun command if statements: ////////
        
        
        if (currentRoom->checkTrigger(verb, noun, inventory, triggers)) // CHECKS FOR TRIGGERS AND ACTIVATES
        {
            cout << "Trigger Fired";
        }
        
        if (verb == "inventory" || verb == "i") // PRINTS INVENTORY
        {
            totalWeight = calcTotalWeight(inventory);
            inventoryCommand(inventory, totalWeight);
        }
        
        else if (verb == "exit" || verb == "quit") // ENDS GAME
        {
            verb = makeUpperCase(verb);
            cout << verb;
            break;
        }
        
        if (verb == "take") // PUT ITEM IN INVENTORY
        {
            if (InventoryS::getTakeOf(noun)) // if it's an item you can take...
            {
                if(currentRoom->removeItem(noun) == true) // proceeds to take item
                {
                    inventory.push_back(noun);
                    totalWeight = calcTotalWeight(inventory);
                    if (totalWeight <= MAXWEIGHT) // checks if it exceeds the weight limit...
                    {
                        cout << "\nThe " << noun << " has been placed in inventory. Your pack is now " << totalWeight << " pounds.\n";
                    }
                    else
                    {
                        inventory.pop_back(); // ...and puts it back if it does
                        cout << "\nSorry, this item pushes you over your " << MAXWEIGHT << "-pound limit!\n";
                    }
                }
                else
                {
                    cout << "\nThere is no such item here.\n";
                }
            }
            else if (InventoryS::getTakeOf(noun) == false) // if it's NOT something you can take
            {
                cout << "\nThat's not something you can pick up!\n";
            }
        }
        
        
        
        if (verb == "drop") // DROP ITEM;   (REMOVES FROM INVEN AND ADDS TO CURRENT ROOM)
        {
            currentRoom->addItemToRoom(noun);
            
            for (int i = 0; i < inventory.size(); i++)
            {
                if (inventory[i]==noun)
                {
                    inventory.erase(inventory.begin()+i);
                    break;
                }
            }
        }
        
        
        
        if (verb == "examine" || verb == "read") // DESCRIBES ITEMS IN INVENTORY
        {
            bool found=false;
            for (int i = 0; i < inventory.size(); i++)
            {
                if (inventory[i] == noun)
                {
                    cout << InventoryS::getDescriptionOf(inventory[i]);
                    found = true;
                    break;
                }

            }
            if (found == false)
                cout << "\nThat item doesn't appear to be in your inventory. Make sure to take it if you want a closer look!\n";
        }
        
        
        if ((verb == "save" && noun == "game") || verb == "save") // SAVE GAME
        {
            saveGame(rooms, currentRoom->getID(), inventory);
            cout << "\nGAME SAVED\n";
        }
        
        if (verb == "load" || (verb == "load" && noun == "game"))
        {
            int currentRoomID;
            loadGame(rooms, currentRoomID, inventory);
            for (int i = 0; i < rooms.size(); i++)
            {
                if (rooms[i].getID() == currentRoomID)
                {
                    currentRoom = &(rooms[i]);
                }
            }
        }
        
        if ((verb == "go" || verb == "swim") && (currentRoom->getID() == 8 || currentRoom->getID() == 14 || currentRoom->getID() == 15 )) // SAME AS GO BUT FOR SWIMMING IN CERTAIN AREAS
        {
            int adjacentRoomID = currentRoom->go(noun);
            if (adjacentRoomID == -1)
                cout << "You can't go that way!\n";
            else
            {
                for (int i = 0; i < rooms.size(); i++)
                {
                    if(adjacentRoomID == i)
                    {
                        currentRoom = & rooms[i];
                        cout << "Room index " << i << ", State: " << currentRoom->getState() <<endl;
                        cout << currentRoom->getDescription() << endl;
                    }
                    
                }
                
            }
        }
        
        else if (verb == "go") // MOVE AROUND
        {
            int adjacentRoomID = currentRoom->go(noun);
            if (adjacentRoomID == -1)
                cout << "You can't go that way!\n";
            else
            {
                for (int i = 0; i < rooms.size(); i++)
                {
                    if(adjacentRoomID == i)
                    {
                        currentRoom = & rooms[i];
                        cout << "Room index " << i << ", State: " << currentRoom->getState() <<endl;
                        cout << currentRoom->getDescription() << endl;
                    }

                }
                
            }
        }
        

        
        
        if (verb == "run")
        {
            cout << "The program is already running!\nHa.\nReally though. Running won't help.\n";
        }
        
        if (verb == "scream")
        {
            cout << "AHHhhhahHHHHHHHHHHHHHHeheehehhhhh...\n";
        }
        
        if (verb == "look")
        {
            cout << currentRoom->getDescription() << endl;
        }
        if (verb == "help" || verb == "menu")
        {
            helpCommand();
        }
        /*
        else
        {
            cout << "\nCommand not recognized. Make sure you didn't slip into a Klingon dialect and try again.\n";
        }
        */
    }
}

///////////////////////////////////////// END MAIN /////////////////////////////////////////









string makeUpperCase (string INPUT)
{
    string newString = INPUT;
    string c;
    
	for(int i=0;(INPUT[i]!='\0');i++)
	{
		newString[i]=toupper(INPUT[i]);
	}
    return newString;
}

void inventoryCommand(vector<string>& INVENTORY, double& TOTALWEIGHT)
{
    if (INVENTORY.size()>0)
    {
        cout << "You are carrying:\n";
        for (int i = 0; i< INVENTORY.size(); i++)
        {
            cout << INVENTORY[i] << ", " << InventoryS::getWeightOf(INVENTORY[i]) << endl;
            
        }
        cout << "Your pack is at " << TOTALWEIGHT << " pounds. You can carry 15 pounds total.\n";
    }
    else
        cout << "Your pack is empty.\n";
}

void getAllRooms(vector <Room>& Rooms, string FileName)
{
    ifstream inputFile(FileName);
    
    if (!inputFile.is_open())
    {
        cout << "File does not exist.";
    }
    else
    {
    
        while(true)
        {
            Room room;
            if(!room.readRoomFromFile(inputFile))
                break;
            Rooms.push_back(room);
            //room.printRoom(); // for testing
        }
    }
    inputFile.close();
}

void getAllTriggers(vector <Trigger> &Triggers)
{
    ifstream inputFile(TRIGFILENAME);
    
    if (!inputFile.is_open())
    {
        cout << "File does not exist.";
    }
    else
    {
        
        while(true)
        {
            Trigger trigger;
            if(!trigger.readTrigger(inputFile))
                break;
            Triggers.push_back(trigger);
        }
    }
    inputFile.close();
}

void saveGame(vector <Room>& Rooms, int CurrentID, vector <string>& Inventory)
{
    ofstream saveFile(SAVELOADFILE);
    if (!saveFile.is_open())
    {
        cout << "File does not exist.";
    }
    else
    {
        saveFile << CurrentID << endl;  // SAVING CURRENT ROOM
        
        if(Inventory.size()<=0)  // SAVING INVENTORY
        {
            saveFile << "NOINVEN";
        }
        else
        {
            saveFile << Inventory.size() << " ";
            saveFile << Inventory[0];
            for (int i = 1; i < Inventory.size(); i++)
            {
                saveFile << " " << Inventory[i];
            }
        }
        
        saveFile << endl; // (space separating inventory from room data
        
        for (int i = 0; i < Rooms.size(); i++) // SAVING ROOMS
            Rooms[i].saveRoom(saveFile);
    }
    saveFile.close();
}

void loadGame(vector <Room>& Rooms, int &CurrentID, vector <string>& Inventory)
{
    
    
    ifstream inputFile(SAVELOADFILE);
    
    string inventoryLine;
    long invenSize;
    string currentItem;
    
    if (!inputFile.is_open())
    {
        cout << "File does not exist.";
    }
    else
    {
        Rooms.clear();
        Inventory.clear();
        inputFile >> CurrentID;
        cout << CurrentID<<endl;
        getline(inputFile, inventoryLine);
        cout << inventoryLine << endl;
        
        if (inventoryLine != "NOINVEN")
        {
            stringstream(inventoryLine) >> invenSize;
            cout << "Inven size: " << invenSize << " ";
            for(int i = 0; i < invenSize; i++)
            {
                stringstream(inventoryLine) >> currentItem;
                Inventory.push_back(currentItem);
                cout << currentItem << " ";
            }
        }
        while(true)
        {
            Room room;
            if(!room.readRoomFromFile(inputFile))
                break;
            Rooms.push_back(room);
            //room.printRoom(); // for testing
        }
    }
    inputFile.close();
}

double calcTotalWeight(vector<string>& INVENTORY) // Calculates inventory weight
{
    double sum = 0;
    for (int i = 0; i< INVENTORY.size(); i++)
    {
        sum = sum + InventoryS::getWeightOf(INVENTORY[i]);
        
    }
    
    return sum;
}

void helpCommand()
{
    cout << "\nGAME HELP\n\n";
    cout << "Objective: The game's objetive is quite up to you. Help the heroes win, and defeat the villians! Or simply explore to your heart's content. Either way, use two-word commands to make the player move around the map and perform tasks.\n\n";
    cout << "Controls: Because text-based adventure games are both finnicky (this one more than most) and rather antiquated, here are some of the more useful keywords:\n";
    cout << "\thelp : displays this page\n";
    cout << "\ttake [item] : places [item] in the user's inventory, if s/he has enough room\n";
    cout << "\tdrop [item] : removes [item] from inventory and leaves it in the current location\n";
    cout << "\tgo [north/south/east/west] : allows the character to move\n";
    cout << "\tsave : saves the game\n";
    cout << "\tload : loads a saved game\n";
    cout << "\texamine [item] : displays [item's] description\n";
    cout << "\tinventory (or \"i\") : displays items in your current inventory\n";
    cout << "\tlook : displays current surroundings\n\n";
}
