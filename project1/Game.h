//
//  Game.h
//  project1
//
//  Created by Aditya Pimplaskar on 1/9/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
};

#endif /* Game_h */
