//
//  main.cpp
//  project1
//
//  Created by Aditya Pimplaskar on 1/9/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

// zombies.cpp

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

#include "Game.h"
#include "Player.h"
#include "Zombie.h"
#include "Arena.h"
#include "globals.h"

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////


int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);
    
    // Play the game
    g.play();
}

