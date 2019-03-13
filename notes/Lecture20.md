# Lecture 20
## Mar 13, 2019
---
### HEAP SORT
- Naive:
  - Insert N numbers into maxheap, while there are numbers in the maxheap -> push biggest value from heap into last available slot of output array
- Better way:
  1. Rearrange input array into maxheap = O(n)
    - startNode = N/2 - 1
      - Don't need to worry about the leaf nodes (they are already, trivially heaps)
    - for(curNode = startNode thru rootNode){
      - Focus on subtree rooted at curNode
      - Think of this subtree as a maxheap
      - Keep shifting the top value down until your subtree becomes a valid maxheap
        - Comparing array[curNode] with array[2(curNode) + 1]
        - Then compare with array[2(curNode) + 2]
  2. While there are numbers left in the maxheap
    - Remove the biggest value --> Place it in the last slot of the array
      - Removing the value and swapping with the bottom right node opens up the last slot -- now we can add the largest value there (UTILIZES REHEAPIFICATION ALGO)
- Time complexity
  - Step 1) O(n) -- convert an array into a maxheap in N steps
  - Step 2) extracting an item takes logN steps, done for N items
  - N + N log N = O(N log N)
---
### Graphs
- ADT that stores entities and keeps track of relationships between them
- Holds 2 types of items:
  - Vertices (aka nodes), edges (aka arcs)
  - Edges connect two vertices to each other
    - Could also connect a vertex to itself
- Directed graphs: edges point in a particular direction
- Undirected graph: bi-directional
- Easiest way to represent a graph:
  - Size of both dimensions = # of Vertices
  - Each element indicates whether or not there is a DIRECTED connection between vertex i and j
    - To indicate an undirected graph, arr[i][j] = arr[j][i]
  - This is an ADJACENCY MATRIX
  - (ADJACENCY MATRIX)^n shows us which vertices are exactly n edges apart
- How else can we represent a graph?
  - A directed graph of N vertices can be represented by a an array of N linked lists: ** ADJACENCY LIST **
  - Each entry j in the linked list at arr[i], there is a connection from i to j
- Adjacency matrix v. adjacency list?
  - 10,000,000 users with ~ 100 friends each
    - USE ADJACENCY LIST (why allocate matrix with a bunch of empty cells)
  - 1000 cities with flights from every city to almost every other city
    - USE ADJACENCY MATRIX
- Graph Traversals:
  - Depth first (stack) or Breadth first (queue)
  - Depth first - go until it hits a dead end or a vertex that has already been visited
  - Breadth first - explores in growing concentric circles, explore all vertices 1 away from the start, then 2, then 3
  - A* finds most efficient path as early as possible using heuristic
- Same as maze-searching!
- Algorithm:

```
Depth first traversal (curVertex){

  If we have already visited the current vertex: return

  Otherwise

    Mark current vertex as visited

    Process the current current vertex
    For each edge leaving the current vertex
      Determine which vertex the edge takes us to
      Call DFT on that vertex
}

DFT w stack(start){
  Push start on to the stack
  WHile the stack is not empty
    Pop the top item and put it in variable c
      IF c has not been visited
        Mark c as visited
        For each edge from c, find the node it goes to
        If we haven't visited that node, push it to stack  
}
```

```
Breadth first (start){
  Add the start vertex to the queue
  Mark the start as discovered
  While queue is not empty
    Dequeue the top vertex, place it in variable c
    Process c
    For each vertex v directly reachable from c
      If v has not been discovered
        Mark it as discovered
          Insert vertex v into the queue
}
```

GRAPHS WITH WEIGHTED EDGES:
- Each edge between vertices has a weight or cost associated with it
- Shortest path = path with lowest weight
