# CS 32 Lecture 1
## Jan 7, 2019
### Review of Classes

[Class website](http://cs.ucla.edu/classes/winter19/cs32/)

Interface: What we want to do
vs.
Implementation: How we do what we want


```c++
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

class Circle{
public:
  Circle(double x, double y, double r);
  bool scale(double factor);
  void draw();
  double radius() const;
    //Class invariant: m_r > 0
  private:
  double m_x;
  double m_y;
  double m_r;
}

double area(const Circle& x);
// Passing by constant reference is the alternative to passing by value

Circle::Circle(double x, double y, double r){
  m_x = x;
  m_y = y;
  if (r <= 0){
    cerr << "Cannot create a circle with radius " << r << endl;
    exit(1);
  }  
  //Can't have negative radius, don't want 0
  m_r = r;
}

double Circle::radius() const{
  return m_r;
}

bool Circle::scale(double factor){ //bool, did it work?
  if (factor  <= 0){ return false; }
  m_r * =  factor;
  return true;
}

void Circle::draw(){}

double area(const Circle& x){
  const double PI = 4 * atan(1.0);
  return PI * x.radius() * x.radius();
}

int main(){
  Circle c(8, -3, 3.7);
  Circle d(-2, -5, 10);
  d.scale(2)
  d.draw();
  cout << area(d);
  double e;
  cin >> e;
  if(!d.scale(e)){ //deal with error }
  d.scale(e);
}
```

C++ source program (.cpp)

---Compiler-->

produces object file (.o)

  DEFINES: main routine

  NEEDS: Circle constructor, functions within class Circle, functions like area, operator <<

libraries to define: strln, str.size, etc.

---Linker-->

Take object files and libraries to create executable file (a.out). The -o option gives us the executable name.

We'd see different types of errors (compilation errors vs. link errors)

---
Declaration of class in a Circle.h file
Declaration of all member functions in Circle.cpp file
Main in another file myapp.cpp

```c++
#include(Circle.h)
```
