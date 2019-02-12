# Lecture 3
## Jan 11, 2019 - Nachenberg
### Pointers Review

Pointer variable holds another variable's address instead of a regular value.

Changing a value using a pointer (not directly with the variable) := indirection.

Can use pointers to modify variables within a function or inside a different function.

```c++
int foo(){
  int idk;
  idk = 42;
  int * p; // pointer p
  p = & idk; // pointer p now holds address to idk
  cout << * p;
  // get address in pointer p, give me value stored there
  * p = 5;
  // get address in pointer p, store a value of 5 there

  int * a, b, c //a is a ptr, b and c are ints
  // The asterisk is associated with the VARIABLE
}
```
```c++
void set(int * px){
  * px = 5;
}
int main(){
  int x = 1;
  set(&x);
  cout << x;
}

// If we didn't use pointers in this case:
// we can't change values of variables in main's scope
```
Passing by reference: what really happens?
Simpler notation for passing by a pointer
```c++
void set(int &px){
  * px = 5;
}
int main(){
  int x = 1;
  set(&x);
  cout << x;
}
```
MISTAKE: we don't know where iptr points

SOLUTION: ALWAYS set the value of a pointer variable before using the * operator on it
```c++
int main(){
  int * iptr;
  * iptr = 123456;
  // We don't know what iptr points to (uninitialized)
}
```

Write a swap function that takes two pointers as arguments and swaps the values pointed to by the pointers.


```c++
void swap(*x, *y){
  int temp;
  temp = * y;
  * y = * x;
  * x = temp;
}

int main(){
  int a = 5, b = 6;
  swap(&a, &b);
  cout << a; // prints 6
  cout << b; // prints 5
  return 0;
}
```

Arrays, addresses and pointers:
Every array has an address in memory. But in C++, we do not use the & operator to get the address of an array. We just have to write the name of the array (without brackets) to gt the address.

Is nums in this case an address or a pointer? nums is just an array, but C++ lets you get its address without the & so it LOOKS like a pointer.

In C++, a pointer to an array can be used just as if it were an array itself.

``` c++
int main(){
  int nums[3] = {10,20,30}; //say it is stored at 9242
  cout << nums; // prints 9242

  int * ptr = nums; //ptr to array, holds 9242
  // ptr ++; //this will now point to 9246 (value of 20)

  cout << ptr[2]; // prints nums[2] or 30
  cout << * ptr; // prints value at start of nums array, 10
  cout << * (ptr + 2) // prints value at 9250, nums[2], 30

}
```

In C++, the two syntaxes have identical behavior:

"Go the address in ptr and skip down j elements (not j bytes, its j of whatever type we point to) --> give me the value there."

```c++
ptr[j] <-> *(ptr+j)
*(ptr+j) <-> *(j+ptr)
*(j + ptr) <-> j[ptr]
```

Pointer Arithmetic and Arrays:

When you pass an array to a function, you really just pass the address to the start of the array. Not passing the array itself.

```c++
void printData(int array[]){
  //we pass in the address of start of array
  cout << array[0] << endl;
  cout << array[1] << endl;
}

int main(){
  int nums[3] = {10,20,30}; //say starts at 3000
  printData(nums); // passes in 3000: OUT 10 new line 20
  printData(&nums[1]); // passes in 3004; OUT 20 endl 30
  printData(nums+1); // passes in 3004; OUT 20 endl 30
}
```

Pointers work with structures and classes too.
```c++
struct Nerd{
  int numZits;
  int hoursOfStarCraft;
};

int main(){
  Nerd carey;
  Nerd * ptr;
  ptr = & carey;

  (* ptr).numZits = 140;
  ptr -> hoursOfStarCraft = 5;
}
```
The this pointer:
```c++
class Wallet{
public:
  void Init();
  void AddBill(int amt);
private:
  int num1s, num5s;
};

void Wallet:Init(){
  num1s = num5s = 0;
}

//OR

void Init(Wallet *this){
  this -> num1s = this -> num5s = 0;
  cout << "I am at address: " << this;
}

void Wallet::AddBill(int amt){
  if (amt == 1){ num1s++; }
  else if (amt == 5){ num5s++; }
}

//OR

void AddBill(Wallet *this, int amt){
  if (amt == 1){ this -> num1s++; }
  else if (amt == 5){ this -> num5s++; }
}

int main(){
  Wallet a, b;
  a.Init();
    // This is really Init(&a)
  b.AddBill(5);
    // This is really AddBill(&b, 5)

  cout << "a is at address: " <<&a;
}
```

We can have pointers to functions as well. All functions have addresses in memory as well.

Syntax: return type (* ptr)(parameters)

```c++
void squared(int a){ cout << a*a; }
void cubed (int a){ cout << a*a*a; }

main(){
  void (*f)(int);
  f = &squared;
  // OR f = squared; can drop the ampersand
  f(10); // We can call the function indirectly, 100
  // Don't need to explicitly dereference
  // Though we can if we want

  f = &cubed;
  f(2); // 8
}
```
---
A new type of variable:
Thus far, all of our variables have been LOCAL, GLOBAL, or CLASS MEMBERS.

We also have DYNAMIC variables. Sometimes we don't know how many variables we need until the program runs. We can dynamically allocate memory to reserve new memory for variables. Operating system will allocate room for the variable in computer's free memory and then return the address of the new variable. We delete this used memory when we are done.

New command figures out how much memory it needs. Then the new command asks OS to reserve that many bytes of memory and assigns the address back to the pointer that we had. Then we can fill in the array.

```c++
int main(){
  int * arr; //create a ptr
  int size;
  cin >> size;

  arr = new int[size]; //new reserves memory for array
  // new command: type of array and number of slots
  // type of ptr must be same as type of array
  arr[0] = 10; // use ptr like an array
  arr[2] = 75; // can also use * notation

  delete [] arr; // free memory when done

}
```
