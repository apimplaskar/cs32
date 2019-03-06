# Lecture 18
## Mar 6, 2019
---
### PROJECT 4
- Make a trie: each node is like a letter, we can keep going down a tree to examine a sequence.
- Example:
                    A
                  /   \
                T      G
              /   \
            G       C
---
### Practice Problem
You want to find a way to efficiently find out which sites a site links to, and also be able to efficiently locate a linked sites.

Average of N sites in keys, average of W sites linked to.

Can use map < string, Set < string > >

Checking if a.com links to b.com : logN + logW

Checking all sites that link to a.com: N*logW

---

### Modulus Operator
- Gives you remainder of dividing LHS by RHS
- X % n will yield results between 0 and n-1
---
## Hash tables
- Build an ADT that holds 9 digit student IDs
- Easy to add new IDs and determine if the ADT holds a particular ID in O(1) time
  - Faster than BST's logN time

### THE ALMOST HASH TABLE
```c++
class AlmostHashTable{
public:
  void addItem(int n){ m_array[n] = true; }
  bool holdsItem(int n){ return m_array[q] == true; }
  //does q exist = can just check if array[q] is true
private:
  bool m_array[1000000000]; //huge
  // true if a particular item exists, false if not
};

int main(){
  AlmostHashTable x;
  x.addItem(400683948);
}
```
- Inefficient because of how much space it uses. What if we could keep track a smaller array
- If we want 100,000 slots, we can no longer use the 9-digit number to index the array
  - Use a mathematical function that takes a 9-digit ID and converts it to a unique slot number between 0 and 999
    - Modulus! Called a hash function (takes one range and maps to another)

### THE ALMOST HASH TABLE 2.0
```c++
class AlmostHashTable2{
public:
  void addItem(int n){
    int bucket = hashFunc(n);
    m_array[bucket] = true;
  }
  bool containsItem(int n){
    int bucket = hashFunc(n);
    return m_array[bucket] == true;
  }
private:
  int hashFunc(int idNum){}
  bool m_array[100000];
};

```
- ISSUE: What if two numbers have the same result after the hash function

### HASH TABLES
- Closed Hash Table with Linear Probing
- Open Hash Table
---
### Closed Hash Table with Linear Probing
- INSERTION
  - We use our hash function to find the right bucket for insertion
  - If the target bucket is empty: we can store our value there
    - Not storing TRUE, storing THE WHOLE VALUE
  - If the target bucket is occupied:
    - Scan down from that bucket until we hit the first open bucket, put the new value there
    - If we hit the bottom bucket and it is filled, wrap around to the top
- SEARCHING:
  - Use hash function to find target bucket
  - If we find it there, done
  - If not, probe linearly down the array until we hit our value or an empty bucket
    - You either find it OR
    - Empty bucket = value is not in the array
- Addresses collisions by putting value as close as possible to the intended bucket
- DELETING:
  - Can't simply set an item's used to false: might prematurely abort search for items that are linearly probed lower
  - If you want to delete, avoid using a closed hash table!

```c++
struct Bucket{
  int value;
  bool used;
};

#define NUM_BUCK 10 //10 buckets
class HashTable{
public:
  void insert(int value){
    int bucket = hashFunc(value);
    for(int tries = 0; tries < NUM_BUCK; tries++){
      if(m_bucket[bucket].used == false){
        m_buckets[bucket].value = value;
        m_buckets[bucket].used = true;
        return;
      }
      bucket = (bucket+1)%NUM_BUCK;
      //the modulus here just makes sure we wrap around
      //i.e. if bucket = 10, we go back to 0
    }
    //no room left in hash table
  }
  bool search(int value){
    int bucket = hashFunc(value);
    for(int tries = 0; tries < NUM_BUCK; tries++){
      if(m_bucket[bucket].used == false)
        return false;
      if(m_bucket[bucket].value == value)
        return true;
      bucket = (bucket+1)%NUM_BUCK;
    }
    return false;
  }
private:
  int hashFunc(int value) const{
    return value % NUM_BUCK;
  }
  Bucket m_buckets[NUM_BUCK];
    //initialize bool of all buckets to false
};
```
- Can have additional data in a bucket, but can organize it using only ONE way (at a time)
---
### Open Hash Table
- Each bucket will now hold a linked list of values
  - Initialize every bucket to hold nullptr unless it points to a linked list after insertion
- INSERTING:
  - Compute a bucket using hash function
  - Add new value to the linked list at array[bucket]
  - DONE
- SEARCHING:
  - Search linked list at array[bucket] for the item
  - If you reach the end of the list without finding the item, the item is not in the table
- DELETIONS:
  - Just remove the value from the linked list
- Open Hash Table is better for insertion/deletion

