# Discussion 1
## Jan 18
### TA: Manoj Reddy
### LA: Evan Lin (elin4046@gmail.com)
(This is not the discussion I am enrolled in. Talk to him about that)

---
### Debugging:

*Step in*: execute a line of code. if it is a function call, executes the function step by step.

*Step over*: Goes to next line

*Step out*: If in a function, complete that function and step to next routine/back to calling routine

*Continue/pause*: Run until you reach a breakpoint

Can view variable values in the lower left box. Function call stack in left hand column (hierarchy of function calls).

---

### Constructors

- Initialize every variable in your class (that may have random values by default).
- No return value.
- If we create an array of an object, the DEFAULT constructor is called on every element of the array.
- Build inner most object first (in order within scope), work our way out

### Destructors
- De-initialize/destruct class variables of an object when it is out of scope
- No return, no arguments
- Delete dynamically allocated variables, avoid memory leak
- Destruct outermost object first, work our way in (destruct in reverse order within scope)

### Initializer Lists
- Constructors can be overloaded based on the parameters that they take
- To initialize member variables
- Syntax: <Outerclass>(args): <member_class>(args)

### Copy Constructors
- Syntax: <Class name>(const <Class name>& <other>)

### Assignment Operator:
- Syntax: <Class name>& operator=(const <Class name>& <other)

```c++
class Person{
public:
  Person();
  Person(string n, int a);
  ~Person();
private:
  string name;
  int age;
};

class Animals{
  Animals(string nm, int ag):m_p1(nm, ag){ ... }
private:
  Person m_p1;
  Person m_p2;

}

Person::Person(){...}

Person::~Person(){...}

int main(){
  Animal a("dolly", 0);
    // before we construct a, we construct m_p1 followed by m_p2
    // destruct a, then m_p2, then m_p1
}

```
---
### Pointers
- Every variable has address in memory. Can access this using the & operator.
- Pointer = variable that stores address in memory
- Occupy 4/8 bytes depending on 32 v. 64-bit architecture
