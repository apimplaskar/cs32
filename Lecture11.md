# Lecture 11
## Feb 6, 2019
---
### Recursion contd

```c++
int sumArr(int arr[], int n){
  if (n == 0) { return 0; }
  if (n == 1) { return arr[0];}
  return sumArr(arr, n/2) + sumArr(arr+(n/2), n-(n/2));
}

void reversePrint(int arr[], int n){
  if (n == 0){ return; }
  reversePrint(arr+1, n-1);
  cout << arr[0];
}

void forwardPrint(int arr[], int n){
  if(n==0) { return; }
  cout << arr[0];
  forwardPrint(arr+1, n-1);
}

int main(){
  const int n = 3;
  int nums[n] = {10,20,42};
  cout << sumArr(num, n);
}
```

Example 3:
Recursion on a linked list
- Instead of passing in a pointer to an array element, we pass in a pointer to a node
- Don't need to pass in a size value (size determined by following the pointers)
  - Look for next == null

FUNCTION TO FIND LARGEST NODE IN NON-EMPTY LINKED LIST

```c++
struct Node{
  int val;
  Node* next;
};

int biggest (Node* cur){
  if(cur -> next == nullptr){ return cur -> val; }

  //if (cur -> val > biggest(Node* cur -> next)){
    //return cur ->val;

  int rest = biggest(Node* cur->next);
  return max(cur->val, rest);

  }
}

/*
Magic function
int magicBig(Node *n){}
*/
```

RECURSIVE FUNCTION should generally only access current node/array element passed into it. Rarely/never access values in nodes cells below/after it.

Recursion can be extremely taxing when it comes to memory usage.

---

RECURSIVE BINARY SEARCH: (Divide and conquer)

Search(sortedWordList, findWord){

  If (no words in list) { DONE! not found. }

  Select middle word in middle list.

  If (findWord == middle word){ DONE! found.}

  If (findWord < middle word) { Search (first half of list)}

  Else (findWord > middle word){ Search (second half of list)}
}

```c++
//Helper function
int BS(string A[], int top, int bot, string f){
  if (top > bot) { return -1; }
  else{
    int Mid = (top + bot)/2;
    if (f == A[Mid]) { return Mid; }
    else if (f < A[Mid]) { return BS(A, top, Mid -1, f); }
    else if (f > A[Mid]) { return BS(A, Mid+1, bot, f); }
  }
}

//Simpler interface that can call a more confusing one
int simpleBS(string A[], int size, string findMe){
  return BS(A, 0, size-1, findMe);
}
```
---
Solving a maze (RECURSIVELY!):
- Similar to a solution using a stack (DFS)
  - Move down a path til it hits a dead end, backtrack until you find another available path

```c++
//globals
bool solvable;
int dcol, drow;
char m[11][11] = {} //array here

void solve(int row, int col){
  m[row][col] = '#';
  if (row == drow && col == dcol){
    solvable == true;
  }
  if(m[row-1][col] == ' '){ solve(row-1,col);}
  if(m[row+1][col] == ' '){ solve(row+1,col);}
  if(m[row1][col-1] == ' '){ solve(row,col-1);}
  if(m[row1][col+1] == ' '){ solve(row,col+1);}
}

int main(){
  solvable = false;
  drow = dcol = 10;
  solve (1,1);
  if (solvable == true){ cout << "true"; }
}

```
---
TIC TAC TOE
pickMoveForX and HowMuchCouldOHurtMe are working CO-RECURSIVELY.

Co-recursion: when two functions recursively call each other
```c++
Gameboard b;
while(!gameIsOver()){
  move = pickMoveForX(); //computer AI
  applyMove('X', move);

  move = GetHumanMove(); //human O
  applyMove('O', move);

}

pickMoveForX(){
  //For each legal X Move
  //IF X just won/tied: record and advance to next Move
  //result = HowMuchCouldOHurtMe();
  //Return best move for X (given ALL of O's moves)
}

HowMuchCouldOHurtMe(){
  //For each legal O move
  //If O won/tied, record and advance to next move
  //result = pickMoveForX
  //Return best move for O (given all of X's moves)
}
```
---
### REVIEW OBJECT ORIENTED DESIGN
---
### Generic Programming
- Build algorithms that operate on many different types of data

CUSTOM COMPARISON OPERATORS:
- Return bools
- Must pass in const parameters

``` c++
class Dog{
public:
  bool operator < (const Dog &other) const{
    if (m_weight < other.m_weight){ return true; }
    return false;
  }
  int getWeight() const{ return m_weight; }
private:
  int m_weight;
};

bool operator >= (const Dog &a, const Dog&b) const{
  if (a.getWeight() >= b.getweight()){ return true; }
  return false;
}
```
