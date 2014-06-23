//
//  Inventory.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/21/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__Inventory__
#define __CS172_Final_Project__Inventory__

#include <iostream>
#include <vector>
#include "Item.h"

class Inventory
{
public:
    void addItem(string);
    void removeItem(string);
    bool searchInven(string Name);
    double totalWeight();
    int getSize();
    void readFromFile();
    void writeToFile();
    vector <Item> getItems();

    
private:
    vector <Item> items;
    static Inventory theInventory;
    
};

#endif /* defined(__CS172_Final_Project__Inventory__) */
