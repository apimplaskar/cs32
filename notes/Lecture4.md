### Lecture 4
## Jan 14, 2019

# New and delete for arrays:
Dynamic memory allocation allows us to reserve memory on the fly (in run time).
1. Define a pointer variable
2. Determine size of array needed
3. Use new command to reserve memory
4. Use pointer like the array
5. Delete/free the memory
  - If we forget to do this: memory leak until the entire program finishes running
  - Usage delete [] ptrname
    - Brackets to make sure that we use destructor if elements of array are objects
  - Frees memory at that address, BUT the pointer doesn't change: just delete what the pointer points to

If we try to allocate more memory than we have:
  - New command will throw an exception and crash
  - Or it will be a nullptr

Allocating a 2-d array:
  - Have an array of pointers, have each pointer point to an array

Smart pointers.

```c++
int main(){
  int size, * arr; //1
  cout << "how big?";
  cin >> size; //2

  arr = new int[size]; //3
  arr[0] = 10; //4
  * (arr + 1) = 11;
  //etc.

  delete [] arr; //5
  arr[0] = 50;
  //this could work, but we don't know what it would do
}
```

# New and delete for non-arrays:
Can use these commands to allocate different types of variables as well.

Dynamically allocating a class: we can provide parameters for the constructor in the new command.

```c++
struct Point{
  int x, y;
};
class Nerd{
public:
  Nerd(int IQ, int zits){
    m_IQ = IQ;
    m_zits = zits;
  }
  void saySomethingNerdy(){
    cout << "Something nerdy";
  }
private:
  int m_IQ;
  int m_zits;
}
int main(){
  //define pointer
  Point * ptr;
  //allocate dynamic variable
  ptr = new Point;
  //use the variable
  Point -> x = 50;
  (* ptr).y = 40;
  //delete
  delete ptr;

  Nerd * ptr;
  ptr = new Nerd(50,100);
  ptr -> saySomethingNerdy();
  delete ptr;
}
```
Using new and delete in a class

```c++
class PiNerd{
public:
  PiNerd(int n){
    m_pi = new int[n]; //allocate
    m_n = n; //store size

    for (int j=0; j < m_n; j++){
      m_pi[j] = getPiDigit(j);
    }
  }

  ~PiNerd(){
    delete[] m_pi; //free memory
  }

  void showOff(){
    for (int j=0; j<m_n;j++){
      cout << m_pi[j] << endl;
    }
  }

private:
  int * m_pi, m_n;
};
```

# Copy construction: Required in all nontrivial C++ programs

Useful to create a new variable from an old one.

```c++
class Point{
public:
  int m_x, m_y;
};

class Circ{
public:
  Circ(const Point &pt, int rad){
    //const means function can't modify pt (pt = a reference)
    //passed by reference
    m_x = pt.m_x;
    m_y = pt.m_y;
    m_rad = rad;
  }
  float GetArea(void) const;
private:
  float m_x, m_y, m_rad;
};

int main(){
  Point p;
  p.m_x = 7;
  p.m_y = 9;

  Circle c(p,3);
  cout << c.getArea();
  ...
}
```
What if we wanted to define a constructor for a circle that accepts another circle?

Can variable b access private variables/functions of variable a? YES.
Every Circ variable can access other Circ variable's private members. "Private" protects one class from another.
```c++
class Circ{
public:
  Circ(int x, int y, int r){
    m_x = x;
    m_y = y;
    m_rad = r;
  }

  Circ(const Point &pt, int rad){
    //const means function can't modify pt (pt = a reference)
    //passed by reference
    m_x = pt.m_x;
    m_y = pt.m_y;
    m_rad = rad;
  }

  Circ (const Circ &old){
    //allowed to access old's private members
    //as long as the classes are the same
    m_x = old.m_x;
    m_y = old.m_y;
    m_rad = old.m_rad;
  }

  float GetArea(void) const{
    return(3.14158*m_rad*m_rad);
  }
private:
  float m_x, m_y, m_rad;
};

void foo(Circ temp){
  cout << "Area is " << temp.GetArea();
}
int main(){
  Circ a(1,2,3);

  Circ b(a); //copy constructor
  Circ c = b; //copy constructor

  foo(a); //passed by value, uses copy constructor
}
```

