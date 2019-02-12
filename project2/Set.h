//
//  Set.h
//  project2
//
//  Created by Aditya Pimplaskar on 1/23/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef Set_h
#define Set_h
#include <string>
using ItemType = std::string;
//using ItemType = int;

struct Item{
    ItemType m_item;
    Item* next;
    Item* prev;
};

class Set
{
public:
    Set();
    bool empty() const;
    int size() const;
    bool insert(const ItemType& value);
    bool erase(const ItemType& value);
    bool contains(const ItemType& value) const;
    bool get(int pos, ItemType& value) const;
    void swap(Set& other);
    
    //ADDED PUBLIC MEMBER FUNCTIONS
    Set(const Set& other); //copy constructor
    Set& operator=(const Set& other); //assignment operator
    ~Set(); //destructor
    void dump() const;
    
private:
    // Item will store the value, and will be able to point to the next and previous items
    int m_size; //number of items
    Item* head; //ptr at start
    Item* tail; //ptr at end
};

void unite(const Set& s1, const Set& s2, Set& result);
void subtract(const Set& s1, const Set&s2, Set& result);

#include <stdio.h>

#endif /* Set_h */
