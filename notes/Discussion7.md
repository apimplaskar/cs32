# Discussion 7
## March 8, 2019
---
### HASH TABLES
- O(1) searching and insertion
  - FASTER THAN BST (O(logn) if balanced, O(n) if not)
- Hashing function:
  - f(INPUT) -> OUTPUT within a range of values
    - Output is independent of bucket size
  - Many to one functions
  - Input can be any sequence of bytes
- Modulo operator (%) -- remainder
  - [0,n-1] if X%n
  - Convert output to desired range
  - ex. 5%3 = 2, -1%3 = 2
- Hashing functions map from a larger space to a smaller space -- this gives us collisions
  - For any given X, hash(X) is ALWAYS the same (not a random function)
  - Values X1 and X2 can hash to the same value hash(X1) = hash(X2)
  - Good hash function:
    - quick to compute, minimize collisions, hard to reverse engineer (given hashed value, difficult to come up with input)
- XOR: do you exclusively have one value or the other?
  - (0,0) and (1,1) -> 0, (0,1) and (1,0) -> 1
---
### CLOSED HASH TABLE WITH LINEAR PROBING
- Closed: fixed size
- Linear probing: keep searching until you find an empty bucket from you hash index
  - We have a boolean that checks whether or not a bucket is used
- Lookup(X)
  - Hash X to get bucket number
  - Search linearly until you find your value or an empty bucket (wrap around if we hit the end of the array)
  - Worst case O(n)
- Insert(X)
  - Hash X to get bucket number
  - Insert value at next open bucket
  - Worst case O(n)
- Delete(X)
  - CAN'T REALLY DO THIS
  - Invalidates old hashing/can create an empty spot even though linearly probed areas might exist beyond that index (those slots are now inaccessible)
- Not conducive to resizing:
  - Will have to REHASH and insert according to new array size
---
### OPEN HASH TABLE
- Every bucket holds a pointer to a list
- Insert(X):
  - Hash X, add to the list in bucket X
  - Can insert as many as we want
- Lookup(X):
  - Hash X, search in the list
- Delete(X):
  - Hash X, search in list and delete it
---
### LOAD FACTOR
- L = (# of values we want to insert)/(# of buckets in the array)
  - L = 1, inserting exactly the same number of buckets in array
  - L always < = 1
- Average number of lookup tries:
  - Closed hash: 0.5(1+(1/(1-L)))
  - Open hash: 1 + (L/2)
  - Open hash tables are ALMOST ALWAYS more efficient than the closed ones
- More buckets decreases L, decreases average number of tries (use more space!)
- Choose a prime number of buckets: even distribution, decrease collisions
  - X%prime number has a more even spread
---
### SETTING THE NUMBER OF BUCKETS
- Given the approach, number of items to insert, and average number of tries: compute number of buckets
  - Compute load factor L = # items/ # buckets
  - Plug in to the lookup tries formula and solve for # buckets
---
### UNORDERED_MAP
- #include <unordered_map>
- Key is hashed
- Node struct:
  - key, value, pointer to next node
- Insert/lookup methods:
  - Hash(X)
  - Search the list though a traversal
---
### LA WORKSHEET
1. Given an array arr[0..n-1] of distinct elements and a range [low, high), use a hash table to find all numbers that are in the range, but not in the array. Print out the missing elements in sorted order. (F.Y.)

```c++
//WITHOUT HASH TABLE
void inRange(int arr[], int size, int low, int high){
  vector<int> found;
  bool found_it;
  for(int i = 0; i < size; i++){
    if(arr[i] >= low && arr[i] < high){
      found.push_back(arr[i]);
    }
  }
  for(int j = low; j < high; j++){
    for(int k = 0; k < found.size(); k++){
      if (j == found[k]){
        found_it = true;
        break;
      }
    }
    if(!found_it) {cout << j;}
  }  
}

//WITH HASH TABLE
#include <unordered_set>
void inRange(int arr[], int size, int low, int high){
  unordered_set<int> h;
  for(int i = 0; i < size; i++){
    h.insert(arr[i]);
  }
  for(int i = low; i < hi; i++){
    unordered_set<int>::iterator check;
    check = h.find(i);
    if(check == h.end()){ cout << i << " "; }
  }
}
```

2. Given an array of n integers, where each integer is guaranteed to be between 1 and 100 (inclusive) and duplicates are allowed, write a function to sort the array in O(n) time.
(Hint: the key to getting a sort faster than O(n log n) is to avoid directly comparing elements of the array!) (MV)

USE A TABLE OF VALUES AND FREQUENCIES

3. Given an array of integers and a target sum, determine if two integers in the array can be added together to equal the sum. The time complexity of your solution should be O(n) where n is the number of elements in the array. In other words, you cannot use the brute force method in which you compare each element with every other element using nested for loops.

```c++
#include <unordered_set>
bool twoSum(const int arr[], int n, int target){
  unordered_set<int> h;
  for(int i = 0; i < n; i++){
    h.insert(arr[i]);
  }
  for(int i = 0; i < n; i++){
    int one = arr[i];
    unordered_set<int>::iterator it1 = h.find(one)
    unordered_set<int>::iterator it2 = h.find(target - one);
    if(it1 != h.end() && it2 != h.end() && it1 != it2){
       return true;
     }
  }
  return false;
}

```

4. Given an vector of strings, group anagrams together. An anagram is a word formed by rearranging the letters of another, such as cinema formed by iceman. Return a vector of vectors of strings. Solve this problem using a hash table. You may assume only lower case letters.

APROACH:
- Unordered_map of string to string
  - Insert key = sorted word, value = actual word
- Loop over the input vector and insert into the map
- Loop over the map:
  - For each key, create a vector of the value strings
  - Push this vector of value strings into a vector of vectors (this will be returned)
