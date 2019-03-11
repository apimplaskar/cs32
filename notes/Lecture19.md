# Lecture 19
## March 11, 2019
---
### Big-O of deleting Open Hash table with B buckets and N values
- O(B+N)
- Can make it O(n) to thread all nodes in buckets into a doubly linked list
  - Must be doubly linked to make linking previous and next efficiently

### Tables
- Use a vector to store records
- Add a data structure that lets us associate each person's name with their slot # in the vector (assign indices)
- Can keep multiple indices (organized by different fields to allow for more efficient searching)
- Make sure that when we delete, we delete both from the vector as well as any index data structure (BST/Hash Table/etc.)
  - Similarly must account for any changes in a field
---
### Priority Queue
- Keep a prioritized list of items
- Each item that is inserted gets a PRIORITY RATING
- Any time you dequeue: dequeue the item with the highest priority (instead of just the first item)
- Operations:
  - Insert a new item, get value of highest priority, dequeue highest priority
- What data structure can we use?
  - What if we have 3 different priorities (high, medium , low)? USE 3 QUEUES!
  - What if we have a LOT of priorities?
    - BST sorted by priority? Must handle duplicates
    - HEAP

### Heap
- Special type of binary tree
  - NOT A BINARY SEARCH TREE
- Uses a complete binary tree
  - First n-1 levels are completely filled with nodes
  - Nodes in bottom-most level are as far left as possible
    - With no empty slots between nodes
- Two types:
  - Maxheap: quickly add a new item in heap, quickly retrieve largest item
  - Minheap: quickly add a new item, quickly retrieve the smallest item

### Maxheap
- Value contained by a node > = values contained by children
- COMPLETE BINARY TREE
- Largest item = at the top/root

- To extract the biggest item:
  1. If tree empty, return error
  2. Otherwise, top item = biggest value. Save it into a variable.
  3. If heap has only one node, delete it and return saved value.
  4. Copy value from right-most node in bottom-most row to the root node
  5. Delete bottom-most, right-most node
  6. Repeatedly swap just-moved value with the larger of its two children until the value is greater than or equal to both of its children ("sifting down")
  7. Return saved value to user

  O(logN) -- N items in tree, tree is logN levels deep. This returns a valid maxheap.
- How do we find the bottom-most, right-most item?
  - Use an array


- Adding a node to a maxheap:
  1. If the tree is empty: add a root node and return
  2. Otherwise, insert the new node in the bottom-most, left-most spot of the tree (still a complete tree)
  3. Compare new value with its parent's value:
  4. If the value is greater than that of its parent, swap
  5. Repeat until the value is at the right spot
    - This is called REHEAPIFICATION

### Implementing a Heap
- Every level of a tree has 2x the number of nodes as the previous level
  - EXCEPT FOR THE LAST LEVEL
- Copy nodes one level at a time into an array
  - Root node in arr[0]
  - Level one in arr[1] and arr[2]
  - And so on...
  - THIS ARRAY IS ISOMORPHIC TO THE BINARY TREE
  - Have a simple int (count) that keeps track of the number of elements
  - This means our heap has a max size (we can use a vector to let it grow)
- Properties of array-based tree:
  - Root value in heap[0]
  - Bottom-most, right-most node in heap[count-1]
  - Bottom-most, left-most open slot in heap[count]
  - Adding/removing node: heap[count] = value and update count
- Locating left and right children of a node using the array:
  - ex. Parent = 0, Left child = 1, Right child = 2
  - ex. Parent = 2, Left child = 5, Right child = 6
  - ex. Parent = 3, Left child = 7, Right child = 8
  - FORMULA:
    - Child slot = 2(parent) + 1 or 2(parent) + 2
    - Parent = (0.5)(child - 1)
      - Left v. right does not matter given integer cut off
- Extracting from a maxheap:
  - If count == 0, empty tree so return error
  - Otherwise heap[0] is biggest value, save it for later
  - If count == 1, set count to 0 and return the saved values
  - Otherwise, copy the value from the right-most, bottom-most node to the root
    - heap[0] = heap[count-1]
  - Delete the right-most node in the bottom-most row
    - count = count -1
  - Repeatedly swap with children until we reach the right spot
    - Start with i = 0
    - Compare heap[i] with heap[2i + 1] and heap[2i + 2]
  - Return the saved value
  - ON AN EXAM: Do this in a tree and then copy the tree back into the array
- Adding a node to the maxheap losing an array
  - Add new value into heap[count] and count++
  - Compare new value in heap[i] with heap[(i-1)/2]
    - If new value > parent: swap
  - Repeat until new value reaches appropriate slot
- Cost of inserting/extracting into maxheap: O(logN)
  - Worst case: SIFT/REHEAPIFY logN steps

### Minheap
- Value contained by a node < = values of children
- COMPLETE BINARY TREE
---
### Heapsort


** THE NAIVE VERSION **
- Insert N numbers into a maxheap
- While there are numbers left in the heap, remove the biggest number and place it in the last open slot
  - O(nlogN)
    - logN to add to heap, N items
    - NlogN to remove from heap


** EFFICIENT VERSION **
- Can avoid creating a whole new maxheap and moving numbers back and forth
- Convert input array into a maxheap
- While there are numbers in the heap, remove values and place in last open slot
