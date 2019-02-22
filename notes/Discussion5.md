# Discussion 5
## Feb 22, 2019
---
## SORTING
- Ordering a bunch of items based on a comparison operator
- Vary in time/space complexity
- STABILITY: If two objects have equal keys (what they are compared based on), they appear in the same order in the sorted output as they do in the input
- Comparison based sorting algorithms cannot do better than nlogn
---
### Selection Sort
- Select smallest item from the array, swap it with the first position
- Find the next smallest step, swap with 2nd
- And so on
- Time complexity O(n^2)
  -  n + (n-1) + (n-2) + (n-3) + ... = (1/2)(n)(n+1)
- Space complexity O(1)
  - Swapping within the array, does not need extra space
- UNSTABLE:

  INPUT ---- 2(a), 2(b), 5, 1

  OUTPUT ---- 1, 2(b), 2(a), 5
- Also works with Linked Lists
- Same number of comparisons regardless of input

```c++
//For an array of ints
void SelectionSort(int x[], int n){
    if (n == 1){ return; } //base
    int minIndex = 0;
    for (int i=0; i < n; i++){
        if(x[i] < x[minIndex]){
            minIndex = i;
        }
    }
    int temp = x[0];
    x[0] = x[minIndex];
    x[minIndex] = temp;
    SelectionSort(x+1, n-1);
}

struct Node{
  int val;
  Node* next;
};

//For a linked list

Node* SelectionSort(Node* head){ //return Node* to new head
  Node * min = head;
  Node * t = head;

  while(t != nullptr){
    if(t->val < min->val){ min = t; }
    t = t->next;
  }

  t = head;
  while (t->next != min){t = t->next; }

  t->next = head;
  Node* temp = head->next;
  t->next->next=min->next;
  min->next = temp;

  SelectionSort(min->next);
  return min;
}
```

### Insertion Sort
- Start from the second items
  - If it is greater/equal than the first, leave it as is
  - If it is less than the first, move it to the front
- Look at third and put it in the right place
- And so on
- Time complexity: O(n^2)
  - Worst case:
    INPUT in descending order  
      - Need to do 1+2+3+...+n = (1/2)(n)(n+1)
  - Best case:
    Already sorted, Order of n
  - Number of operations depend on input
- Space complexity: O(1)
- Stable: we only place element before another if element we are checking is STRICTLY less than the element that will follow it

### Bubble Sort
- Each step pushes the largest value to the end
- Keep traversing array until you do no swaps
- Worst case: Comparison is made every single time in arithmetic sum fashion
- Time complexity: O(n^2)
- Space complexity: O(1)
- STABLE: If two numbers are identical, they are not swapped
---
## DIVIDE AND CONQUER
### Merge Sort
- Merge operation: take two sorted array, produce one combined sorted array
  - Compare incrementally until you finish one array, then copy the rest of the other
- Base case: split arrays over and over until a bunch of arrays of one element (already sorted)
- Time complexity: O(nlogn)
  - n elements to sort, split in half for every step
  - Split in half log n times
  - Worst case must compare n elements compared when merging
  - log n (splitting) * n (merge)
- Space complexity: O(n)
- STABLE
- Can parallelize on a multi-core processor

### Quick Sort
- Pick a pivot (some element of the array)
  - Go over all elements of the array:
      - If element is smaller than pivot: place to L
      - If it is larger: place to R
- Then recursively pick a pivot on each half of the array (around original pivot)
- Time complexity: O(n^2)
  - Worst case: selecting largest or smallest element as pivot everytime
  - Best case (if we take random pivot): nlogn
- Space complexity: O(n)
- NOT stable (similar to why selection sort is not stable)
- Can be parallelized
