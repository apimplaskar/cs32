# Discussion 4
## Feb 15, 2019
---
## TEMPLATES AND STL
### Generic Programming
More efficient and flexible

1. GENERIC COMPARISONS:
  - Can define ==, <, > , <=, >=, !=
  - Can only use public member variables if defined outside of the class
  - Can only compare with objects of the own type

  ```c++
  class C{
    bool operator<(const C &o) const{
      //since it is a constant object, have to declare as const
      if(m_int < o.m_int){ return true; }
      else{ return false; }
    }
    int get_int(){ return m_int; }
  private:
    m_int;
  };

  bool operator>(const C &a, const C &b){
    if(a.get_int() > b.get_int()){ return true; }
    else{ return false; }
  }
  ```

2. GENERIC FUNCTIONS:
  - Function takes generic parameter type
  - Compiler generates new version of function for every type
  - Don't assume that comparison operators, assignment operators, copy constructors are defined
  - Can also have multi-type templates
    - template < typename t1, typename t2 >
  - If you define a template, that type MUST be included in the parameter list
    - template < typename t1>
      - t1 func(int a); DOES NOT COMPILE
      - t1 func(t1 a); WORKS

  ```c++
  template <typename Item>
  void swap(Item &a, Item &b){
    Item temp = a;
    a = b;
    b = temp;
  }
  ```
3. GENERIC CLASSES
   - Classes containing template types
   - Same syntax as before
   - stack < type > , etc.
   - Different syntax if we define functions within or outside of class

   ```c++
   template <typename Item>
   class Test{
   public:
     void setVal(Item a);
     ...
   private:
     Item m_a;
   }

   template <typename Item>
   void Foo<Item>::setVal(Item a){
     m_a = a;
   }

   ```
4. STL (Standard Template Library)
  - Collection of pre-written classes that are provided
  - Class built using templates (can hold many different data types)
  - Stack, queue, vector, list, map, set
----
### STL
- VECTORS:
  - Acts as an array that resizes easily and can hold any type
  - vector < type > name(num_elements, init_value)
  - Can access elements using indices []
  - Insert: push_back (push item to the end of the vector, size incremented)
  - Remove: pop_back (remove last item)
  - Useful functions: empty(), size()

- LIST:
  - Works exactly like a linked list
  - Has push_back, pop_back, empty, size methods
  - Can't use [] to access elements, have to use iterator
    - Initialize with .begin() method (can also check for end())


- ITERATORS:
  - container < type > ::iterator it


- MAP:
  - Maps type 1 to type 2
  - map < type1, type 2 > name
  - Keys stored in a sorted manner

- SET:
  - Stores unique items

### STL Algorithms
- Work similarly
---
### Worksheet Problem

You are given an STL set< list < int >* >. In other words, you have a set of pointers, and each pointer points to a list of ints. Write a function that removes the lists with odd sums from the set. The lists with odd sums should be deleted from memory and their pointers should be removed the set. This function should also return the number of lists that are removed from the set.  If a list is empty, treat its sum as zero.  You may assume that none of the pointers is null.

```c++
int deleteOddSumLists(set< list< int > *> & s){
  set<list<int> * >::iterator s_it = s.begin();
  int count = 0;

  while (s_it != s.end()){
    int sum = 0;
    list <int> ::iterator l_it = (* s_it)->begin();

    while(l_it != (* s_it)->end()){
      sum += (* l_it);
      l_it++;
    }

    if(sum % 2 != 0){
      delete (* s_it);
      s_it = erase(s_it);
      count++
    }

    else{
      s_it++;
    }
  }
  return count;
}

```
---
---
## Big O / Complexity Analysis
- Determine complexity of an algorithm

EXAMPLE:

This follows an arithmetic series (0 + 1 + 2 + ... + n)

This is n(n+1)/2 WHICH IS O(n^2)
```c++
void func1(int n){
  for (int i = 0; i < n; i++){
    for(int j = 0; j < i; j++){
      cout << j;
    }
  }
}
```
- For multi-input algorithms: include each independent variable.
  - i.e. O(m+n) for m and n being two different variables
- Traversing a linked list: O(n)
- 
