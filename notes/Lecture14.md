# Lecture 14
## February 20, 2019
---
## Algorithmic Analysis contd.
### Big O contd.

*NOTE the base of the logarithm is omitted in these notes (as it does not matter for big O analysis). That being said, whatever we divide by (ex. split in half = base 2), will dictate the base of the log*

- Typical functions: n, n^2, log n, n log n, etc.
- No need to make super efficient algorithms for small problems
- Need to be thrifty/optimize if the problem is large
  - Don't prematurely optimize. Write simple code that works, then optimize.
- To avoid complications of loops that don't run a fixed number of iterations: just take the maximum possible iteration count

```c++
for (int i = 0; i < n; i+=2){ sum++; }
//O(n), runs through loop n/2 times

for(int i = 0; i < q; i++){
  for(int j = 0; j < q; j++){
    sum++;
  }
}
//O(q^2), runs through inner loops q^2 times

for(int i = 0; i < n; i++){
  for (int j = 0; j < n*n; j++){
    sum++;
  }
}
//O(n^3), runs through inner loop n^3 times

k = n;
while (k>1){
  sum++;
  k=k/2;
}
//O(log n), problem is halved every times so log base 2

for(int i = 0; i < n; i++){
  int k = n;
  while (k>1){
    sum++;
    k = k/3
  }
}
//O(nlogn), problem is split into a third every time
//the outer loop runs (but O(log base 3) = O(log base 2))

void foo(){
  int i, sum = 0;
  for (i = 0; i < n*n; i++){ sum += i; }
  for(i = 0; i < n*n*n; i++) { sum += i; }
}
//O(n^3), lower loop takes more iterations (n^3)

int searchArray(int arr[], int n, int forValue){
  for (int i = 0; i < n; i++){
    if (arr[i] == forValue){ return i; }
  }
  return -1;
}
//O(n)

void addToEndOfArray(int arr[], int &n, int addMe){
  arr[n] = addMe;
  n=n+1;
}
//O(1)

void mystery(int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < i; j++){
      cout << "a";
    }
  }
}
//O(n^2), Arithmetic sum (n*(n-1)/2)

for(int j = 0; j < q*q; j+++){
  for(int k = 0; k < j; k++){
    sum++;
  }
}
//O(q^4)

for(int i = 0; i<n; i++){
  for (int j = 0; j < i*i; j++){
    for(int k = 0; k < j; k++){
      sum++;
    }
  }
}
//O(n^5), n * n^2 * n^2

for(int i = 0; i < p; i++){
  for (int j = 0; j < i*i; j++){
    for (int k = 0; k < i; k++){
      sum++;
    }
  }
}
//O(n^4)

for(int i = 0; i < n; i++){
  Circ arr[n]; //n iterations, calls c'tor of class
  arr[i].setRadius(i); //n iterations
}
//O(n^2)

for (int i = 0; i < n; i++){
  int k = i;
  while (k>1){
    sum++;
    k=k/2;
  }
}
//O(nlogn)
```
---
### Multi-Input algorithms
If we have multiple independent variables, we must factor in ALL of them.

- Include all variables as one could dominate the other
  - Still get rid of lower order terms for EACH variable

