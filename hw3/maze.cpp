//
//  main.cpp
//  hw3-maze
//
//  Created by Aditya Pimplaskar on 2/6/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
/*
If the start location is equal to the ending location, then we've
solved the maze, so return true.
Mark the start location as visted.
For each of the four directions,
If the location one step in that direction (from the start location) is unvisited,
 then call pathExists starting from that location (and ending at the same ending location as in the current call).
If that returned true,
then return true.
Return false.
*/

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    
    //Handle invalid input
    if (sr > nRows || sc > nCols || er > nRows || ec > nCols) {return false;}
    
    //base case
    if (sr == er && sc == ec){ return true; }
    
    maze[sr][sc] = 'v'; //mark as visited
    
    //recursive step
    if (maze[sr+1][sc] == '.'){ //down
        if(pathExists(maze, nRows, nCols, sr+1, sc, er, ec)){ return true; }
    }
    if (maze[sr][sc-1] == '.'){ //left
        if(pathExists(maze, nRows, nCols, sr, sc-1, er, ec)){ return true; }
    }
    if (maze[sr-1][sc] == '.'){ //up
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec)){ return true;}
    }
    if (maze[sr][sc+1] == '.'){ //right
        if(pathExists(maze, nRows, nCols, sr, sc+1, er, ec)) { return true; }
    }
           
    
    //no path
    return false;
}

int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X....X...X",
        "X.XX.XX..X",
        "XXX....X.X",
        "X.XXX.XXXX",
        "X.X...X..X",
        "X...X.X..X",
        "XXXXX.X.XX",
        "X........X",
        "XXXXXXXXXX"
    };
    
    string maze2[6] = {
        "XXXXXX",
        "X...XX",
        "XXX.XX",
        "X.X.XX",
        "XXX.XX",
        "XXXXXX"
    };
    
    
    //pathExists(maze, 10, 10, 3, 5, 8, 8);
    assert(pathExists(maze, 10, 10, 1, 1, 8, 8));
    assert(!pathExists(maze, 10, 10, 8, 8, 1, 8));
    assert(pathExists(maze2, 6, 6, 1, 3, 4, 3));
    assert(!pathExists(maze2, 6, 6, 1, 3, 3, 1));
    cout << "All tests passed" << endl;
}
