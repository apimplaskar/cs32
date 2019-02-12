# Lecture 2
## Jan 9, 2019 - Nachenberg
---
Header file (.h), Implementation file (.cpp), main cpp (main.cpp). Include necessary files.

If we don't define a constructor explicitly, there is a default constructor. This default constructor will NOT initialize primitive member variables.

When are constructors called? Every time a new variable of a class is created. Called N times (one for each element) when an array of size N is created. Called when we use new to dynamically allocate a new variable. If declared in a loop, newly constructed for each iteration.

A pointer does NOT call the constructor.

``` c++
class Gassy{
  ...
}

int main(){
  Gassy carey(45, false), bill; //called once
  Gassy arr[52] //called 52 times
  Gassy * ptr = new Gassy(1,3); //called once
  for int(i = 0; i<10; i++){
    Gassy temp; //called once per iteration so 10 times
    ...
  }
  Gassy * justAPtr //this does NOT call the constructor
};
```

Destructors: just as every class has a constructor, every class also has a destructor. De-initializes class variable when it goes away (end of scope).

If we don't define one: C++ defines an implicit destructor for us.

When must you have a destructor? When a class allocates a system resource.
- Reserving memory using the new command --> delete
- Opening a disk file --> close the files
- Connect to another computer over the network --> disconnect

When is a destructor called? When the object goes out of scope. Dynamically allocated variables are ONLY destructed when we use the delete command.

``` c++
class Gassy{
public:
  ...
  ~Gassy(){
    for (int i=0;i<5;i++){
      cout << "gone!\n";
    }
  }
private:
  ...
};

void someFunc(){
  Gassy a; //constructor
  Gassy ar[52]; //constructor
  for(int i = 0; i<5; i++){
    Gassy temp; //constructor
  } //temp's destructor is called here

  Gassy * dyn_alloc = new Gassy; //constructor
  dyn_alloc --> //some functions
  delete dyn_alloc; //
} //a's destructor is called here
//ar's destructor is called here 52 times (works backwards)
```

Class composition: When a class contains one or more members that are objects (belong to other classes).
Using strings in classes is class composition!

``` c++
class GasTank{
  ...
}
class Car{
  GasTank myTank;
  int horsePower;
  string modelName;
}
class Garage{
  Car my_car;
}
};
```
How does construction work when we use class composition?
Which constructor runs first? HungryNerd constructor uses Brain and Stomach variables, which have constructors of their own.

When an outer object contains member objects, C++ automatically adds code to the outer object to FIRST call default (no parameters) constructors of all member objects. We construct from ("inside to outside").

What about destructors? Which destructor runs first in HungryNerd's destructor? Runs HungryNerd's destructor first and then Stomach and Brain's destructors are called.

When an outer object contains member objects, C++ runs the outer destructor first before running the inner objects' destructors. This occurs in the reverse of the order of construction (in order of declaration). We destruct from "outside to inside".

```c++
class Stomach{
public:
  Stomach(){ myGas = 0; }
  void eat() { myGas++; }
  ~Stomach() { cout << "stomach gone!\n"}
}

class Brain{
public:
  Brain() { myIQ = 100; }
  void think() { myIQ += 10;}
  ~Brain(){ cout << "brain gone!\n"}
};

class HungryNerd{
public:
  HungryNerd(){
    // call myBelly and myBrain's default constructors
    myBelly.eat();
    myBrain.think();
  }
  ~HungryNerd{
    myBelly.eat();
    myBrain.think();
    // call myBrain and myBelly's destructors
    //  Reverse order of construction
  }
private:
  Stomach myBelly;
  Brain myBrain;
};

int main(){
  HungryNerd carey;
}
```

Why do we have auto-generated constructors/destructors? This is to ensure that member objects are properly constructed and destructed.

If HungryNerd had implicit constructors and destructors, it would automatically add the default constructors and destructors for embedded object variables. It will NOT initialize primitive member variables.

If your class has primitives (ints, bools, floats, doubles, etc.), you should DEFINE YOUR OWN CONSTRUCTOR to INITIALIZE them.

MIDTERM PROBLEM: What is the order of construction?

A more complex example:
What if our embedded variables does not have a default constructor (one that requires a parameter)?

Compilation error if we try to run it as we did before. Now we use an initializer list. Colon after the closing parenthesis of the constructor, followed by initializer/parameter. Initializer list sets between prototype and body. Initializer list maintains the order of variable/embedded object definition in the object.

Usually initializer list should be ordered in the order that objects are compiled.

Initializer lists can also initialize primitive variables.
Initializer lists do not need to have constant parameters; we can pass in variables.

```c++
class Stomach(){
public:
  Stomach(int startGas){
    myGas = startGas
  }
  ~Stomach(){ cout << "no stomach!\n" ;}
  void eat(){ myGas++; }
private:
  int myGas;
};

class Brain{
public:
  Brain(int startIQ) { myIQ = startIQ; }
  void think() { myIQ += 10;}
  ~Brain(){ cout << "brain gone!\n"}
};


class HungryNerd(){
public:
  HungryNerd(int startingGas): myBelly(startingGas),
    myBrain(150), myAge(19)//initializer list
  // Tries to call myBelly's default constructor but CANNOT
  // because it does not have a default constructor so
  // we use the initializer list as above
  {
    myBelly.eat();
    myBrain.think(;)
  }
private:
  Stomach myBelly;
  Brain myBrain;
  int myAge;
}

```
---
### Pointers
Every variable has an address:
- Upon variable definition: compiler finds unused address in memory and reserves some memory to store it
  - The address of a variable is defined to be the LOWEST address in memory where the last variable is stored

We can get the address of a variable using the & operator.
- This is an overloaded operator (& has many meanings)

```c++
int main(){
  int age = 19;
  char grade = A;

  cout << "age's address: " << &age ;
  cout << "grade's address: " << &grade ;
}
```

Pointer: a variable that holds another variable's address instead of a regular value

```c++
int foo(){
  int idontknow; // a regular variable
  idontknow = 2; // holds regular value

  int * p; // pointer p
  p = &idontknow; // p holds address of idontknow

}
```
