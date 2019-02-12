//
//  Set.cpp
//  project2
//
//  Created by Aditya Pimplaskar on 1/23/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include "Set.h"
#include <iostream>
using namespace std;
using ItemType = std::string;
//using ItemType = int;

Set::Set(){
    //Since we insert as we go, we don't need to define a capacity
    //Initializes size to 0, head and tail both pointer to nullptr in an empty linked list
    m_size = 0;
    head = nullptr;
    tail = nullptr;
}

Set::Set(const Set& other){
    m_size = other.m_size;
    Item* q = other.head;
    
    //Traverse linked list to make copies
    Item* previous = nullptr; //to keep track of the previous item
    Item* newItem = nullptr; //keep track of current item
    head = nullptr; //default initalization
    
    while(q != nullptr){ //if empty, this doesn't execute (head = nullptr, tail wiil get assigned nullptr too)
        newItem = new Item; //allocate new item
        if(q == other.head) { head = newItem; } // takes care of 1st element
        newItem -> m_item = q->m_item; // assign value
        newItem->prev = previous; //update previous ptr using the ptr we declared outside
        if(previous != nullptr){ previous->next = newItem; } //if prev is nullptr, we have reached the end (so it can't have a next)
        previous = newItem; //update previous for the next iteration
        q = q->next;
    }
    tail = newItem;
    tail -> next = nullptr;
}

