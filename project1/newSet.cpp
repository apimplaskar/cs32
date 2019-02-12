//
//  newSet.cpp
//  hw1
//
//  Created by Aditya Pimplaskar on 1/17/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include "newSet.h"
#include <iostream>

using namespace std;
using ItemType = unsigned long;

Set::Set(){
    m_arr = new ItemType[DEFAULT_MAX_ITEMS];
    m_num = 0;
    m_size = DEFAULT_MAX_ITEMS;
}

Set::Set(int n){
    m_arr = new ItemType[n];
    m_num = 0;
    m_size = n;
    
}

Set::Set(const Set &other){
    m_size = other.m_size;
    m_num = other.m_num;
    m_arr = new ItemType[m_num];
    for (int i=0; i < m_num; i++){
        m_arr[i] = other.m_arr[i];
    }
}

Set& Set::operator=(const Set &other){
    if(this == &other){ return *this; }
    delete[] m_arr;
    m_size = other.m_size;
     m_num = other.m_num;
    m_arr = new ItemType[m_num];
    for (int i=0; i < m_num; i++){
        m_arr[i] = other.m_arr[i];
    }
    return *this;
}

Set::~Set(){
    delete[] m_arr;
}

bool Set::empty() const{
    if (m_num == 0){ return true; }
    else{ return false; }
}

int Set::size() const{
    return m_num;
}

bool Set::insert(const ItemType& value){
    if(m_num >= DEFAULT_MAX_ITEMS) { return false; }
    for (int i = 0; i < m_num; i++){
        if (m_arr[i] == value){ return false; }
    }
    m_arr[m_num] = value;
    m_num++;
    return true;
}

bool Set::erase(const ItemType& value){
    for (int i = 0; i < m_num; i++){
        if (m_arr[i] == value){
            for (int j = i; j < m_num; j++){
                m_arr[j] = m_arr[j+1];
            }
            m_num--;
            return true;
        }
        
    }
    return false;
}

bool Set::contains(const ItemType &value) const{
    for (int i = 0; i < m_num; i++){
        if (m_arr[i] == value){ return true; }
    }
    return false;
}

bool Set::get(int i, ItemType &value) const{
    if(i < 0 || i > m_num){ return false; } //eliminate invalid input
    //need to find the order for the elements of the array
    //then we find the i+1 th element of the sorted array
    
    int count=0;
    for (int j=0; j < m_num; j++){ //loop over each element
        for (int k=0; k < m_num; k++){ //loop through the array again to see how many it is greater than
            if (j == k){ continue; } //can't compare the element to itself
            else{
                if (m_arr[j] > m_arr[k]){ //at the end of this loop, we will get the index of the element in an ordered array
                    count++;
                }
            }
        }
        if (count == i) {
            value = m_arr[j];
            return true;
        }
        count = 0;
    }
    return false;
}

void Set::swap(Set& other) {
    //Now we can use pointers
    ItemType* ptr;
    ptr = m_arr;
    m_arr = other.m_arr;
    other.m_arr = ptr;
    
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
    int temp_num = m_num;
    m_num = other.m_num;
    other.m_num = temp_num;
}

/*
 //This is the way from Set.cpp
    ItemType temp;
    int maxNum;
    
    if (m_num <= other.m_num){ maxNum = other.m_num; }
    else{ maxNum = m_num; }
    
    for (int i=0; i < maxNum; i++){
        temp = m_arr[i];
        m_arr[i] = other.m_arr[i];
        other.m_arr[i] = temp;
    }
    
    int tempNum = m_num;
    m_num = other.m_num;
    other.m_num = tempNum;
    return;
}
 */

/* did it this way first with a temp array
 
 //create temp array
 ItemType temp[m_num];
 int temp_num = m_num;
 for(int m = 0; m < m_num; m++){
 temp[m] = m_arr[m];
 }
 // need to clear out the original array
 for(int i = 0; i < m_num; i++){
 m_arr[i] = "";
 }
 //fill in this array with other array
 m_num = other.size();
 for (int j = 0; j < m_num; j++){
 m_arr[j] = other.m_arr[j];
 }
 //fill in other array from temp
 for(int k = 0; k < temp_num; k++){
 other.m_arr[k] = temp[k];
 }
 //replace other's m_num member
 other.m_num = temp_num;
 return;
 }
 */

void Set::dump() const{
    for (int i=0; i < m_num; i++) { cerr << m_arr[i] << endl; }
    cerr << "m_num = " << m_num << endl;
}