```c++
void buffet(string ppl[], int p, string fds[], int f){
  int i,j;
  for (i = 0; i < p; i++){
    for(j = 0; j < f; j++){
      cout << ppl[i] << " ate " << fds[j] << endl;
    }
  }
}
//O(p*f)

void tinder(string csmaj[], int c, strings eemaj[], int e){
  for (int i = 0; i < c; i++){
    for (int j = 0; j < c; j++){
      cout << csmaj[i] << " " << csmaj[j];
    }
  }
  for (int k = 0; k < e; k++){ cout << eemaj[k]; }
}
//O(c^2 + e)

void tinder(string csmaj[], int c, strings eemaj[], int e){
  for (int i = 0; i < c; i++){
    for (int j = 0; j < c; j++){
      cout << csmaj[i] << " " << csmaj[j];
    }
  }
  for (int k = 0; k < e; k++){
    for(int l = 0; l < e; l++){
     cout << eemaj[k];
   }
  }
  for (int k = 0; k < e; k++){ cout << eemaj[k]; }
}
//O(c^2 + e^2)

void bar(int n, int q){
  for (int i=0; i < n*n; i++){
    for(int j = 0; j < q; j++){
      cout << "add";
    }
  }
}
//O(n^2*q)

void bletch(int n, int q){
  for (int i = 0; i < n; i++){ cout << "a"; }
  for (int i = 0; i < q*q; i++){ cout << "b"; }
}
//O(q^2+n)

void eh(int n){
  for (int i = 0; i < n; i++){ cout << "a";}
  for (int i = 0; i < n^2; i++){ cout << "b";}
}
//O(n^2)

void barf(int n, int q){
  for(int i = 0; i < n; i++){
    if (i == n/2){
      for(int k = 0; k < q; k++){ cout << "a"; }
    }
    else{ cout << "b"; }
  }
}
//O(n+q)
//Only run inner loop once
//The outer loop runs n times
```
---
### The STL and Big O
- Containers in the STL use algorithms to do things. We can examine Big O of these algorithms.
- set.find(item)
  - Requires O(logn)
  - Binary search
- vector.push_back(item)
  - O(1) if we just add to the back
  - We may need to reallocate a larger vector, but over time it is O(1)
- delete first item of vector
  - O(n), need to move up other elements

SEE STL/Big O CHEAT SHEET FOR Big O OF STL ALGORITHMS (In Carey's slides)

- When evaluating STL-based algorithms: find max number of items that each container will hold, then do the analysis

```c++
void printNums(vector<int> &v){
  int q=v.size();
  for(int i = 0; i < q; i++){ //q times
    int a = v[0]; //O(1)
    cout << a;
    v.erase(v.begin()); //O(n)
    v.push_back(a); //O(1)
  }
}
//O(q^2)

set <int> nums;
//variable size of nums as we insert
for (int i = 0; i < q; i++){
  nums.insert(i);
}
//O(q log q)

void clearFromFront(vector <int> v){
  //vector v has p items
  while(v.size() > 0){
    v.erase(v.begin()); //must shift up
  }
}
//O(p^2)

void addItems(set <int> &s, int q){
  for (int i = 0; i < q*q; i++){
    s.insert(i);
  }
}
//O(q^2 log (q^2)) = O(q^2 log q)

void clearFromBack(vector <int> &v){
  //z items in v
  while(v.size()>0){
    v.pop_back(); //O(1)
  }
}
//O(z)

```

ex.
vector<set<int>> v;

v has N sets in it.
Each set has an avg of Q items
1. check if set v[0] contains value of 7?

  O(log(Q))
2. if any set has value of 7?

  N(log(Q))
3. determine number of even values in all of v?

  O(NQ)
4. finding first set with a value of 7 and counting number of evens in that set?

  O(NlogQ + Q)

  - NlogQ finds first set with a 7, Q to loop over set

---
## Sorting Algorithms
- Ordering items based on some rule/subject to constraints
- We can sort anything and any number of items
- Can subject to any level of rules
- Algorithms will depend constraints (ex. on RAM or on disk, array or linked list, etc.)

RULES:
1. Do not choose algorithm until you understand problem requirement.
2. Choose the simplest algorithm possible that meets requirements.

### The inefficient ones:
Would not use them practically.

- SELECTION SORT
  1. Look at N books, select the shortest book = O(n)
  2. Swap shortest book with the first book
  3. Look at remaining N-1 books and find the shortest = O(n)
  4. Swap it with the second book
  5. Look at the remaining N-2 and find shortest
  6. Swap with third'
  7. And so on...

  If we have N books, this will take N^2 steps. It is NOT efficient.