Set& Set::operator=(const Set& other){
    if (&other == this) { return *this; }
    //Destructor
    Item* p = head;
    while (p != nullptr){
        Item* deleteNext = p->next;
        delete p;
        p = deleteNext;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    //Now we have a fresh start, just use copy constructor code
    m_size = other.m_size;
    Item* q = other.head;
    
    //Traverse linked list to make copies
    Item* previous = nullptr; //to keep track of the previous item
    Item* newItem = nullptr;
    head = nullptr;
    
    while(q != nullptr){
        newItem = new Item;
        if(q == other.head) { head = newItem; }
        newItem -> m_item = q->m_item;
        newItem->prev = previous;
        if(previous != nullptr){ previous->next = newItem; }
        previous = newItem;
        q = q->next;
    }
    tail = newItem;
    tail -> next = nullptr;

    return *this;
}

Set::~Set(){
    Item* p = head;
    while (p != nullptr){
        Item* deleteNext = p->next;
        delete p;
        p = deleteNext;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

bool Set::empty() const{
    // We have a variable that keeps track of size
    if (m_size == 0){ return true; }
    return false;
}

int Set::size() const{ return m_size; } //returns size variable

// things to check for:
// make sure head, tail, and m_size are ALWAYS in sync

bool Set::insert(const ItemType &value){ //Insert in alpha order to make get function's implementation easier
    //Case 1: empty linked list, aka if head points to null
    if (head == nullptr){
        Item* p = new Item; //allocate new item
        p->m_item = value; //assign value to item's member
        head = p; //connect head to p
        p->prev = nullptr;
        tail =  p; //p is now the tail
        p->next = nullptr; //p connected to null
        m_size++;
        return true;
    }
    //Case 2: otherwise
    else{
        
        //traverse list to make sure that nothing is repeated
        //if we don't find a repeat, break out when we get to a value that EXCEEDS the one we want to add
        Item* check = head; // it is all right for us to go past the last element (we want to scan everything)
        while(check != nullptr){
            if(check->m_item == value){ return false; }
            if(check->m_item > value){ break; }
            check = check -> next;
        }
        
        //Account for case where check reaches the end of the linked list (new item is tail)
        //1) update new item's value to the inserted value
        //2) the check pointer now points to tail's next
        //3) tail's next = new item
        //   new item's prev = tail
        //   new item's next = null
        //   tail now points to new item
        
        if (check == nullptr){
            Item* p = new Item; //allocate new item
            p->m_item = value; //assign value
            tail->next = p;
            p->prev = tail;
            p->next = nullptr;
            tail = p;
            m_size++;
            return true;
        }
        
        //Psuedocode for how we will change the pointers after new item has been allocated
        //1) update new item's value to the inserted value
        //2) the check pointer now points to the element that will come AFTER the one we are adding
        //3) new item's previous is check item's previous
        //   check's previous is new item
        //   new item's next is check
        //   new item's previous' next is the new item
        
        //Case: if it has to be added to the front
        if(check == head){
            Item* p = new Item; //allocate new item
            p->m_item = value; //assign value
            p->next = head;
            head->prev = p;
            p->prev = nullptr;
            head = p;
            m_size++;
            return true;
         }
            
        Item* p = new Item; //allocate new item
        p->m_item = value; //assign value
        //step 3 in pseudocode
        p->prev = check->prev;
        check->prev = p;
        p->next = check;
        p->prev->next = p;
        m_size++;
        return true;
    
}
}

    

/* THIS VERSION INSERTS TO END EVERYTIME. It was ammended so as to make the get function's implementation easier.
    //Case 1: empty linked list, aka if head points to null
    if (head == nullptr){
        Item* p = new Item; //allocate new item
        p->m_item = value; //assign value to item's member
        head = p; //connect head to p
        p->prev = nullptr;
        tail =  p; //p is now the tail
        p->next = nullptr; //p connected to null
        m_size++;
        return true;
    }
    
    //Case 2: otherwise
    else{
        
        //traverse list to make sure that nothing is repeated
        Item* check_repeats = head; // it is all right for us to go past the last element (we want to scan everything)
        while(check_repeats != nullptr){
            if(check_repeats->m_item == value){ return false; }
            check_repeats = check_repeats -> next;
        }
        
        //Psuedocode for how we will change the pointers after new item has been allocated
        //1) update new item's value to the inserted value
        //2) new element is next after the old tail
        //3) new element's next points to null (where the old tail's next pointed)
        //   new element's old points to the old tail
        //4) tail = new element
        
        //don't need to traverse the list to add new item, since we have a tail pointer
        //as we did in lecture
        Item* p = new Item; //allocate new item
        p->m_item = value; //assign value
        tail->next = p; //now new item connects to old tail
        p-> next = nullptr;
        p -> prev = tail;
        tail = p; // p is new tail
        m_size++;
        return true;
        
    }
}
*/
    


bool Set::erase(const ItemType &value){
    //Case 1: empty linked list, return false as there is nothing to erase
    if (head == nullptr){ return false; }
    //Case 2 non-empty linked list
    else{
        //Case 2.1, the element does not exist in the list
        //Traverse the list to check (just as we did in the insert function)
        //If we do not find an item matching value, return false. If we do, carry on.
        Item* value_present = head; // it is all right for us to go past the last element (we want to scan everything)
        while(value_present != nullptr){
            if(value_present -> m_item == value){ break; }
            value_present = value_present -> next;
        }
        if (value_present == nullptr){ return false; } //if we make it to the bottom of the list without breaking
        else{
            //Case 3, we have found the element and value_present points to the node before the one we want to delete. Now we can delete the allocated spcae for it and link the elements before and after it.
            // If there is an element that precedes the element we want to delete
            
            if(value_present->prev != nullptr){ value_present->prev->next = value_present->next; }
                //Handles case where value present is not the first element
            if(value_present->next != nullptr){ value_present->next->prev = value_present->prev; }
                //Case where value present is not the last element
            if(value_present == head){ head = value_present->next; }
                //If value present is the first element
            if(value_present == tail){ tail = value_present -> prev; }
                //If value present is the last element
            
            delete value_present; //get rid of space in memory
            m_size--; //update size
            return true;
        }
    }
}

//Linked list traversal, if we find element, return true
bool Set::contains(const ItemType &value) const{
    Item* check = head;
    while(check != nullptr){
        if(check -> m_item == value){ return true; }
        check = check->next;
    }
    return false;
}

bool Set::get(int pos, ItemType &value) const{
    if(pos <0 || pos >= m_size){ return false; } //false if input is invalid
    
    //Traverse the linked list with a counter (increments every time we move forward a node)
    //When that counter = pos, we will break.
    //After breaking, we will point at the item that we need to return
    Item* check = head;
    int counter = 0;
    while (check != nullptr){
        if(counter == pos){ break; }
        check = check->next;
        counter++;
    }
    // just in case
    if(check == nullptr){ return false;}
        
    value = check->m_item;
    return true;
}

void Set::swap(Set& other){
    //Just swap the head pointers, tail pointers, and size.
    //If we swap head and tail, the following list doesn't need to be changed. Each set just points to the other list now.
    Item* temp_h = head;
    head = other.head;
    other.head = temp_h;
    
    Item* temp_t = tail;
    tail = other.tail;
    other.tail = temp_t;
    
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
}

void unite(const Set& s1, const Set& s2, Set& result){
    result = s1;
    ItemType x;
    
    for(int i = 0; i < s2.size(); i++){
        s2.get(i,x);
        result.insert(x);
    }
    
   
    
    //PSEUDOCODE:
    //copy s1 into result using assignment operator
    //Loop over s2, insert s2 into result
    //We will get values from s2 using the get function
    //We don't need to worry about adding duplicates because insert has a check for that
    
}

void subtract(const Set& s1, const Set&s2, Set& result){
    result = s1;
    ItemType x;
    for(int i = 0; i < s1.size(); i++){
        s2.get(i,x);
        result.erase(x);
        
    }
    
    //PSEUDOCODE:
    //copy s1 into result using assignment operator
    //Traverse s2, erase s2 from result
    //We don't need to worry about subtracting elements that don't exist because we have a check for that
}

void Set::dump() const{
    Item* p = head;
    while(p != nullptr){
        cerr << p->m_item << " " << endl;
        p = p->next;
    }
}
