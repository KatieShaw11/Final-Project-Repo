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
#define FILENAME "/Users/katidid/Documents/COMP SCI 172/Final Project/CS172 Final Project/Rooms test.txt"
#define INVENFILENAME "/Users/katidid/Documents/COMP SCI 172/Final Project/CS172 Final Project/Full Inventory.txt"
#define MAXWEIGHT 15
using namespace std;

string makeUpperCase (string INPUT);
void inventoryCommand(vector<string>& INVENTORY, double& TOTALWEIGHT);
void getAllRooms(vector <Room>& Rooms);
void saveGame(vector <Room>& Rooms);
double calcTotalWeight(vector<string>& INVENTORY);



int main()
{
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
    getAllRooms(rooms);
    
    
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
            saveGame(rooms);
            cout << "\nGAME SAVED\n";
        }
        if (verb == "go") // MOVE AROUND
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
    }
}
// END MAIN







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

void getAllRooms(vector <Room>& Rooms)
{
    ifstream inputFile(FILENAME);
    
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

void saveGame(vector <Room>& Rooms)
{
    for (int i = 0; i < Rooms.size(); i++)
        Rooms[i].saveRoom();
    cout << "GAME SAVED";
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

