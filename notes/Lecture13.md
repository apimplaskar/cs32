# Lecture 13
## February 13, 2019
---
### The Map Class

Useful to find associations between A and B. Need unique entries on the LHS.  

Uses balanced binary search tree: makes it efficient to search using the left hand side.

Stored in alphabetical order
```c++
#include <map>
#include <string>
using namespace std;

int main(){
  map<string, int> name2Age;
  name2Age("c", 20);
  name2Age("b", 19);
  map<string, int>::iterator it;
  it = name2Age.find("b");
    //find only takes data type of left side
  if(it == name2Age.end()){
    cout << "not found";
    return
  }
  cout << (* it).first; //b
  cout << it -> second; //19
  it = name2Age.find("c");
  for(it = name2Age.begin(); it != name2Age.end(); it++){
    cout << it -> first << " " << it -> second << endl;
  }
  // b c
}
```

We can associate complex types like classes/structs with a map.

We must define an operator < for the left hand class/struct.
Check if a < b and if b < a to determine if a is </>/= to b. If you only have a class on the RHS, but the LHS is primitive, we don't need to define a < operator.

```c++
struct Student{
  string name;
  int idNum;
};

bool operator<(const Student &a, const Student &b){
  return (a.idNum < b.idNum);
}

int main(){
  map<Student, float> stud2GPA;
  stud d;
  d.name = "david";
  d.idNum = 912840928
  stud2GPA[d] = 1.3;
}
```
---
### Set
Keeps a unique set of item in order.

We can iterate through it just like we iterate through a map.

```c++
#include <set>
using namespace std;

struct Course{
  string name;
  int units;
};

bool operator<(const Course &a, const Course &b){
  return (a.name < b.name);
}

int main(){
  set<int> a;
  a.insert(2);
  a.insert(3);
  a.insert(4);
  a.insert(2); //doesn't do anything
  cout << a.size(); //4
  a.erase(2);

  set<int>::iterator it;
  it = a.find(2);
  if(it == a.end()){
    cout << "2 not found";
      return;
    }
  cout << "i found " << (* it);

  Course lec1;
  lec1.name = "CS32";
  lec1.units = 16;
  set<Course> myClasses;
  myClasses.insert(lec1);
}
```
---
### Deleting items from STL containers
Most STL containers have an erase() method that we can use to delete an item.
1. You search for the item you want to delete and get an iterator to it
2. Call erase on it

```c++
int main(){
  set<string> geeks;
  geeks.insert("carey");
  geeks.insert("asdfg");
  set<string>::iterator it;
  it = geeks.find("carey");
  if(it != geeks.end()){
    cout << "deleted " << * it;
    geeks.erase(it);
  }
}
```
---
### Iterator issues/gotchas
- If we point an iterator to an item in a vector, and we add/erase an item from the same vector
  - ITERATOR IS INVALIDATED
  - Run time error
  - Make sure you point iterator to something valid
- The same problem does not occur with sets/lists/maps
  - UNLESS: we erase the item that is pointed to by the iterator
---
### STL Algorithms
- find() method: can search most STL containers and arrays for a value
- set_intersection: compute the intersection of two sorted lists/arrays/sets
- sort (start, end): sort in ascending order (arrays and vectors)
  - Requires < operator for any non-primitive type

```c++
#include <vector>
#include <algorithm>

class Dog{
public:
  int getBark(){ return m_bark; }
  int getBite(){ return m_bite; }
private:
  int m_bark, m_bite;
};

bool customCompare(const Dog &a, const Dog &b){
  if(a.getBite > b.getBite()){ return true; }
  if(a.getBite < b.getBite()){ return false; }
  return (a.getBark > b.getBark);
}

int main(){
  vector<string> n;
  n.push_back("carey");
  n.push_back("bart");
  n.push_back("alex");

  sort(n.begin(), n.end()); // can also pass iterators

  Dog arr[4] = {...};
  sort(arr, arr+4, &customCompare);
    //use this instead of operator <

}
```
---
### Compound STL Data Structures
We want to maintain a list of courses for each UCLA Student
- Map of students to a list (or vector) of courses

```c++
#include <map>
#include <list>

class Course{
public:...
};

int main(){
  map<string, list<Course> > coursemap;
  Course c1("cs", "32");
  crsmap["student"].push_back(c1);
}
```

Associate a Person object with a set of friends (also Person objects)
- Map of Person objects to a set of persons
  - Would need to define < operator

Associate people with a group of courses that they have taken. Associate each course with the grade that they got.
- Map a Person to a map of a course that maps to a grade
- Need a < operator for course and person

```c++
class Person{
public:
  string getName();
  string getPhone();
};

bool operator < (const Person &a, const Person &b){
  return (a.getName < b.getName());
}

bool operator < (const Course &a, const Course &b){
  return a.getName < b.getName;
}

int main(){
  map <Person, set<Person> > facebook;
  map <Person, map<Course, string> > x;
}
```
---
---

### Algorithmic Analysis (Big O)
"How fast is that algorithm?"
- Can't use TIME (dep. on computer)
- Can't use number of instructions (dep. on size of data)

WE CAN USE: Number of instructions as a function of size of input data.
- This way we can compare algorithms for a given size input
- Predict performance of algorithm for data (different sizes)

Big-O measures an algorithm by gross number of steps that it requires to process an input of size N in the WORST CASE.
- Ignore coefficients and lower-order terms
  - Takes 5N^2 + 4N + 3 steps WILL BECOME Big O of N^2
  - Less specific but overall impression of worst-case efficiency

Use functions like lg(n), n, n^2, nlg(n), n^3, etc.

Determine number of operations in an algorithm:
- ex. Accessing an item, evaluate math expression, traverse singly linked list, etc.

Computing f(n) example:
```c++
int arr[n][n];
for(int i = 0; i < n; i++){
  for(int j = 0 j < n; j++){
    arr[i][j] = 0;
  }
}
```

1. Initialize value of n once
2. Compare i with n in the loop n times
3. i is incremented n times
4. j is initialized n times
5. j is compared with n in the inner loop n^2 times
6. j is incremented n^2 times
7. Set arr[i][j] to 0, n^2 times

f(n) = 3n^2 + 3n + 1.

So this is O(n^2)

COMPUTING BIG O:
- Determine f(n): number of steps
- Drop lower order terms
- Remove coefficients

BIG-O SIMPLIFICATION:
- Find the operation that runs the most number of times
- How many times does it run? That is big-O

Lg(n): if we are dividing in half things over and over

O(n^2) does NOT mean it runs in exactly n^2 steps: it is some number in the order of n^2.
