//
//  Inventory.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/21/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "Inventory.h"


vector <Item> Inventory::getItems()
{
    return items;
}
void Inventory::addItem(string item)
{
    for (int i = 0; i < rooms[currentRoom].inventory.getSize(); i++)
    {
        
    }
    items.push_back(item);
}
void Inventory::removeItem(string movingItem)
{
    int itemPosition = -1;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getName() == movingItem)
            itemPosition = i;
    }
    if (itemPosition == -1)
        cout << "You don't have that item!" << endl;
    else
        items.erase(items.begin()+ itemPosition);
}
bool Inventory::searchInven(string Name)
{
    
    return true;
}
double Inventory::totalWeight()
{
    double sum = 0;
    for (int i = 0; i < items.size(); i++)
    {
        sum = sum + items[i].getWeight();
    }
    return sum;
}
int Inventory::getSize()
{
    double sum = 0;
    for (int i = 0; i < items.size(); i++)
    {
        sum++;
    }
    return sum;
}


void readFromFile()
{
    
}
void writeToFile()
{
    
}
