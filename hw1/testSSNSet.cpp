//
//  testSSNSet.cpp
//  hw1
//
//  Created by Aditya Pimplaskar on 1/17/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <stdio.h>

#include <iostream>
#include "SSNSet.h"
#include "newSet.h"
using namespace std;
using ItemType = unsigned long;


void testSSNSet(){
    SSNSet ssn1;
    
    ssn1.add(111111111);
    ssn1.print();
    assert(ssn1.size() == 1);
    
    ssn1.add(222222222);
    ssn1.print();
    assert(ssn1.size() == 2);
    
    ssn1.add(333333333);
    ssn1.add(444444444);
    ssn1.add(555555555);
    assert(ssn1.size() == 5);
    
}

int main(){
    testSSNSet();
    cout << "Passed all tests" << endl;
}

