# Discussion 6
## March 1, 2019
---
### Trees
- Nodes can have 2+ children (BINARY TREE HAS <= 2 Nodes)
- Root represented by a tree node pointer
- Operations: search, delete, insert, etc.
- TreeNodes are randomly organized in memory
- Traversals:
  - Pre/in/post order
---
### Implement Level Order Tree Traversal
- Breadth first search. Will process all elements of a given depth before going to the next level.
- Can use a queue to implement
- Cannot be recursive. (Recursion is inherently stack-based)

```c++
void printLevelOrder(Node* root){ //NOT RECURSIVE
  queue<Node*> nodes;
  nodes.push(root);
  while(!nodes.empty()){
    if(nodes.front == nullptr){ return; }
    cout << nodes.front->val;
    if(nodes.front->left != nullptr)
      {nodes.push(nodes.front->left);}
    if(nodes.front->right != nullptr)
      {nodes.push(nodes.front->right);}
    nodes.pop();
  }
}
```
---
### Write a function that determines the maximum depth of a binary tree
```c++
struct TreeNode{
  int val;
  TreeNode* left, right;
};

int maxDepth(TreeNode* root){
  if (root == nullptr){ return 0; }
  if(root->left == nullptr && root->right == nullptr )
    { return 1; }

  depthL = maxDepth(root->left);
  depthR = maxDepth(root->right);

  return 1+max(depthL, depthR);
}
```
---
### Binary Search Trees
- Entire subtree to left < the value of the node AND entire subtree to the right > the value of the node
  - By extension (without keeping track of a count in each node), we can't have duplicates (UNIQUE NODES)
- Makes searching easier
  - in balanced case, don't need to scan N items, rather need to go down log(N) times
  - in unbalanced case, O(N)
- For insertion:
  - If balanced, O(log(N)). If not, O(N).
  - Algorithm:
    - Basically a search. When you find a nullptr where you need to insert, we initialize a new node.
- For deletion: CHECK SLIDES
---
### Get the max value of a BST
- This is the right most node (i.e. right child is null)

```c++
int maxBST(TreeNode* root){ //makes use of our maxDepth fn
  if (root == nullptr){ return -1; }
  TreeNode* cur = root;
  for(int i = 0; i < maxDepth(root); i++){
    cur = cur->right;
  }
  return cur->val;
}

int maxBST(TreeNode* root){ //without maxDepth fn
  if (root == nullptr){ return -1; }
  TreeNode* cur = root;
  while (cur->right != nullptr){
    cur = cur->right;
  }
  return cur -> val;
}

int maxBST(TreeNode* root){ //recursive
  if(root == nullptr){ return -1; }
  if(root->right == nullptr){ return root->val; }
  return maxBST(root->right);
}
```
---
### Check if the binary tree is valid
- If the binary tree is not valid, return false
- In order traversals should ALWAYS be sorted

```c++
bool FAILisValidBST(Node* root){
  if (root == nullptr){ return true; }
  if(root -> left != nullptr){
    if((root ->left -> val)>(root ->val)){ return false; }
  }
  if(root->right != nullptr){
    if((root->right->val) < (root->val)){ return false; }
  }
  return (isValidBST(root->left) && isValidBST(root->right));
}
//THIS WILL FAIL

void inOrderTrav(Node* root, vector<int>& v){
  if (root == nullptr){ return; }
  inOrderTrav(root->left, v);
  v.push_back(root->val);
  inOrderTrav(root->right, v);
}

bool isValidBST(Node* root){
  vector<int> check;
  inOrderTrav(root, check);
  for(int i = 0; i < check.size()-1; i++){
    if(check[i] > check[i+1]){ return false; }
  }
  return true;
}

/*
Every node on the left fall in [-infinity, node->val)
Every node on right fall in (node->val, infinity]
Check the range for every value (must update range as you go)
*/

bool isValidBST(Node* root){ //RECURSIVE
  if (root == nullptr){ return true; }
  // must include <climits>
  int min = INT_MIN;
  int max = INT_MAX;
  return (validBSThelper(root, min, max);
}

bool validBSThelper(Node* cur, int min, int max){
  if(cur == nullptr){ return true; }
  if(min > root->val || max < root->val){ return false; }
  return (validBSThelper(cur->left, min, cur->val)
    && validBSThelper(cur->right, cur->val, max));  
}
```
---
### Checking if a tree is balanced or not
- Balanced := number of levels <= log2(N)
- If maxDepth (from our old function) exceeds log2(N), then it is not balanced (must lean one way or another)
---
