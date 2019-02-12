# Lecture 5
## Jan 16
---
### Assignment Operator continued
Take an existing variable that has been constructed and assign it to another variable.
- Free memory held by target variable
- Determine how much memory source variable use
- Allocate same amount of memory in target variable
- Copy contents of source variable into the target
- Return reference to the target variable

We get a LOGICAL copy, but not necessarily EXACT copies.

```c++
class PiNerd{
public:
  PiNerd(int n){ ... }
  ~PiNerd(){ delete [] m_pi; }
  void showOff(){ ... }

  PiNerd & operator= (const PiNerd &src){
    delete [] m_pi;
    m_n = src.m_n;
    m_pi = new int[m_n];
    for (int i=0; i < m_n; i++){
      m_pi[i] = src.m_pi[i];
    }
    return * this;
  }
private:
  int *m_pi, m_n;
};

int main(){
  PiNerd ann(3);
  PiNerd ben(4);
  ben = ann;
} //ann's destructor called, then ben's destructor
```

Why do we return * this? So we can do multiple assignments in the same statement.

Assignment happens from right to left.
```c++
class Gassy{
public:
  ...
  Gassy &operator= (const Gassy &src){
    m_age = src.m_age;
    m_ateBeans = src.m_ateBeans;
    return * this;
  }
private:
  int m_age;
  bool m_ateBeans;
};

int main(){
  Gassy sam(5, false);
  Gassy ted(10, false);
  Gassy tim(3, true);
  tim = ted = sam; //first calls ted's assignment operator
  //* this returns a reference to the ted object
  // then second assignment is just tim = ted
}
```
An issue with the assignment operator: what if we assign a variable to itself?

The fix: In the assignment operator, CHECK TO SEE IF WE ARE ASSIGNING A VARIABLE TO ITSELF

Aliasing: refer to the same variable using different references/pointers.

```c++
class PiNerd{
public:
  PiNerd(int n){ ... }
  ~PiNerd(){ delete [] m_pi; }
  void showOff(){ ... }

  PiNerd & operator= (const PiNerd &src){
    if (&src == this){ return * this; }
    //don't do anything if assigning variable to itself

    delete [] m_pi;
    m_n = src.m_n;
    m_pi = new int[m_n];
    for (int i=0; i < m_n; i++){
      m_pi[i] = src.m_pi[i];
    }
    return * this;
  }
private:
  int *m_pi, m_n;
};

void f(PiNerd &x, PiNerd &y){
  x=y;
}

int main(){
  PiNerd ann(3);
  f(ann, ann);
  // Assignment operator u on the x ann (on the left)
  // Clears the memory for ann's array
  // sizes equated
  // re-allocated memory: has random values
  // now we copy in random values from the array to itself
  // we fix this by adding the if statement in the assign. op.
}
```
---
### Linked Lists

What if we don't know how many items we will have in an array beforehand? Then we have to reserve enough slots for the largest possible case. New/delete don't really help.

Also, what if we need to insert/delete a new element in the middle of the array? We'd have to move a bunch of elements which is extremely inefficient.

An approach that works better than a fixed-size array.
- Allows us to store an arbitrary number of items
- Easier to insert a new item in the middle
- Faster to delete from the middle

Organize as a "scavenger hunt". Clue -> item + clue -> item + clue -> item + clue -> ... ->  item + end.
- To add a new item: just add a new chest with a new item, copy the clue from the previous clue and add it to the new chest, replace the previous clue to point to the new location of the chest
- To delete a new item: take the chest before the one we want to delete, let that clue point to the item after the one we want to delete, get rid of the item we want to delete

In C++:
We can use a struct

THIS IS NOT HOW WE DO LINKED LISTS, Just a conceptual idea.

```c++
struct Chest{
  string treasure;
  Chest * nextChest;
  //each Chest variables holds pointer to another Chest variable
};
//Now we can define a chest for every item in the scavenger hunt

int main(){
  //Need a pointer to point to the first Chest
  Chest * first;
  Chest chest1, chest2, chest3;

  first = &chest1;
  chest1.treasure = "toast";
  chest1.nextChest = &chest2;
  chest2.treasure = "bacon";
  chest2.nextChest = &chest3;
  chest3.treasure = "eggs";
  chest3.nextChest = nullptr;

}
```

This data structure is called a linked list. It is called a linked list because every structure is linked by a pointer to the next element.

Each item in the linked list is called a *node*.
The top item in the linked list is called the *head pointer*.

Given just the head pointer, we should be able to get to every node in the linked list.

Normally, we don't create linked lists with local variables. Instead, we use dynamically-allocated variables (and pointers).

AGAIN, NOT HOW WE DO LINKED LISTS. JUST AN UNDERSTANDING.

```c++
struct Chest{
  string treasure;
  Chest * nextChest;
  //each Chest variables holds pointer to another Chest variable
};
//Now we can define a chest for every item in the scavenger hunt

int main(){
  Chest * head, * second, * third;
  head = new Chest;
  second = new Chest;
  third = new Chest;

  head -> treasure = "toast";
  head -> nextChest = second;
  second -> treasure = "bacon";
  second -> nextChest = third;
  third -> treasure = "eggs";
  third -> nextChest = nullptr;

  delete head;
  delete second;
  delete third;
}
```
As we said:

Each item in the linked list is called a *node*.
The top item in the linked list is called the *head pointer*.
The value held in a node is called *value*.
The linking pointer is called *next*. (next instead of nextChest).

There is no reason why a node would hold just one value.

Review:

```c++
Node *p = new Node; // allocate new Node
Node *q = new Node;

p -> value = "new" //change node's values
cout << p-> value;

p-> next = q; //link a node to another

Node *r = p-> next; //get the address of the node after p

q -> next = nullptr; // terminal node

//3 pointers and 2 nodes in this case

delete p;
delete q; // same as delete r;
//THIS DOES NOT GET RID OF THE POINTER
//GETS RID OF WHAT IS POINTED TO
```

Linked lists DO NOT NEED TO BE LINEAR.

```c++
struct Node{
  string value;
  Node * next;
};

class LinkedList{
public:
  LinkedList(){ head = nullptr; } //create empty linked list

  void addToFront(string v){
    Node * p = new Node; //allocate new node
    p->value = v; //add in value to node
    p->next = head; //link new node to old top nodes
    head = p; //head pointer links to new top node
  }

  void addToRear(string v){
    // case 1: empty linked list, same as adding node to top
    if (head = nullptr){
      addToFront(v);
    }

    // case 2: otherwise
    else{
      Node * p;
      p = head;
      // stop AT last node
      while(p->next != nullptr){
        p = p->next;
      }
      Node * q = new Node;
      q->value = v;
      p->next = q;
      q->next = nullptr;  
    }
  }

  void deleteItem(string v){ ... }

  bool findItem(string v){   
    Node * p;
    p = head;
    while(p != nullptr){
      if (p-> value = v) { return true; }
      p = p -> next;
    }
    return false;
  }

  void printItems(){ //loop over all nodes starting w head + print
    Node * p;
    p = head; //p points to first nodes
    while(p != nullptr){ //while p points to valid node
      //p goes PAST last node
      cout << p -> value;
      p = p -> next; //CAN'T USE p++
    }
    //This is a linked list traversal: go through every node
  }

  ~LinkedList(){ ... }

private:
  Node * head;
  int m_numNodes;
  // what if we had a tail pointer
}

int main(){
  LinkedList myList;
  // add a bunch of nodes
  myList.printItems(); // if we want
}
```
Linked list traversal: goes through every node.
