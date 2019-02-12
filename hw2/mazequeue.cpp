//
//  main.cpp
//  hw2-queue
//
//  Created by Aditya Pimplaskar on 1/30/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <queue>
#include <cassert>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

//ASSUMPTIONS for simplification:
/*
 The maze array contains nRows rows (you couldn't check for this anyway); each string in the maze is of length nCols;
 The maze contains only Xs and dots when passed in to the function;
 The top and bottom rows of the maze contain only Xs, as do the left and right columns;
 sr and er are between 0 and nRows-1, and sc and ec are between 0 and nCols-1;
 maze[sr][sc] and maze[er][ec] are '.' (i.e., not walls)
 
 PSEUDOCODE FOLLOWS THE STACK PSEUDOCODE; just the order of traversing the maze changes.
 */

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    // Return true if there is a path from (sr,sc) to (er,ec)
    // through the maze; return false otherwise
    queue<Coord> coordQueue; //use STL to create queue
    
    //Create coordinate for start pt and add it to the queue
    Coord start(sr,sc);
    maze[sr][sc] = 'e'; //e for encountered
    coordQueue.push(start);
    
    while(!coordQueue.empty()){ //while queue not empty
        Coord curr = coordQueue.front(); //peeks at front item
        int c_row = curr.r();
        int c_col = curr.c();
        coordQueue.pop(); //STL pop doesn't return element, check top and pop separately
        //cerr << c_row << "," << c_col << endl;
        if (c_row == er && c_col == ec) { return true; } //solved
        else{
            if(maze[c_row+1][c_col] != 'e' && maze[c_row+1][c_col] != 'X'){ //checks down
                maze[c_row+1][c_col] = 'e'; //mark as seen
                Coord AddDown(c_row+1, c_col); //push to stack
                coordQueue.push(AddDown);
            }
            if(maze[c_row][c_col-1] != 'e' && maze[c_row][c_col-1] != 'X'){ //checks left
                maze[c_row][c_col-1] = 'e';
                Coord AddLeft(c_row, c_col-1);
                coordQueue.push(AddLeft);
            }
            if(maze[c_row-1][c_col] != 'e' && maze[c_row-1][c_col] != 'X'){ //checks up
                maze[c_row-1][c_col] = 'e';
                Coord AddUp(c_row-1, c_col);
                coordQueue.push(AddUp);
            }
            if(maze[c_row][c_col+1] != 'e' && maze[c_row][c_col+1] != 'X'){ //checks left
                maze[c_row][c_col+1] = 'e';
                Coord AddRight(c_row, c_col+1);
                coordQueue.push(AddRight);
            }
        }
        
    }
    return false; //not found
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
