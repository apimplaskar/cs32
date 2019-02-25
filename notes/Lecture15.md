# Lecture 15
## Feb 25, 2019
---
### Selection Sort
- Start with first element, scan rest of the element and swap the smallest element with the first
- Look at the remaining n-1 books, and swap the smallest book with the second
- And so on
- EX. 3 2 5 1 --> 1 2 5 3 --> 1 2 5 3 --> 1 2 3 5
- This is O(n^2), so it is not efficient
  - n + (n-1) + (n-2) + (n-3) + ... = n(n+1)(1/2) = O(n^2)
- No input data that can make this more or less efficient
  - Still have to scan ALL books
- UNSTABLE
---
- Most efficient sorting you could ever have is O(n) because you have to check all n items (for comparison). For GENERAL PURPOSE sorts, the most efficient sort is O(nlogn).

- Stable sort: if you have two values with the same key, if these values' ordered is maintained from the input to the output, it is stable.
---
### Insertion Sort
- Scan to the last element, remove it, insert in proper slot after shift all other elements that follow
- O(n^2)
  - Worst case if array is completely wrong order
- More efficient if everything is already sorted
  - NO SHIFTING
- STABLE: Every time we add an item we will push it to the  slot where it is strictly less than its next element
---
### Bubble Sort
- Start with the front element, if its key is greater than some other element in the array, bubble that element to the end
- Keep traversing the array until you have NO swaps
- O(n^2)
  - Worst case: totally out of order
  - Best case: completely sorted O(n)
- STABLE: identical numbers, not swapped
---
### Shell Sort
- H-sorting:
  - Pick a value of h
  - If A[i] and A[i+h] is out of order, swap the two
    - If h=1 this is bubble sort!
- "3-sorted" = "h-sorted with an h of 3"
- Shellsort will sort with decreasing h-values
  - 8 -> 4 -> 2 -> 1
  - With every h-sort, the process becomes simpler after each iteration
- No one knows the big O
- Almost as efficient as nlogn but space complexity is a LOT smaller.
---
### STL Challenge
Have a map<string, set<string>> mapping people to all streets they have lived on
- Finding ALL instances of a particular street:
  - O(PlogE)
  - P people * log(E) for binary search in set
- Finding if one particular person ever lived on a particular street:
  - O(log(E) + log (P))
  - log(P) to find person + log (E) to find string
- Print every name along with every street (both in alpha order)
  - O(PE)
- Print out every street that one individual has lived on
  - O(log(P) + E)
  - log(P) to find person, + E to print out all streets
---
## Divide and conquer (Recursive) sorts

### Quick Sort
- If array has 0 or 1 element, return
- Select an arbitrary element P from the array (maybe the first element)
- Division step: PARTITIONING
  - All elements <= P go to the left, all other elements (>P) go to the right of the array
  - Item P is now sorted
  - Order at this point does not matter
- Repeat this process on the left and right sub-arrays (ignore item P)
- Technically O(n^2) but averages to O(nlogn)
  - Partition is O(n)
  - Can divide log n times
  - WORST CASE:
    - Already sorted in ascending/descending ordered
    - Partition doesn't cut in half, rather it just steps it forward one (O(n^2))
    - Go n levels deep (take off one item at a time), and n steps to partition
- Difficult to use a singly linked list, can use doubly (so we can access previous items)
- Swapping items so NOT STABLE
- Uses a variable amount of RAM (depends on how many levels deep you go)
- Can PARALLELIZE on multiple cores

```c++
void QuickSort(int Array[], int First, int Last){
  if (Last-First >= 1){
    int pivotIndex;
    pivotIndex = Partition(Array, First, Last);
    QuickSort(Array, First, PivotIndex-1); //Last
    QuickSort(Array, PivotIndex+1, Last); //First
  }
}

void Partition(int a[], int low, int high){ //O(n)!
  int pi = low;
  int pivot = a[low];
  do{
    while(low <= high && a[low] <= pivot)
      //find first value that is > the pivot
      low++
    while( a[high] > pivot){
      //find first value that is <= pivot
      high--;
    if(low < high)
      //swap them
      swap(a[low], a[high]);
  }while(low < high);
  //low and high will converge at the center

  swap(a[pi], a[high])
  pi = high;
  return (pi);
}
```
