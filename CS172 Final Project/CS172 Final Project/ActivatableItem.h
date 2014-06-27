//
//  Activatable Item.h
//  CS172 Final Project
//
//  Created by katie joy shaw on 6/23/14.
//  Copyright (c) 2014 Katie Shaw. All rights reserved.
//

#ifndef __CS172_Final_Project__Activatable_Item__
#define __CS172_Final_Project__Activatable_Item__

#include <iostream>
#include "Item.h"

class ActivatableItem: public Item
{
public:
    void activate();
    
private:
    bool activated;
};

#endif /* defined(__CS172_Final_Project__Activatable_Item__) */
