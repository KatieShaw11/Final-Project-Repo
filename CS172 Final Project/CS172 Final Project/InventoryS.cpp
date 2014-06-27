//
//  InventoryS.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/21/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "InventoryS.h"

static vector <Item> theInventory;

bool getNextInventoryDataLine(ifstream& ifstr, string& inputLine) //helper function for reading lines excluding empty lines to make files more readable; to replace getlines
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


void InventoryS::addItem(string)
{
    
}
void InventoryS::removeItem(string)
{
    
}
bool InventoryS::searchInven(string Name)
{
    for(int i = 0; i < theInventory.size(); i++)
    {
        if(theInventory[i].getName() == Name)
            return true;
    }
    return false;
}
bool InventoryS::readFromFile(ifstream& str) //inheritance/polymorphism
{
    while(!str.eof())
    {
        string activateCheck;
        getNextInventoryDataLine(str, activateCheck);
        
        Item item;
        ActivatableItem aItem;
        if (activateCheck == "<nonact>") // reading in regular items
        {
            if(item.readItemFile(str)==false)
                break;
            theInventory.push_back(item);
        }
        
        if (activateCheck == "<act>") // reading in activatable items
        {
            if(aItem.readItemFile(str)==false)
                break;
            theInventory.push_back(aItem);
        }
    }
    return true;
}
void InventoryS::writeToFile()
{
    
}

double InventoryS::getWeightOf(string Name)
{
    for(int i = 0; i < theInventory.size(); i++)
    {
        if(theInventory[i].getName() == Name)
            return theInventory[i].getWeight();
    }
    
    return -1;
}
string InventoryS::getDescriptionOf(string Name)
{
    for(int i = 0; i < theInventory.size(); i++)
    {
        if(theInventory[i].getName() == Name)
            return theInventory[i].getDescription();
    }
    
    return "No description for this item.";
}

bool InventoryS::getTakeOf(string Name)
{
    for(int i = 0; i < theInventory.size(); i++)
    {
        if(theInventory[i].getName() == Name)
            return theInventory[i].getTake();
    }
    
    return "No takeAble status for this item.";
}
