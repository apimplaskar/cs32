# Lecture 9
## Jan 30, 2019
---
## POLYMORPHISM

### Continued

```c++
class Person{...};
class Student : public person{...};
void LemonadeStand(Person &p);

Person john;
LemonadeStand(john); //works
Student alan;
LemonadeStand(alan);
//works, Student alan is derived from a person

```
A function that takes a REFERENCE TO base class as a parameter can also take classes derived from it. This function does NOT know about the derived nature of this object (unless it uses the virtual keyword), only the behavior based on the type that it takes as a parameter.

i.e. A function that takes a REFERENCE to a person can also take a student object as a parameter. The function only knows about the "person" parts of the object, not the "student" parts.

POLYMORPHISM: Using a base pointer/base reference to a derived object.
- MUST BE A REFERENCE OR A POINTER (not by value)

If we pass by value, it will perform *chopping*, where it chops off all of the subclass components, copies just the base class components, and then passes in the copy. In turn, our function may ignore the subclass nature of the item we pass in.

```c++
class Shape{
public:
  virtual double getArea(){ return 0; }
  //we will have new versions of this function in subclasses
  // has getX, setX, getY, setY
};

class Square : public Shape{
public:
  Square(int side) { m_side = side; }
  virtual double getArea(){ return m_side * m_side; }
  void setSide(int side){ m_side = side; }
private:
  int m_side;
};

class Circle : public Shape{
public:
  Circle(int rad){ m_rad = rad; }
  virtual double getArea() { return 3.14 * m_rad * m_rad; }
private:
  int m_rad;
};

/*
void PrintPriceSq(Square &x){
  cout << "Cost = " << x.getArea() * 3.25 << endl;
}

void PrintPriceCir(Circle &x){
  cout << "Cost = " << x.getArea() * 3.25 << endl;
}

//the two print price functions are identical, apart from arg
*/

void PrintPrice(Shape &x){
  cout << "Cost = " << x.getArea() * 3.25 << endl;
  //x.setSide(1);  THIS WILL FAIL
  //In terms of the fn, x is just a Shape
  //Can't access Square's setSide fn
}

int main(){
  Square s(5);
  Circle c(10);
  Shape sh;

  PrintPrice(s); //25, calls Square's getArea
  PrintPrice(c); //314, calls Circle's getArea
  PrintPrice(sh); //0, calls Shape's getArea;

}

```

In our example, since we made the getArea function virtual, when we call the PrintPrice item, we will use the correct version (correct arg type) of the PrintPrice function.
- ONLY IF WE USE VIRTUAL KEYWORD

INHERITANCE: Derive subclasses from a common base class. Deived class can inherit common set of functions from base class. Derived class can redefine functions from the base class using the virtual keyword (makes them subclass specific).

POLYMORPHISM: Can use a base pointer/reference to access ANY variable that is of the base type OR derived from the base class. It is the passing of a reference to a derived variable
to a function that accepts a base pointer/reference.

---
### Why polymorphism?
Design and implement systems that are easily extensible.

ex. The PrintPrice function from above can now be applied to ANY new shape subclass that we make.

