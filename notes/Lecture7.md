# Lecture 7
## January 25, 2019
---
### STACKS continued

When pushing:
- Store the new item in m_top'th element of arrays
- Post increment m_top

When popping:
- Decrement m_top
- return the item from the m_top'th element

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
      m_top--; //since m_top points to first OPEN spot
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

Stacks, linked lists, vectors, etc. are provided in the standard template library (STL).
```c++
#include <iostream>
#include <stack>
using namespace std;

int main(){
  stack<int> int_stack; // stack of ints

  int_stack.push(10);
  int_stack.push(20);

  cout << istack.top(); //get top value (20)

  int_stack.pop(); //get rid of top items

  if (!int_stack.empty()){ cout << int_stack.size(); }
  //is it empty? what is the size?
```

### STACKS ARE USED FOR:
- Storing undo items in word processor
- Evaluate math expressions
- Convert infix to postfix
- CPU has a built in stack to keep track of variables/functions

### Undo:
pushes each new modification

### POSTFIX EXPRESSIONS:

```c++
///IN | POST
15 + 6 | 15 6 +

9 - 4 | 9 4 -

(15+6) * 5 | 15 6 + 5 *
```

Easier to compute: unambiguous (no parentheses, etc.)

### Computing postfix
Input: post fix expression string

Output: number representing answer

Private data: Stack

Algorithm:

1. Start with left-most token

2. If it is a number:
  - push it to the Stack


3. Else, if the token is an operator:
  - Pop the top value into a variable called v2
  - Pop the second-to-top item into a variable called v1
    - The order of v2 and v1 matters in subtraction/division
  - Apply the operator to v1 and v2
  - Push the result on the stack


4. If there are more tokens, advance to the next token, go back to step 2

After all tokens have been processed, stack should only have ONE number. This is the output.


### Converting infix to postfix:
KNOW HOW TO DO THIS
Algorithm is in the slides

### Solving a maze
Input: 10x10 Maze in 2D array

Member variables: sx and sy coordinates, current curx, cury coordinates, and final points

Algorithm:

1) Push starting point onto stack

2) Mark starting point as "discovered"

3) If the stack is empty, there is NO SOLUTION

4) Pop the top off of the stack. This is our CURRENT location.

5) If current == endpoint, we are done.

6) If slot to west is open & undiscovered:
- Mark (curx-1, cury) as discovered
- Push (curx-1, cury) onto stack

7) Do the same for east, north, south if undiscovered and open.

8) GO TO STEP 3

THIS IS A DEPTH FIRST SEARCH. Goes as deep as it can, then retraces steps. Not a great solution.

---

### QUEUES
Used for:
- Optimal route navigation
- Streaming video buffering
- Flood-filling in paint programs
- Searching through mazes
- Tracking calls in call centers

Another ADT. More like a LINE. First item in is first out (FIFO).

Every queue has a front and a rear. Enqueue items at rear. Dequeue items from front.

Interface:
```c++
enqueue(int a); //adds to rear of queue
int dequeue(); //remove front item and return
bool isEmpty();
int size(); //num of items
int getFront(); //value of top item, without removing
```

### Using Queues to solve mazes
Breadth first search

Algorithm:

1) Insert starting point onto the queue

2) Mark starting point as "discovered"

3) If queue is empty: we are done, no solution

4) Remove top point from queue

5) Is current location == endpt? If yes, done. If not, keep going.

6) Check slot to west. If open and undiscovered:
  - Mark (curx-1, cury) = discovered
  - Insert it to queue (AT REAR)

7) Do the same for N, E, S

8) GO TO STEP 3

THIS IS MORE EFFICIENT FOR THIS PROBLEM

### Queue implementations
We can use an ARRAY and an INTEGER to represent a queue
- Every time you insert an item, place it in the rear slot and increment the rear count.
- Every time you dequeue an item, move all of the items forward in the array and decrement the rear count
- If we have n items in the queue:
  - Cost of inserting an item: 1 step ( O(1) )
  - Cost of dequeuing an item: n steps ( O(n) )

```c++
int queue[6], rear = 0;
```

We can use a linked list as well.

We can use a CIRCULAR QUEUE (array-based). We never need to shift items.

Private data: an array (arr), an integer (head), an integer (tail), an integer (count).

Algorithm:

1) Set count = head = tail = 0

2) To insert an item place it in arr[tail]. Increment tail and count.

3) To dequeue, we will fetch arr[head], increment head, and decrement count.

4) If head or tail exceed the end of the array, set it back to 0. Count adjusted accordingly.

- COUNT MUST ALWAYS BE SMALLER THAN THE SIZE OF THE ARRAY

### There is a queue in the STL
```c++
#include <iostream>
#include <queue>
using namespace std;

int main(){
  queue<int> iqueue; //queue of ints
  iqueue.push(10);
  iqueue.push(20);
  cout << iqueue.front(); //peeks front
  iqueue.pop(); //get rid of front item
  if(!iqueue.empty()){
    cout << iqueue.size();
  }
}
```
---
# Inheritance
A way to form new classes (instances of which are called objects) using classes that have already been defined.

Two classes have some member variables with same get/set functions and same purpose. Our new class may have some additional methods/data.

ex. class Person and class Student.

```c++
class Person{
public:
  string getName();
  void setName(string &n);
  int getAge();
  void setAge(int age);
private:
  string m_sName;
  int m_nAge;
};

class Student{
public:
  string getName();
  void setName(string &n);
  int getAge();
  void setAge(int age);
  int getStudentID();
  void setStudentID(int id);
  float getGPA();
private:
  string m_sName;
  int m_nAge;
  int m_nID;
  float m_fGPA;
};
```

We want to avoid code duplication (don't want to write a whole new class that is virtually identical).

What if we could define a new subclass (student) that inherits all of the functions/data from a superclass (person)? We could eliminate duplicate code.
