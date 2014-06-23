//
//  Item.cpp
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/8/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#include "Item.h"

bool getNextItemDataLine(ifstream& ifstr, string& inputLine) //helper function for reading lines excluding empty lines to make files more readable; to replace getlines
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

Item::Item()
{
    description = "Default item";
    weight = 1;
    takeAble = true;
}

Item::Item(string Description, double Weight, bool TakeAble)
{
    description = Description;
    weight = Weight;
    takeAble = TakeAble;
}

string Item::getDescription()
{
    return description;
}

double Item::getWeight()
{
    return weight;
}

bool Item::getAct()
{
    return activateAble;
}
bool Item::getTake()
{
    return takeAble;
}

void Item::setWeight(double Weight)
{
    weight = Weight;
}
void Item::setName(string Name)
{
    name = Name;
}
string Item::getName()
{
    return name;
}


bool Item::readItemFile(ifstream& str)
{
    string inputLine;
    
    if(getNextItemDataLine(str, inputLine)) // Name
    {
        name = inputLine;
    }
    else
        return false;
    
    if(getNextItemDataLine(str, inputLine)) // ActivateAble
    {
        stringstream(inputLine) >> activateAble;
    }
    else
        return false;
    
    if(getNextItemDataLine(str, inputLine)) // takeAble
    {
        stringstream(inputLine) >> takeAble;
    }
    else
        return false;
    
    
    
    if(getNextItemDataLine(str, inputLine)) // Description
        description = inputLine;
    else
        return false;
    
    
    if(getNextItemDataLine(str, inputLine)) // Weight
        stringstream(inputLine) >> weight; // stringstream converts to doubles
    else
        return false;
    
    //cout << name << " " << description << " " << weight << endl; //for testing
    
    return true;
}


