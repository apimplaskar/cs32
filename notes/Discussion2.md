# Discussion 2
## Feb 1, 2019
---
### STACKS
- Push to the top, pop from the top
  - Last in, first out (LIFO)
- Push (add to top), pop (remove top), top (see top element), size, empty (empty or not?)
- Items can be of any type
- Can implement as an array or linked list
  - Array needs index to keep track of linked list
  - Use head pointer in LL and add/pop from front
- Can also use STL library
  - #include < stack >
  - std::stack < type > nameStack;


INFIX v. POST FIX

ex. (2+2) vs (2 2 +)

Post-fix gets rid of ambiguity in order of operations

---
### QUEUES
- Enqueue to back, dequeue from front
  -  First in, first out (FIFO)
- Can use array or linked list
  - Circular queue: have a start and end index, and a size variable
    - Insert: add to end, increment end ptr, add size
    - Pop: pop from head, increment start ptr, decrement size
    - SIZE to distinguish empty vs completely full array
- Can also use STL library