COPY CONSTRUCTOR: a constructor that initializes a new variable from an existing variable
  - It takes another instance of the same class instead of regular values
  - Parameters SHOULD be const (don't modify old variable)
  - Parameters MUST be references
    - Passing by value makes copy of the variable, which uses the copy constructor
    - Making a copy of the variable also REQUIRES the copy constructor
    - Get caught in a loop that doesn't work
  - Parameter type must match type of destination variable
  -  USE A CONSTANT REFERENCE

We can also use a simpler syntax to call the copy constructor.
- Circ b(a) is the same as Circ b = a

Copy constructor is not just called when we initialize a new value. Also called when we pass by value.

SHALLOW COPY: If we don't define our own copy constructor, C++ provides a default one for us. Copies all of the member variables from the old instance to the new instance.

Why do we need to define our own if we can shallow copy? Can mess up pointers, dynamically allocated objects, etc.

If class holds pointers, file objects, network sockets, etc.: DEFINE OWN COPY CONSTRUCTOR (don't want shallow copy)

```c++
class PiNerd{
public:
  PiNerd(int n){
    m_pi = new int[n]; //allocate
    m_n = n; //store size

    for (int j=0; j < m_n; j++){
      m_pi[j] = getPiDigit(j);
    }
  }

  PiNerd(const PiNerd & src){
    m_n = src.m_n; //can directly copy size
    m_pi = new int[m_n]; //allocate new array

    for(int j = 0; j < m_n; j++){
      m_pi[j] = src.m_pi[j]; //copy elements into array
    }
  }

  ~PiNerd(){
    delete[] m_pi; //free memory
  }

  void showOff(){
    for (int j=0; j<m_n;j++){
      cout << m_pi[j] << endl;
    }
  }

private:
  int * m_pi, m_n;
};

int main(){
  PiNerd ann(3);
  if (...){
    PiNerd ben = ann;
    //shallow copy ann to ben
    //the m_pi pointers for both objects are identical
    //this is why we have defined our own copy constructor
    ...
  } //ben's destructor is called if shallow copies
  //array at ann's m_pi pointer also gets deleted!
  //our copy constructor makes sure ann's array stays
  ann.showOff();
}
```
---
# Assignment Operators
Change the value of an existing variable (that has already been constructed) to the value of another variable (unlike copy constructors which INITIALIZE a new variable with the value of another).

We use an assignment operator to copy the value of one existing variable into another existing variable.

C++ has a default shallow copy: directly copies everything.

Assignment operator:
- Function name is operator=
- Function return type is a reference to the class
- Use CONST REFERENCE as parameter
- Returns * this
- = sign is overloaded. If variable is of the object we define the operator/copy constructor for: we use alternate definitions of the =. If the object is new, = uses copy constructor. If it is an existing object, = uses assignment operator.

```c++

int main(){
  class Circ{
  public:
    Circ(int x, int y, int r){
      m_x = x;
      m_y = y;
      m_rad = r;
    }

    Circ(const Point &pt, int rad){
      //const means function can't modify pt (pt = a reference)
      //passed by reference
      m_x = pt.m_x;
      m_y = pt.m_y;
      m_rad = rad;
    }

    Circ (const Circ &old){
      //allowed to access old's private members
      //as long as the classes are the same
      m_x = old.m_x;
      m_y = old.m_y;
      m_rad = old.m_rad;
    }

    Circ & operator=(const Circ &src){
      m_x = src.m_x;
      m_y = src.m_y;
      m_rad = src.m_rad;

      return * this;
    }

    float GetArea(void) const{
      return(3.14158*m_rad*m_rad);
    }
  private:
    float m_x, m_y, m_rad;
  };

  Circ x(1,2,3);
  Circ y = x; // Copy construction, y is new

  Circ foo(1,2,3);
  Circ bar(4,5,6);
  bar = foo; //assigning to an existing variable
  //not copy constructed since bar already initialized
  //uses our assignment operator (for Circ objects)
  //bar.operator=(foo)

}
```
If we need a copy constructor, we need an assignment operator.
```c++
```c++
class PiNerd{
public:
  PiNerd(int n){
    m_pi = new int[n]; //allocate
    m_n = n; //store size

    for (int j=0; j < m_n; j++){
      m_pi[j] = getPiDigit(j);
    }
  }

  PiNerd(const PiNerd & src){
    m_n = src.m_n; //can directly copy size
    m_pi = new int[m_n]; //allocate new array

    for(int j = 0; j < m_n; j++){
      m_pi[j] = src.m_pi[j]; //copy elements into array
    }
  }

  PiNerd & operator=(const PiNerd &src){
    delete [] m_pi; //free original memory
    m_n = src.m_n; //copy src's size
    m_pi = new int[m_n]; //allocate new array

    for(int j = 0; j < m_n; j++){
      m_pi[j] = src.m_pi[j]; //copy elements into array
    }
    return * this;
  }

  ~PiNerd(){
    delete[] m_pi; //free memory
  }

  void showOff(){
    for (int j=0; j<m_n;j++){
      cout << m_pi[j] << endl;
    }
  }

private:
  int * m_pi, m_n;
};

int main(){
  PiNerd ann(3);
  Pi Nerd ben(4);
  ben = ann;
    // can't do this, ben's m_pi ptr to the array lost
    //ben's m_pi now points to the same as ann
}
//ann's destructor is called, ann's memory freed
//ben's destructor called
//tries to delete whatever replaced the memory ann freed
//ben's original reserved memory leaks


```
In the example above:
IN OUR ASSIGNMENT OPERATOR
- Free memory held onto by target variable (the one changing)
- Determine how much memory source variable uses
- Allocate same amount of memory for target
- Fill in, return * this
