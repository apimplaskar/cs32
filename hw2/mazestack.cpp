//
//  main.cpp
//  hw2-stack
//
//  Created by Aditya Pimplaskar on 1/30/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <stack>
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
*/
 
/*
Push the starting coordinate (sr,sc) onto the coordinate stack and
update maze[sr][sc] to indicate that the algorithm has encountered
it (i.e., set maze[sr][sc] to have a value other than '.').
While the stack is not empty,
{   Pop the top coordinate off the stack. This gives you the current
    (r,c) location that your algorithm is exploring.
    If the current (r,c) coordinate is equal to the ending coordinate,
    then we've solved the maze so return true!
    Check each place you can move from the current cell as follows:
    If you can move SOUTH and haven't encountered that cell yet,
    then push the coordinate (r+1,c) onto the stack and update
    maze[r+1][c] to indicate the algorithm has encountered it.
    If you can move WEST and haven't encountered that cell yet,
    then push the coordinate (r,c-1) onto the stack and update
    maze[r][c-1] to indicate the algorithm has encountered it.
    If you can move NORTH and haven't encountered that cell yet,
    then push the coordinate (r-1,c) onto the stack and update
    maze[r-1][c] to indicate the algorithm has encountered it.
    If you can move EAST and haven't encountered that cell yet,
    then push the coordinate (r,c+1) onto the stack and update
    maze[r][c+1] to indicate the algorithm has encountered it.
}
There was no solution, so return false
*/


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
    stack<Coord> coordStack; //use STL to create stack
    
    //Create coordinate for start pt and push it onto the stack
    Coord start(sr,sc);
    maze[sr][sc] = 'e'; //e for encountered
    coordStack.push(start);
    
    while(!coordStack.empty()){ //while stack not empty
        Coord curr = coordStack.top(); //peeks at top item
        int c_row = curr.r();
        int c_col = curr.c();
        coordStack.pop(); //STL pop does not return the element it pops, so we have to check the top and pop separately
        //cerr << c_row << "," << c_col << endl;
        if (c_row == er && c_col == ec) { return true; } // solved
        
        else{
            if(maze[c_row+1][c_col] != 'e' && maze[c_row+1][c_col] != 'X'){ //checks down
                maze[c_row+1][c_col] = 'e'; //mark as seen
                Coord AddDown(c_row+1, c_col); //push to stack
                coordStack.push(AddDown);
            }
            if(maze[c_row][c_col-1] != 'e' && maze[c_row][c_col-1] != 'X'){ //checks left
                maze[c_row][c_col-1] = 'e';
                Coord AddLeft(c_row, c_col-1);
                coordStack.push(AddLeft);
            }
            if(maze[c_row-1][c_col] != 'e' && maze[c_row-1][c_col] != 'X'){ //checks up
                maze[c_row-1][c_col] = 'e';
                Coord AddUp(c_row-1, c_col);
                coordStack.push(AddUp);
            }
            if(maze[c_row][c_col+1] != 'e' && maze[c_row][c_col+1] != 'X'){ //checks left
                maze[c_row][c_col+1] = 'e';
                Coord AddRight(c_row, c_col+1);
                coordStack.push(AddRight);
            }
        }
    }
    return false; //hasn't been found
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
