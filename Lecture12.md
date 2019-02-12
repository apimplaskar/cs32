# Lecture 12
## Feb 11, 2019
---
### Custom Comparison Operators contd.
Define custom comparison operator for any class/struct that is defined

NEED THE CONST KEYWORD
```c++
class Dog{
public:
  int getWeight () const{ return m_weight; }
  bool operator < (const Dog &other) const{
    if(m_weight < other.m_weight){ return true;}
    return false;
  }
private:
  int m_weight;
}

bool operator >= (const Dog &a, const Dog &b){
  if(a.getWeight >= b.getWeight){ return true; }
  return false;
}
```
---
### Writing Generic Functions
Swap functions:

We will use C++'s template feature.
Always place ENTIRE template functions in a header file.
```c++
template <class Item>
template <typename Item>
void swap(Item &a, Item &b){
  Item temp;
  temp = a;
  a = b;
  b= temp;
}

template <typename Data>
Data func(int i); //INVALID
```

Every time we call this function on a new data type, compiler creates a NEW VERSION of the function.

The template data type must define at least one formal PARAMETER or we will get an error.

If a function has 2+ templated parameters with the same type, we must pass in the same type of variable/value for both.

We can override a templated function with a specialized function.

In the example, top one is used generically, but bottom one is used for dogs specifically.

```c++
template <typename Data>
Data bigger(Data &x, Data &y){
  if(x>y){ return x; }
  else {return y;}
}

Dog bigger(Dog &x, Dog &y){
  ...
}
```

If the template function uses a comparison operator and you pass in a class, the class must have a user defined comparison operator.

---
### Writing Generic Classes
```c++
template <typename Item>
class HoldOneVal{
public:
  void setVal(Item a);
  void print(){ cout << m_a; }
private:
  Item m_a;
};

template <typename Item>
void HoldOneVal<Item>::setVal(Item a){
  m_a = a;
}

HoldOneVal<int> v1;
...

```

In classes with externally-defined member functions, see syntax above.

---
### Template linked lists
Don't need to make a new one for each type. We can make a generic one.

---
### Standard Template Library (STL)

Collection of pre-written, pre-tested classes provided.

Container classes: stack, queue, linked list, etc.

1) VECTOR: Like an array that can grow and shrink
  - All values are initialized
  - Add an item: push_back
  - Can use [] operator to access elements/change values
  - Access front/back elements (front(), back())
  - Remove last item and shrink vector: pop_back
  - Accessing invalid elements: CRASH

They can grow: if you fill array, allocate new larger (2x size) array and copies old array over (size grows exponentially)

```c++
#include <vector>
int main(){
  vector <string> str;
  str.push_back("str1");
  str.push_back("str2");
  str[1] = "new str2";
  cout << str[0]; //str1
  str.push_back("last");
  cout << str.back(); //last
  cout << str.front(); //str1
  str.pop_back(); //removes last
  cout << str.size(); //2
  cout << str.empty(); //false

  vector <int> int(2,444); //size two, initialized to 444
  vector<Robot> robots;
}
```

2)LIST: just like a linked list

When to use a vector:
  - Random access

Using a list:
  - Add to bottom, don't need []

Can make a list for a struct/class

Iterating through elements of a list/other container:
- To enumerate: we can use an iterator variable
- Like a pointer but used with STL containers
- Begin method will point to the first element (begin())
- * iterator = element iterator points to (OPERATOR OVERLOAD)
- End method points AFTER last item (end())


```c++
#include <list>
using namespace std;
int main(){
  list <float> lf;
  lf.push_back(1.1);
  lf.push_back(2.2);
  lf.push_front(3.3);

  list<float> :: iterator it;
  it = lf.begin();
  cout << * it; //3.3
  it = lf.end();
  it--;
  cout << * it; //2.2

  it = lf.begin();
  while (it != myVec.end()){
    cout << * it;
    it++;
  }
}
```

How to use iterators:

```c++

void func(const list<string> &nerds{
  list<string>::const_iterator itr;
  for (itr = nerds.begin(); itr != nerds.end(); itr++){
    cout << *itr << endl;
  }
}

int main(){
  nerds.push_back("a");
  nerds.push_back("b");
  func(nerds);
}
```

STL Iterators:
- Represents some information that points to a container
- Has a hidden node structure

---

```c++
#include <map>
#include <string>
using namespace std;

int main(){
  map<string, int> name2Phone;
  name2Phone["a"] = "1234567890";
  name2Phone["b"] = "0987654321";

  map<int, string> phone2Name;
  //do it the other way around

  map<string, int>:: iterator it; 

}
```
### MAP

Associate two related values.

ex. name, and phone numbers

Redef. of [] operator.

Will only associate in one direction

- Store each association in a struct variable. This struct has a pair that matches one to the other.
- Ordered by the first field type.
- Can use brackets to change values.
- Uses a balanced binary search tree.
