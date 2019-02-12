//
//  newSet.h
//  hw1
//
//  Created by Aditya Pimplaskar on 1/17/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#ifndef newSet_h
#define newSet_h

#include <stdio.h>
using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Set
{
public:
    
    Set();         // Create an empty set (i.e., one with no items). Array made of size DEFAULT_MAX_ITEMS.
    
    Set(int n); // Create an array of size n.
    
    Set(const Set &other); //Non-default copy constructor
    
    Set& operator=(const Set &other); //Non-default assignment operator
    
    ~Set(); //Non-default destructor
    
    bool empty() const;  // Return true if the set is empty, otherwise false.
    
    int size() const;    // Return the number of items in the set.
    
    
    bool insert(const ItemType& value);
    // Insert value into the set if it is not already present.  Return
    // true if the value was actually inserted.  Leave the set unchanged
    // and return false if the value was not inserted (perhaps because it
    // was already in the set or because the set has a fixed capacity and
    // is full).
    
    bool erase(const ItemType& value);
    // Remove the value from the set if present.  Return true if the
    // value was removed; otherwise, leave the set unchanged and
    // return false.
    
    bool contains(const ItemType& value) const;
    // Return true if the value is in the set, otherwise false.
    
    bool get(int i, ItemType& value) const;
    // If 0 <= i < size(), copy into value the item in the set that is
    // strictly greater than exactly i items in the set and return true.
    // Otherwise, leave value unchanged and return false.
    
    void swap(Set& other);
    // Exchange the contents of this set with the other one.
    
    void dump() const;
    // Use to print info about set
    // Must write to cerr
    
private:
    ItemType* m_arr; // pointer to the array
    int m_num; // number of elements we care about, AKA the size
    int m_size; //Total size of array
};
#endif /* newSet_h */
