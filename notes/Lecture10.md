# Lecture 10
## Feb 4, 2019
---
### Abstract Base Classes (ABC):
- At least one function that is pure virtual
- If we define an abstract base class:
  - Must either provide CODE for ALL pure virtual functions
  - OR the derived class becomes an ABC itself

```c++
class Robot{ //ABC
public:
  virtual void talkToMe() = 0;
  virtual int getWeight() = 0;
};

class KillerRobot:public Robot{ //NOT AN ABC
public:
  virtual void talkToMe() { cout << "hello"; }
  virtual int getWeight() { return 100; }
};

class FriendlyRobot: public Robot{ //ABC
public:
  virtual void talkToMe() { cout << "hi"; }
  //cannot call getWeight
};

class BigHappyRobot: public FriendlyRobot{ //not ABC
public:
  virtual int getWeight() { return 500; }
};
```

We can still use polymorphism on ABCs. Can use a base class reference/base class pointer to point to an object of a derived class.
```c++
int main(){
  Robot * ptr1 = new KillerRobot;
  FriendlyRobot * ptr2 = new BigHappyRobot;
  ptr1 -> talkToMe(); //hi
  ptr2 -> getWeight(); //500
  delete ptr1; delete ptr2;
}
```

*ALWAYS HAVE VIRTUAL DESTRUCTORS*

---
### Recursion:
Use same algorithm on smaller and smaller subproblems until we reach a solution (i.e calls itself on a smaller subset of itself).

- Merge Sort
  ```c++
  void MergeSort(an array){
    if (array_size == 1){ return; } //1 item is sorted
    MergeSort(first half of array); //process 1st half
    MergeSort(second half of array); //process 2nd half
    Merge(the two array halves); //merge sorted halves
    //complete array is sorted
  }
  ```

The function call MUST work properly on the subset of data.

RULES OF RECURSION:
- Have a stopping condition (BASE CASE)
  - May be more than one
- Have a simplifying step
  - Every time the recursive function calls itself, it must pass a sub-problem; eventually reach the base case
  - Most recursive functions simplify input BY:
    - Dividing in half (like MergeSort)
    - Or subtracting one
- Should NOT use global variables, static variables, or member variables
  - Use local variables and parameters

WRITING OUR OWN RECURSIVE FUNCTIONS
1. write function header
2. define "magic" function
3. add base case code
4. solve problem
5. remove "magic"
6. validate

Ex. FACTORIAL
```c++
int factorial(int n){
  if (n == 0) { return 1; }
  return n * factorial(n-1);
}
```

Ex. RECURSION ON AN ARRAY:
Sum up all of the items
```c++
int sumArr(int arr[], int n){
  if (n == 0){ return 0; }
  if (n == 1){ return arr[0]; }
  //return arrSum(arr, n-1) + arr[n-1]; //front to back
  //return arrSum(arr+1, n-1) + arr[0]; //back to front
  return arrSum(arr, n/2) + arrSum(arr+(n/2), n-(n/2));
  //divide and conquer
}
```
