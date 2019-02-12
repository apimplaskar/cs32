//
//  SSNSet.cpp
//  hw1
//
//  Created by Aditya Pimplaskar on 1/17/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//


#include "SSNSet.h"
#include <iostream>
using namespace std;


SSNSet::SSNSet(){
}

bool SSNSet::add(unsigned long ssn){
    return m_Set.insert(ssn);
}

int SSNSet::size() const{
    return m_Set.size();
}

void SSNSet::print() const{
    for (int i = 0; i < m_Set.size(); i++){
        ItemType x;
        m_Set.get(i, x);
        cout << x << endl;
        //can't access m_arr from m_Set
        // have to use a function in class Set
    }
}

