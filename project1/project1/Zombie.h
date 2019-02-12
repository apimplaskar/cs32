//
//  Zombie.h
//  project1
//
//  Created by Aditya Pimplaskar on 1/9/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef Zombie_h
#define Zombie_h

#include <stdio.h>

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Zombie declaration.

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool getAttacked(int dir);
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
};


#endif /* Zombie_h */
