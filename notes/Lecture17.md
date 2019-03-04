# Lecture 17
## Mar 4, 2019
---
### Binary Search Trees
- Big O of BST insertion:
  - Search (where we would insert) is log(N) -- Then insert is log(1)
  - Assuming a balanced binary search tree: log(N)
- Finding maximum item: keep following right pointers
- Find minimum: follow left pointers
- Print a BST in alphabetical order: use an in-order traversal
  - Big O: O(N) -- all traversals are O(N)
- How to free the whole tree: post-order traversal
  - O(N) -- traversal

```c++
void FreeTree(Node* cur){
  if (cur == nullptr){ return; }
  FreeTree(cur->left);
  FreeTree(cur->right);
  delete cur;
}
```
---
### Deleting a node from a BST
ALGORITHM: Given a value V that we want to delete

Time complexity: O(log(N))

1. Find the value V in the tree with a slightly modified BST search (keep track of current and parent pointer)
  - Parent = nullptr, cur = root
  - while(cur != nullptr)
    - if (v == cur->value) -- done
    - if (v < cur->value) -- parent = cur, cur = cur->left
    - if (v > cur->value) -- parent = cur, cur = cur->right
2. If node was found, delete it
  - Case 1: node is a leaf (easy)
    - Subcase 1: target node is not the root node
      - Unlink parent node by setting L/R pointer to nullptr
      - delete cur
    - Subcase 2: target node is the root node
      - set root ptr to null
      - delete cur
  - Case 2: node has one child (less easy, still easy)
    - Subcase 1: target node is not the root node
      - relink parent node to the cur's only child
      - delete cur
    - Subcase 2: target node is the root node
      - set root to its only child
      - delete cur
  - Case 3: node has two children (hard)
    - We don't delete the node K itself, we will just replace the value in the current node with either:
      - K's left subtree's largest-value child
      - K's right subtree's smallest-value child
    - Need to delete the node whose value replaced K using case 1/2
---
### Uses of Binary Search Trees
- Used by STL map and set
- ASCII = Representation of letters/punctuations/digits with a number
- These numbers are stored in binary
- Huffman Encoding:
  - Compute frequency of every character in a file
  - Build a Huffman tree (binary) based on frequencies
    - Create a leaf node for every letter
    - While we have more than one node left:
      - Find two nodes with lowest frequencies
      - Create a new parent node
      - Link parent node to each of the children
      - Set the parent's total frequency equal to the sum of its children's
      - Place the new parent node in our grouping
  - Label each left edge with a 0, right edge with a 1
  - Now we can encode characters as 0s and 1s to that letter
    - Higher frequency letters: fewer bits
- Decoding:
  - Extract encoding scheme from compressed file
  - Build Huffman tree based on encodings
  - Use binary tree to convert compressed characters to original
  - Save converted (uncompressed) file

- Lempel Ziv compression (.zip)
- Lossy compression (.jpeg) -- from Fourier transforms
---
### A function that takes in the head of a binary tree and finds depth
```c++
int findBTDepth(Node* cur){
  if(cur == nullptr) { return 0; }
  if (cur -> left == nullptr && cur -> right == nullptr)
    { return 1; }

  int depthL = findBTDepth(cur->left);
  int depthR = findBTDepth(cur->right);
  if(depthL > depthR){ return 1+depthL; }
  else{ return 1+depthR;}
}
```
---
### Balanced Binary Search Trees
- Maintain balance so that operations are log(N)
  - Insertion, deletion, searching
- 2-3 trees, Red-Black trees, AVL trees, etc.
- AVL Tree: keeps track of heights of ALL subtrees (of every node in the tree)
  - Shift nodes to maintain the balance
    - log(N) time to shift
---
### Hash Tables
- Consider a BST that holds N student records, indexed by name. Each node contains a linked list of L classes students took at UCLA.
  - Big O to determine if a student has taken a class: O(logN + L)
    - logN to find student in BST, L to find class in linked list
- Hash tables: MOST EFFICIENT WAY TO SEARCH FOR DATA
- The modulus operator (%):
  - Divide two numbers and obtain remainder
