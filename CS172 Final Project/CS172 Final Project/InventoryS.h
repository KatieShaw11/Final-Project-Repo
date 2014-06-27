//
//  InventoryS.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/21/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__InventoryS__
#define __CS172_Final_Project__InventoryS__

#include <iostream>
#include "Item.h"
#include "ActivatableItem.h"
#include <vector>
#include <sstream>
#include <fstream>

class InventoryS
{
public:


    static void addItem(string);
    static void removeItem(string);
    static bool searchInven(string Name);
    static bool readFromFile(ifstream& str);
    static void writeToFile();
    
    static double getWeightOf(string Name);
    static string getDescriptionOf(string Name);
    static bool getTakeOf(string Name);

};

#endif /* defined(__CS172_Final_Project__InventoryS__) */
