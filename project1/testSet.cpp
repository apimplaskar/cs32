//
//  testSet.cpp
//  hw1
//
//  Created by Aditya Pimplaskar on 1/17/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <stdio.h>


 #include <iostream>
 #include "Set.h"
 #include <cassert>
 using namespace std;
 using ItemType = unsigned long;

 void testSet(){
     /*
 //this part was tested with ItemType as string
 Set ss1;
 Set ss2;
 
 ss1.dump(); //m_num = 0
 ss2.dump(); //m_num = 0
 assert(ss1.empty() == true);
 assert(ss2.empty() == true);
 assert(ss1.size() == 0);
 assert(ss2.size() == 0);
 
 ss1.insert("basketball");
 ss2.insert("ferrari");
 ss1.dump(); //"basketball" , new line, "m_num = 1"
 ss2.dump(); //"ferrari" , new line, "m_num = 1"
 assert(ss1.empty() == false);
 assert(ss2.empty() == false);
 assert(ss1.size() == 1);
 assert(ss2.size() == 1);
 
 ss1.insert("water polo");
 ss1.insert("swimming");
 ss1.insert("football");
 ss1.insert("baseball");
 ss2.insert("honda");
 ss2.insert("bmw");
 ss2.insert("maserati");
 ss1.dump();
 ss2.dump();
 assert(ss1.size() == 5);
 assert(ss2.size() == 4);
 ItemType x;
 ItemType y;
 assert(ss1.get(3,x) == true && x == "swimming");
 assert(ss1.get(6,x) == false && x == "swimming");
 assert(ss1.get(-1,x) == false);
 assert(ss2.get(1,y) == true && y == "ferrari");
 assert(ss2.get(0,y) == true && y == "bmw");
 assert(ss2.get(4,y) == false);
 assert(ss1.contains("bmw") == false);
 assert(ss1.contains("water polo") == true);
 assert(ss2.contains("water polo") == false);
 assert(ss2.contains("bmw") == true);
 assert(ss1.erase("quidditch") == false);
 assert(ss1.erase("baseball") == true);
 ss1.dump();
 assert(ss2.erase("aston martin") == false);
 assert(ss2.erase("honda") == true);
 ss2.dump();
 ss1.swap(ss2);
 ss1.dump();
 ss2.dump();
 //IMPLEMENT Set.swap WITHOUT CREATING TEMP ARRAY
 
 //NOW TO CHECK IF COPY CONSTRUCTORS, ASSIGNMENT OPERATORS, DESTRUCTORS (default) WORK
 //THEN TRY WITH CHANGING ITEMTYPE TO UNSIGNED LONG
 
 Set ss3 = ss1; //for copy constructor
 ss3.dump();
 
 ss3 = ss2; //for assignment operator
 ss3.dump();
 
 */


//this part was tested using ItemType of unsigned long
Set ss4;
Set ss5;

ss4.dump(); //m_num = 0
ss5.dump(); //m_num = 0
assert(ss4.empty() == true);
assert(ss5.empty() == true);
assert(ss4.size() == 0);
assert(ss5.size() == 0);

ss4.insert(1);
ss5.insert(2);
ss4.dump(); //1 , new line, "m_num = 1"
ss5.dump(); //2 , new line, "m_num = 1"
assert(ss4.empty() == false);
assert(ss5.empty() == false);
assert(ss4.size() == 1);
assert(ss5.size() == 1);

ss4.insert(3);
ss4.insert(5);
ss4.insert(7);
ss4.insert(9);
ss5.insert(4);
ss5.insert(6);
ss5.insert(8);
ss4.dump();
ss5.dump();
assert(ss4.size() == 5);
assert(ss5.size() == 4);

ItemType x;
ItemType y;

assert(ss4.get(3,x) == true && x == 7);
assert(ss4.get(6,x) == false && x == 7);
assert(ss4.get(-1,x) == false);
assert(ss5.get(1,y) == true && y == 4);
assert(ss5.get(0,y) == true && y == 2);
assert(ss5.get(4,y) == false);
assert(ss4.contains(4) == false);
assert(ss4.contains(3) == true);
assert(ss5.contains(3) == false);
assert(ss5.contains(8) == true);
assert(ss4.erase(11) == false);
assert(ss4.erase(9) == true);
ss4.dump();
assert(ss5.erase(0) == false);
assert(ss5.erase(8) == true);
ss5.dump();
ss4.swap(ss5);
ss4.dump();
ss5.dump();

}

int main(){
    testSet();
    cout << "Passed all tests" << endl;
}

