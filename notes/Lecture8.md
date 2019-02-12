# Lecture 8
## January 28, 2019
---
# INHERITANCE Continued
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
Student is identical to a Person, but has more data/methods. We don't want to re-write code (avoid bugs, convenience, etc.).

Create a class that will inherit existing data/methods from another class. We can define a *subclass* that can inherit functions/data from a *superclass*.

HOW TO:

1) Define superclass and implement its member functions. (ex. First we define Robot)

2) Define subclass, explicitly basing it on the superclass

3) Add new functions/member variables as needed.

```c++
class Robot{
public:
  void setX(int newX){ m_x = newX; }
  int getX(){ return m_x; }
  void setY(int newY){ m_y = newY; }
  int getY(){ return m_y; }
private:
  int m_x, m_y;
};

class ShieldedRobot: public Robot{
public:
  //everything that Robot can do
  void setShield(int s){ m_shield = s; }
  int getShield(){ return m_shield; }
private:
  //everything that Robot has
  int m_shield;
}
```
A shielded robot *IS A TYPE OF* robot. "Is a type of" will use inheritance. Inheritance trees follow the "IS A" relationship. Top items are more generic. Get more and more specialized as we go down the tree.

On the other hand, a robot *HAS AN* x and y value. "Has" will be a private member variable.

TERMINOLOGY:

*Base class/superclass*: Class that serves as a basis for other classes

*Derived class/subclass*: Class that is derived from a base class.

You can inherit more than once.

``` c++
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

class Student:public Person{
public:
  //Person's functions
  int getStudentID();
  void setStudentID(int id);
  float getGPA();
private:
  //Person's members
  int m_nID;
  float m_fGPA;
};

class CSStudent:public Student{
public:
  //Student's functions
  void code();
private:
  //Student's members
  string m_code;
};
```


We use public inheritance. SYNTAX is class subclass:public superclass.

---
## Uses of Inheritance

### REUSE:
Write code once in base class and reuse it in subclasses.
- Public members in the base class and public in the derived class.
  - ONLY public members are exposed/reused
  - Have public accessors and mutators (get and set)
  - Private members are hidden from the derived class
- Can be used normally by any part of the program.

```c++
class Robot{
public:
  void setX(int newX){ m_x = newX; }
  int getX(){ return m_x; }
  void setY(int newY){ m_y = newY; }
  int getY(){ return m_y; }
protected:
  chargeBattery();
private:
  int m_x, m_y;
};

class ShieldedRobot: public Robot{
public:
  //everything that Robot can do
  void setShield(int s){ m_shield = s; }
  int getShield(){ return m_shield; }
  // int thisWontWork(){ m_x = 0; } //THIS FAILS

private:
  //everything that Robot has
  int m_shield;
};
```

If we want to call a "private" member function of the superclass in a subclass, but not in the rest of your program, we can make them PROTECTED instead of private.

Should not make data members public or protected.

Superclass A, subclass B

Public member function: any function in B (or subclass of B) can access it, all classes/functions unrelated to B can access it

Protected function: any function in B (or subclass of B) can access it, classes/functions unrelated to be cannot access it

Private member variable/function: cannot be accessed outside of A

If class is a friend of A, it can access protected/private members

### EXTENSION:
Add new behaviors/member functions/data to a derived class. All public extensions may be used normally by the rest of your program.

The base class cannot access extensions from the classes derived from it.

### SPECIALIZATION:
Redefine an existing behavior (FUNCTION) from the base class with a new behavior for the subclass.

We must use the VIRTUAL keyword in front of both function definitions (in base and subclasses). The functions must be identical (same return type, name, parameters).

Making things virtual slows down code. Don't make them virtual if you don't have to.

A redefined function hides the base version of the function.
If there is a subclass that does NOT redefine a function definition, it will use the most derived version. Also, if another function in the derived class calls the redefined function, it will use the most derived version.

If we define our member function outside of the class declaration, we only put virtual before the function declaration (NOT in the definition).

