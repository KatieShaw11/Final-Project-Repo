//
//  Item.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/8/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__Item__
#define __CS172_Final_Project__Item__

#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

class Item
{
public:
    Item();
    
    Item(string Description, double Weight, bool TakeAble);
    string getDescription();
    double getWeight();
    bool getTake();
    void setWeight(double Weight);
    
    void setName(string);
    string getName();

    bool readItemFile(ifstream& str);


private:
    string name;
    string description;
    double weight;
    bool takeAble;
};

#endif /* defined(__CS172_Final_Project__Item__) */