---
### Hash Table Efficiency:
- Dependent on type, number of elements, number of collisions, etc.
  - Completely Empty/Sparse + CLOSED HASH TABLE:
    - INSERTION is O(1), SEARCHING is O(1)
  - Nearly full + CLOSED HASH TABLE:
    - INSERTION is O(n), SEARCHING is O(n)
- How big do we have to make our hash table to keep it near O(1)?
  - LOAD FACTOR: maximum number of values we intend to add divided by number of buckets in the array
  ```
  L = max values / total buckets
  ```
  - Load of 0.5 means array has 2x as many buckets as we intended
  - Max load for closed hash table = 1, max load for open hash table is infinite
- CLOSED HASH TABLE WITH LINEAR PROBING Efficiency
  - Given a particular load L, average # of tries to insert/find is
  ```
  0.5(1+ (1/(1-L))) for L < 1.0
  ```
  - For a load factor of 0.9, we still have an average of ~6 searches
- OPEN HASH TABLE
  - Average number of checks given particular load L:
  ```
  1+(L/2)
  ```
  - For a load factor of 0.9, we have an average of ~1.45 searches
- Open hash table are almost always more efficient
---
### Hash Table Sizing Problem
- We intend to store up to 1000 items in a hash table, and we want roughly 1.25 searches to find each item
  - Make it open: use the open hash table formula
  - 1+(L/2) = 1.25 so L = 0.5
  - If we need a load factor of 0.5 and 1000 items, our hash table should have **2000 buckets**


- Trade off:
  - BIG hash table takes up a lot of space but makes searching faster
  - SMALL hash table takes up less space but makes searching slower

- Try to choose a prime number of buckets for even distribution

---
### Hash Function for Strings
```c++
int hashFunc(string& name){
  int i, total = 0;
  for(int i=0; i < name.length(); i++){
    total = total+name[i];
  }
  total = total % HASH_TABLE_SIZE
  return(total);
}
```
- A bad function because anagrams will be put together even though they are different

```c++
int hashFunc(string& name){
  int i, total = 0;
  for(int i=0; i < name.length(); i++){
    total = total+ (i+1) * name[i];
  }
  total = total % HASH_TABLE_SIZE
  return(total);
}
```
- A little bit better

```c++
#include <functional>
unsigned int yourHashFunc(const std::string& hashMe){
  std::hash<std::string> str_hash; //create hasher
  unsigned int hashValue = str_hash(hashMe); //hash
  unsigned int bucketNum = hashValue%NUM_BUCKETS;
  //add our own modulo
  return bucketNum;
}
```
- The function above makes use of a hasher that has already been written -- by the pros!
---
### Hash Function for non-standard data type
NOT TRIVIAL. DEPENDS HEAVILY ON THE DATA WE ARE ANALYZING.

CRITERIA:
- For a given input, it should always return the same bucket
- Should disperse items in the hash array as evenly as possible
- Always measure how well it distributes items (use a histogram)
  - Want every bucket to be roughly equally likely to take a value

---
### The unordered_map: Hash based version of map
```c++
#include <unordered_map>
#include <iostream>
#include <string>
using namespace std::tr1; //required for hash based map
using namespace std;

int main(){
  unordered_map<string, int> hm;
  unordered_map<string,int>::iterator it;
  hm["Carey"] = 10;
  hm["David"] = 20;
  it = hm.find("Carey");
  if(it == hm.end()){ cout << "not found"; }
  else{ cout << it->first << " " << it->second; }
}
```
- CONSTANT TIME for searching/inserting, O(N) for traversal
  - As opposed to logN for maps
- As the name suggests, it's not in any order
---
## Tables
- A RECORD is like a struct: it has a bunch of FIELDS that hold values
- A bunch of RECORDS = a TABLE
- Though there may be identical entries in some fields, keep track of unique KEY FIELDS that can be used to distinguish records
- Creating a record in C++
  - Can use a struct/class
- Creating a table in C++
  - Create an array or vector
- Searching for a record with a particular value
  - Different functions to search by a particular field
- Why not create a whole C++ class for a table?


- Can we increase efficiency by storing in alphabetical order?
  - Can now use binary sort to search
  - Have to re-sort when adding an item
  - If you sort by one field, it is difficult to search by other fields
- What if we use a binary search tree?
  - We can still only use binary search on the field that we order by. It is still linear searching if we search by a different field.
  - What if we create a new table that is sorted by a different field? This takes up space!


- Making an efficient table:
  - We can still use a vector for our students
  - Add a secondary data structure that associates a field with their slot in the vector.
    - MAP
  - Now we have a BST by name to search for slot number, and then we can directly access that slot
  - We can add another data structure to associate another field with their slot in the vector!
    - MAP
