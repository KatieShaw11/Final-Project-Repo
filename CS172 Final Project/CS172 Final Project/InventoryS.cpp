//
//  InventoryS.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/21/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "InventoryS.h"

static vector <Item> theInventory;


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
bool InventoryS::readFromFile(ifstream& str)
{
    while(!str.eof())
    {
        Item item;
        if(item.readItemFile(str)==false)
            break;
        //item.readItemFile(str);
        theInventory.push_back(item);
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

bool InventoryS::getActOf(string Name)
{
    for(int i = 0; i < theInventory.size(); i++)
    {
        if(theInventory[i].getName() == Name)
            return theInventory[i].getAct();
    }
    
    return "No activateAble status for this item.";
}