Every time we access an object through a base reference, the referred-to object will always behave in the right way (i.e. don't need special case code).

---
### Forgetting the virtual keyword
The polymorphic function will only call the function on the base class.

USING THE VIRTUAL KEYWORD:
- Use virtual keyword in base class any time you expect to redefine a function in a derived class.
- Use the virtual keyword in derived classes any time we redefine a function.
- ALWAYS use the virtual keyword for destructors in your bas class (AND your derived classes).
- CANNOT have a virtual constructor.

---
### Polymorphism and pointers

Can I point a base class pointer at a derived class variable?
In the example, can we point a Shape pointer at a Square variable?

```c++
class Shape{
public:
  virtual double getArea(){ return 0; }
  //we will have new versions of this function in subclasses
  // has getX, setX, getY, setY
};

class Square : public Shape{
public:
  Square(int side) { m_side = side; }
  virtual double getArea(){ return m_side * m_side; }
  void setSide(int side){ m_side = side; }
private:
  int m_side;
};

class Circle : public Shape{
public:
  Circle(int rad){ m_rad = rad; }
  virtual double getArea() { return 3.14 * m_rad * m_rad; }
private:
  int m_rad;
};

int main(){

  Square s(5);
  Circle c(10);
  Shape * p;
  Shape * q;
  p = &s;
  q = new Square(3);
  //This pointer can only access Shape attributes
  //And virtual redefined behaviors

  p->getArea(); //works!
  //p->setSide; //FAILS!

  Shape sh;

  PrintPrice(s); //25, calls Square's getArea
  PrintPrice(c); //314, calls Circle's getArea
  PrintPrice(sh); //0, calls Shape's getArea;

}
```

CAN POINT ANY SUPERCLASS POINTER AT A DERIVED VARIABLE.

```c++
int main();
  Shape * shapeptr;
  char choice;

  cout << "square (s) or circle (c)" << endl;
  cin >> choice;

  if (choice == s){ shapeptr = new Square(3); }
  if (choice == c){ shapeptr = new Circle (3); }

  Circle c(1); Square s(2); Shape * arr[10];
  arr[0] = &c; arr[1] = &s;
  for(int i = 0; i < 2; i++){
    arr[i]->plot(); //plot all shapes in the array
  }
}
```

CAN WE POINT A SUBCLASS POINTER AT A BASE CLASS? No. That would assume that the base class behaves as a subclass.

---

### Virtual Destructors and Polymorphism:
ALWAYS have a virtual destructor when using poymorphism

```c++
class Prof{
public:
  Prof(){ m_myIQ = 95; }
  virtual ~Prof(){ cout << "I died smart: " << m_myIQ; }
private:
  int m_myIQ;
};

class MathProf : public Prof{
public:
  MathProf(){
    m_pTable = new int[6];
    for (int i = 0; i < 6; i++){
      m_pTable = i*i;
    }
  }
  virtual ~MathProf(){ delete [] m_pTable; }
private:
  int * m_pTable;
};

int main(){
  Prof * p;
  p = new MathProf;
  ...
  delete p;
}

```
Work flow:
- construct most basic to most derived
- destruct most derived to most basic

Construct Prof ->
Construct MathProf ->
Destruct MathProf ->
Destruct Prof

IF WE DON'T MAKE DESTRUCTORS VIRTUAL: Not specifically defined in C++.

Construct Prof ->
Construct MathProf ->
Destruct Prof

MEMORY LEAK from MathProf! This happens because our pointer is Prof pointer (NOT a MathProf pointer). If it were a MathProf pointer, it would work fine. In this case, C++ doesn't know that it is a MathProf, and it destructs as it would destruct a Prof object.

ONLY A PROBLEM if we have a base pointer pointing to a derived object and we use delete. (when not using virtual).

---
### How does it all work?
```c++
Class Shape{
public:
  virtual int getX() {return m_x;}
  virtual int getY() {return m_y;}
  virtual int getArea(){return 0;}
private:
  ...
}

Class Square : public Shape{
public:
  virtual int getArea(){
    return m_side * m_side;
  }
private:
  ...
};

int main(){
  Shape s;
  Square q;
  cout << s.getArea(); //uses shape v table
  Shape * p = &q;
  cout << p-> getArea(); //uses square's v table
}

```
Creates a v table for EVERY virtual function in the class. Pointers in the vtable point to functions defined with the virtual keyword, specifically pointing to the implementation that we will use. V table is used in run-time.

Shape's vtable:
- getX/Y/Area point to Shape's getX/Y/Area

Square's vtable:
- getX/Y point to Shape's getX/Y
- getArea points to Square's getArea

etc.

When we call a member function, it goes to the v table for a particular variable and refers to the correct version of the function.

---

### Summary of Polymorphism
- First figure out what we want to represent (ex. shapes)
- Define a base class with functions common to all derived subclasses
- Write derived classes with specialized version of common functions
- Access derived variables with base class pointer or reference
- Use virtual destructor

---

### Pure virtual functions

THE COMMON FUNCTIONS in the base class that will be specialized in sub classes are DUMMY FUNCTIONS (not meant to be called). They should return 0.

We HAVE to define functions in our base class in order to have them be common to all derived classes (when using polymorphism).

What if we could remove the dummy functions??

We can if we use a PURE VIRTUAL (abstract) functions. They don't have (or need) any actual body code. Says that the base version of the function is never called; the derived classes must implement it.

If we have even one pure virtual function in a class, we can't create variables of the base class.

```c++
class Shape{
public:
  virtual float getArea() = 0;
  virtual float getCircum() = 0;
  ...
};

int main(){
  Shape s; //CANNOT even define the variable
  cout << s.getArea(); // CANNOT call this
  cout << s.getCircum(); //CANNOT call this
}
```

MAKE A BASE CLASS FUNCTION PURE VIRTUAL IF: base-class version of function does nothing.

If we define at least one PURE VIRTUAL FUNCTION in a base class, our base class is now an "ABSTRACT BASE CLASS".
Abstract base classes cannot be used to define a regular variable.
