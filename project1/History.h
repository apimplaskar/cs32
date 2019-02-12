//
//  History.h
//  project1
//
//  Created by Aditya Pimplaskar on 1/11/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef History_h
#define History_h

#include <stdio.h>
#include "globals.h"


class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_nRows;
    int m_nCols;
    char m_grid[MAXROWS][MAXCOLS];
    
};


#endif /* History_h */
