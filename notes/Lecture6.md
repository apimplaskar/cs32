# Lecture 6
## Jan 23, 2019
---
### On exams:
- DRAW DIAGRAMS / THINK THROUGH PROBLEM BEFORE WRITING CODE
---
### Linked Lists contd.

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

  void addItem(string v){
    if (head = nullptr) { addToFront(v); }
    else if(/* new node is first element */){ addToFront(v); }
    else if(/* new node belongs in the middle */){
      Node * p = head;
      //traverse to find node above where we want to insert item
      while (p->next != nullptr){
        if( /* p points above where we want to insert */){
            // Allocate new node
            Node * latest = new Node;
            // Fill new node with item
            latest->value = v;
            // Link new node to the one beneath it
            latest->next = p->next;
            // Link new node into list right after the ABOVE node
            p->next = latest;
        }
        p = p->next
      }
    }
  }

  void deleteItem(string v){
    // case 0: if linked list is empty
    if (head = nullptr) { return; }
    //case 1: delete first node, first node holds item
    if (head -> value == v){
      Node * killMe = head;
      head = head ->next;
      delete killMe;
      return;
    }
    //case 2: delete any other node:
    Node * p = head;
    while (p != nullptr){
      if(p->next != nullptr && p->next->value == v) { break; }
      //p points to node above the one we want to delete
      p = p->next;
    }
    if(p != nullptr){ //only if we actually found our item
      Node * killMe = p->next; //addr. of target node
      p->next = p->next->next; // link nodes
      delete killMe;  //delete the node we want to get rid of
    }
  }

  bool findItem(string v){   
    Node * p;
    p = head;
    while(p != nullptr){
      if (p-> value == v) { return true; }
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

  ~LinkedList(){
    Node * p = head;
    while (p != nullptr){
      Node * deleteNext = p->next;
      delete p; //uses Node's default destructor
      p = deleteNext;
    }
  }

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

Limitations of linked lists:
- More complex than arrays
- Slow (takes n steps to add an item to the end, n-1 steps to reach nth item)
- We can fix the problem of it being difficult to add items to the end.

We can use a tail pointer to point at the last node.

```c++
class LinkedList{
public:
  void addToRear(string v){
    if (head == nullptr) { addToFront(v); }
    else{
      Node * n = new Node;
      n->value = v;
      tail->next = n;
      n->next = nullptr;
      tail = n;
    }

  }
private:
  Node * head;
  Node * tail;
};
```

### Doubly Linked Lists
- Simple linked lists can only be traversed in one direction (down, using the next pointer)
- Doubly-linked lists can move in both directions
  - Use next pointers for node below, previous pointers for node above

What changes?
- When adding/deleting nodes: Have to update THREE set of nodes (new node's next and previous, previous node's next, following node's previous)

```c++
struct Node{
  string value;
  Node * next;
  Node * previous;
};

class LinkedList{
public:
  ...
private:
  Node * head;
  Node * tail;
};

```
### LINKED LIST CHEAT SHEET
- Never access node's data until validating its validity
  - if (ptr != nullptr)
- To advance a pointer to the next node
  - ptr must != nullptr
  - ptr = ptr -> next
- See if ptr points to last node
  - (ptr != nullptr && ptr->next == nullptr)
- Get next node's data
  - ptr != nullptr && ptr->next != nullptr
  - ptr->next->value
- CHECK THE REST IN CAREY'S SLIDES

### Linked lists vs. arrays:
- Get to 753rd element: ARRAY IS BETTER
- Insert new item at front: LINKED LIST
- Removing item from middle: LINKED LIST
- Easier to program: ARRAYS

Situational convenience. If we CAN use both, use arrays (it's easier).

DO THE CLASS CHALLENGE AS A PROBLEM.

### Linked lists with Dummy nodes
- CHECK SLIDES

---
## STACKS AND QUEUES

### Stacks

- Useful abstract data type (ADT) that holds a collection of items where the elements are always added to one end
- Last item pushed onto top of the stack is the first item to be removed (last in, first off = LIFO)
- Stack operations:
  - Put something new on the top of the stack (PUSH)
  - Remove the top item (POP)
  - Look at top item without removing it
  - Check to see if stack is empty

```c++
const int SIZE = 100;

class Stack{ // of ints
public:
  Stack(){ m_top = 0; } //constructor

  void push(int i){
    if (m_top >= SIZE){ return; } //stack overflow
    else{
      m_stack[m_top] = i;
      m_top++;
    }
  }

  int pop(){
    if(m_top == 0){ return -1; } //underflow
    else{
      m_top--;
      return m_stack[m_top];
    }
  }

  bool isEmpty(){
    if(m_top == 0){ return true; }
    return false;
  }

  int peekTop(){
    if(m_top == 0){ return -1; }
    else{ return m_stack[m_top-1]; }
  }

private:
  int m_stack[SIZE];
  int m_top; //where NEXT item should be added
};

```