If we want to call the base version from a derived class, syntax is base::method();.

We can CALL the superclass' function prior to redefining it so that we can ADD to the output of the superclass' function.

```c++
class Student{
public:
  virtual void WhatDoISay();
  virtual string whatILike(){ return myFav; }
  ...
};

class UCLAStudent:public Student{
public:
  virtual void WhatDoISay(){ cout << "go bruins"; }
  ...
  virtual string whatILike(){
    string fav = Student::whatILike();
    fav += " bruins";
    return fav;
  }
  void saySchool(){ Student::WhatDoISay(); }
};

void::Student WhatDoISay(){ cout << "School"; }

int main(){
  Student s;
  UCLAStudent u;
  s.WhatDoISay(); //"School"
  u.WhatDoISay(); //"go bruins"
  u.Student::WhatDoISay(); //"School"
}
```
---
## Inheritance and Construction/Destruction
Constructors run from outside to inside. If we don't explicitly construct, we will have a default constructor.

The same goes for inheritance.

```c++
class Machine{...}
class Battery{...};
class Robot: public Machine{
public:
  Robot(){
    //m_bat's constructor
    m_x = m_y = 0;
  }
  ~Robot(){ m_bat.discharge; } //m_bat destructor
private:
  Battery m_bat;
  int m_x, m_y;

};
class ShieldedRobot: public Robot{
public:
  ShieldedRobot(){
    //initalize base part of object
    //m_sg c'tor
    m_shieldStrength = 1;
  }
  ~ShieldedRobot(){
    m_sg.turnGeneratorOff();
  } //m_sg destructor
  ...
private:
  int m_shieldStrength;
  ShieldGenerator m_sg;
};
class ShieldGenerator{...};

int main(){
  ShieldedRobot phyllis;
  //construct Robot
  //(construct machine then m_bat then rest of robot)
  //construct m_sg
  //then rest of ShieldedRobot
}
//destruct phyllis
//m_sg destructed
//shielded robot part destructed
//m_bat destructed
//robot destructed
//machine destructed
```

Construct base part, construct member classes, then derived object.

Destructor of outer object first, and then all member variables. Applies for derived objects as well. We destruct derived part first, base part second

Order of construction and destruction are EXACTLY opposite.

### Inheritance and initializer lists
```c++
class Animal(){
public:
  Animal(int lbs){m_lbs = lbs;}
  void wt(){cout << m_lbs << "lbs" << endl;}
private:
  int m_lbs;
};

class Stomach(){
public:
  Stomach(int size) { m_sz = size;}
private:
  int m_sz;
}
class Duck: public Animal(){
public:
  Duck(int lbs, int numF): Animal(lbs-1), m_stom(1){m_feathers=99;}
  void whoAmI(){ cout << "duck" <<endl;}
private:
  int m_feathers;
  Stomach m_stom;
};
```

If we don't have a default constructor for our superclass, we need to pass in a parameter when constructing the superclass. In turn, we MUST use an initializer list.

A class in only responsible for initializing the IMMEDIATE base class of itself. Base class MUST be the first thing in the initializer list (order initializer list in the order of construction).

### Inheritance and Assignment Operators
Will do a shallow copy: copy all data from base class first, copy all data from derived class next.

With dynamically allocated variables, it is ugly.

---
## Review
- Form new classes using existing classes that have already been defined
- REUSE: write code once in a base class, reuse it
- EXTENSION: add new behaviors/data to base classes
- SPECIALIZATION: redefine old behavior in base class to new behavior in derived class
  - Virtual key word

---
---
# POLYMORPHISM
- Goes hand-in-hand with inheritance.

Consider a function taking a Person as an argument
```c++
void LemonadeStand(Person &p){
  cout << "Hello " << p.getName();
  cout << "How many cups of lemonade do you want?";
}

//Student is a type of person

int main();
Person p;
LemonadeStand(p); //THIS WORKS
Student s;
LemonadeStand(s); //Does this work?? Yes, it is a subclass of person.
```
