# Lecture 16
## Feb 27, 2019
---
### MergeSort
Before we learn the sorting algorithm, we need to go over the merging algorithm

- Merge function Information
  - Non-recursive function
  - Input: 2 sorted arrays, Output: 1 sorted array with elements from both input arrays
  - Need to use new command to allocate a temporary array
  - Input array does not pass in two separate sorted arrays
    - We pass in ONE array and two sizes (n1 is size of first "shelf" and n2 is size of second "shelf")


  - Merge ALGORITHM (code is in the slides)
    1. Initialize counter variables i1 and i2 to zero
    2. While there are more items to copy
      - If a1[i1] < a2[i2]: Copy a1[i1] to output array, i1++
      - Else: Copy a2[i2] to output, i2++;
    3. If either array runs out, copy the entire contents the other array to the output.


- MergeSort ALGORITHM
  1. If array has one element: return (it is sorted)
  2. Split the array into two equal sections
  3. Recursively call MergeSort on left half
  4. Recursively call MergeSort on right half
  5. Merge the two halves


- MergeSort Information
  - Can go log(n) levels deep - keep dividing in half until we reach one element
  - Merging takes n steps
  - MergeSort is O(nlogn) -- ALWAYS
  - Stability depends on implementation -- yes if you compare left side first

---
### CHALLENGE PROBLEMS
- Algorithm to efficiently determine which element occurs in the largest number of element in the array
  1. Map: map each int to a count of the number of times we saw that element in the array
  2. Order the array using a sorting algorithm. Then do a sweep that checks number of elements.

- Best algorithm to sort 1,000,000 random numbers that are all between 1-5
  1. Have an array of 5 slots, fill in array elements with counts of each integer in the set of random numbers
  2. Then we can fill in each element with the number of times it appears corresponding to the count in the array

---
## TREES
- Organize hierarchical data
- All trees have a head/root pointer
- Made of nodes
- Like a linked list, only we can have MULTIPLE pointers to next items
- Every node may have >= 0 CHILDREN nodes
- A node with 0 children is called a LEAF node
- A tree with no nodes is an EMPTY TREE (head/root = null)

### BINARY TREES
- Distinct from a binary search tree
- Each node has TWO children (a left and right child)
- Subtree = part of a tree that is rooted at that a particular node (the subtree of the root is the entire tree)
- Operations on trees:
  - Enumerate items, search for an item, add items at a certain position, delete items, cut a tree off at a particular point (pruning), etc.

```c++
struct BTNode{
  int value;
  BTNode* left, right;
};

int main(){
  BTNode* temp;
  BTNode* root;

  root -> value = 5;
  root->left = nullptr;
  root -> right = nullptr;

  temp = new BTNode;
  temp->value = 6;
  temp->left = nullptr;
  temp->right = nullptr;
  root->left = temp;
}
```
BINARY TREE TRAVERSAL
  - Start at the root node
  - 4 common ways to traverse a tree (most of them use recursion):
    - Pre-order traversal
    - In-order traversal
    - Post-order traversal
    - Level-order traversal
  - O(n) as we must visit each node exactly once

1. PRE-ORDER TRAVERSAL:
  - Process the current node
      - ex. print value, check value to see if it matches your value, incrementing a count, etc.
  - Recursively process the left subtree
  - Recursively process the right subtree
  - Pre-order because we process BEFORE we take a recursive step

  ```c++
  void preOrder(Node * cur){
    if(cur == nullptr){ return; }
    cout << cur->value;

    preOrder(cur->left);
    preOrder(cur->right);
  }
  ```
2. IN-ORDER TRAVERSAL:
  - Process the nodes in left subtree
  - Process current node
  - Process right subtree

  ```c++
  void inOrder(Node * cur){}
    if(cur == nullptr){ return; }
    inOrder(cur->left);
    cout << cur->value;
    inOrder(cur->right);
  }
  ```
3. POST-ORDER TRAVERSAL:
  - Process the nodes in left subtree
  - Process right subtree
  - Process current node

  ```c++
  void inOrder(Node * cur){}
    if(cur == nullptr){ return; }
    inOrder(cur->left);
    inOrder(cur->right);
    cout << cur->value;
  }
  ```

4. LEVEL-ORDER TRAVERSAL: NOT RECURSIVE, uses a queue
  - Like a Breadth-first search
  - Temp pointer variable and a queue of node pointers
  - Push root node into the queue
  - While the queue is not empty:
    - Dequeue top node pointer and put it into temp
    - Process the node
    - Push the node's children if they are not null to the queue


- Easy way to keep track of pre/in/post order traversal
  - Starting just above the left node, draw a loop CCW around all of the nodes
  - For a pre-order traversal: when drawing the loop, if you pass a node on its left, draw a dot on the left side of the node -- that is the order of the traversal
  - For an in-order traversal: if you pass a node and are under it, put a dot under the node -- that is the order
  - For a post-order traversal: if you pass a node on the right of it, put a dot there -- that is the order
- Level order traversal: go level by level, read from left to right.

EXPRESSION EVALUATION: using post order traversal
1. If current node is a number, return its value
2. Else, evaluate the left and right subtree and get the result. Apply the operator to the left and right results and return that result.

---
### Binary Search Trees
- Binary tree with the following properties
  - For every node X in the tree:
    - all nodes in the left sub-tree are less than X
    - all nodes in the right subtree are greater than X
- Operations:
  - Determine if it is empty, search for an element, insert/delete an item, find height, find number of nodes/leaves, traverse the binary search tree (act on all values in order on O(n) time)

SEARCHING A BST:
- Input a value v to search for
- Output: true if found, false if not
- WORST CASE O(n) -- effectively a linked list then

  IF BALANCED: every time we go down a link, we eliminate half of the tree -- O(logn)
- ALGORITHM:  
  1. Start at the root
  2. Keep going until we hit the nullptr
  3. CHECK!
    - If V = current node's value, found
    - If V less than current node, go left
      - Recursively call function on left OR iterate
    - If V greater than current node, go right
      - Recursively call function on right OR iterate
  4. If we hit a nullptr: not found.

INSERTING INTO A BST:
- Input: a value V to insert
- ALGORITHM
  1. If tree is empty:
    - Allocate a new node and put V into it
    - Point the root pointer at our new node, DONE!
  2. Start at the root of the tree.
  3. While we are not done:
    - If V is equal to current node's value, DONE! (don't need to do anything)
    - If V is less than current node's value, go left and check there
    - If V is greater than current node's value, go right and check there

- Can be done recursively or iteratively (below)

  ```c++
  class BST{
  public:
    BST(value){ m_root = nullptr; m_value = value; }
    void insert(const std::string &value){
      if (m_root == NULL){
        m_root = new Node(value); return; }
      }
      Node * cur = m_root;
      for (;;){
        if(value == cur->value){ return; }
        else if(value < cur->value){
          if(cur->left != NULL){
            cur = cur->left;
          }
          else{
            cur->left = newNode(value);
            return;
          }
        }
        else if(value > cur->value){
          if(cur->right != NULL){ cur = cur->right; }
          else{ cur->right = newNode(value); return; }
        }
      }
    }
  private:
    Node* m_root;
    string m_value;
  };

  ```
- Given a random array of numbers: inserting into BST = "bushy"
- Given an ordered array of numbers: inserting into BST will be like a "linked list"
  - DON'T USE A BST IF YOU HAVE ORDERED ARRAYS!
  - Insert in random order so that you can get a "bushy" tree
