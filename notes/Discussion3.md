÷÷
# Discussion 3
## Feb 8, 2019
---
### Inheritance
- Can have subclasses of a base subclasses
  - Inherits member variables and member functions from base class
  - Can add other functional member variables and functions
- Inheritance uses an "is a" relationship, "has a" would use member variables
- Avoid duplicate code
- Motivation:
  - Reuse:
    - Reuse members of base class
  - Extension:
    - Create additional members/methods
  - Specialization
    - Existing functions catered for each subclasses
    - Use virtual keyword
    - Call most derived version
    - To call base class' version, BaseClass::method()

How do construction and destruction work?
- RECAP For a class: construct member variables, then run constructor body
- Construct base class first (member variables then constructor body), then member variables of subclass, then constructor body for subclasses
- Derived class destructor, destruct member variables of derived class, destructor of base class, destruct member variables of base class
- May need to use initializer list if base class does not have default constructor
  - subclass():base(parameter){}
---
### Polymorphism
- Can use a base class pointer/base class reference to refer to a derived object
  - ONLY works as a reference or pointer
- Subclass pointer/reference CANNOT refer to base class object
- Always have a virtual destructor (avoid memory leak).
- Pure virtual functions:
  - No actual code
  - Indicate that base class won't be called, but provides standard for use in subclasses
  - Syntax: virtual type func() = 0;
  - Force use of correct implementations
- Abstract base class:
  - At least one pure virtual functions
  - Cannot create an object of ABC
---
### Recursion
- Recursive function calls itself
- TWO RULES:
  - Have a base case: "stopping condition"
    - Simplest subproblem and its solution
    - Has to stop calling recursive function
  - Simplifying step:
    - Pass in a smaller subproblem
    - Want it to eventually reach the base case
- SHOULD NEVER USE GLOBAL/STATIC/MEMBER VARIABLES (stay self-contained)
  - Only use local variables/parameters

```c++
int fact(int n){
  if (n==0){ return 1; }
  return fact(n-1);
}

int fib(int n){
  if (n==1){ return 1; }
  if (n==2){ return 1; }
  return fib(n-2) + fib(n-1);
}

int movesHanoi(int n){
  if (n<1) { return -1; }
  if (n == 1){ return 1; }
  return 2*movesHanoi(n-1)+1;
}

void Hanoi(int n, char fromRod, char toRod, char auxRod){
  if(n==1){ cout << "move disc 1 from " << fromRod << " to rod " << toRod << endl; }
  Hanoi(n-1, fromRod, auxRod, toRod);
  cout << "move disc " << n << " from " << fromRod << " to " << toRod;
  Hanoi(n-1, auxRod, toRod, fromRod);
}
```
