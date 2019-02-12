//
//  History.cpp
//  project1
//
//  Created by Aditya Pimplaskar on 1/11/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//
#include <iostream>
using namespace std;
#include "History.h"
#include "globals.h"

History::History(int nRows, int nCols){
    m_nCols = nCols;
    m_nRows = nRows;
    for (int i = 1; i <= nRows; i++){
        for (int j = 1; j <= nCols; j++){
            m_grid[i][j] = '.'; //initalize to all representing 0 deaths
            //2-d array represents the arena
        }
    }
}

bool History::record(int r, int c){
    if (r <= 0 || c <= 0 || r > MAXROWS || c > MAXCOLS){ //invalid input by our system
        return false;
    }
    if (m_grid[r][c] == '.'){
        m_grid[r][c] = 'A'; //first one
    }
    else if(m_grid[r][c] >= 'A' && m_grid[r+1][c+1] < 'Z' ){
        m_grid[r][c] += 1; //relies on ASCII numerization of characters
    }
    else{
        m_grid[r][c] = 'Z'; //upper bound
    }
    return true;
}

void History::display() const{
    clearScreen();
    for (int i = 1; i <= m_nRows; i++){
        for (int j = 1; j <= m_nCols; j++){
            cout << m_grid[i][j];
        }
        cout << "\n";
    }
    cout << "\n"; 
}



