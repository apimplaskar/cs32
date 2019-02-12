//
//  main.cpp
//  hw3-tree
//
//  Created by Aditya Pimplaskar on 2/7/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

// Return the number of ways that all n2 elements of a2 appear
// in the n1 element array a1 in the same order (though not
// necessarily consecutively).  The empty sequence appears in a
// sequence of length n1 in 1 way, even if n1 is 0.
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then for this value of a2     the function must return
//    10 20 40            1
//    10 40 30            2
//    20 10 40            0
//    50 40 30            3
int countIncludes(const double a1[], int n1, const double a2[], int n2)
{
    //base
    if(n1 == 1 && a1[0] == a2[0]) { return 1; } // Only one element in n1, matches first and only element in a2
    if(n1 < n2 || n1 < 1){ return 0; } // cannot have an n+1 element series appear in an n element array OR in an empty array
    if(n2 < 1) { return 1; } //looking for empty element, always true
    
    //Recursive:
    if(a1[0] == a2[0]){ //if we match the first element
        int rest = countIncludes(a1+1, n1-1, a2+1, n2-1); //we could repeat the first element OR could move on to the next
        return countIncludes(a1+1, n1-1, a2, n2) + rest; //add them
    }
    else{ return countIncludes(a1+1, n1-1, a2, n2);} // if not, move on to the next element of a1 to check
   
}



// Exchange two doubles
void exchange(double& x, double& y)
{
    double t = x;
    x = y;
    y = t;
}


// Rearrange the elements of the array so that all the elements
// whose value is > divider come before all the other elements,
// and all the elements whose value is < divider come after all
// the other elements.  Upon return, firstNotGreater is set to the
// index of the first element in the rearranged array that is
// <= divider, or n if there is no such element, and firstLess is
// set to the index of the first element that is < divider, or n
// if there is no such element.
// In other words, upon return from the function, the array is a
// permutation of its original value such that
//   * for 0 <= i < firstNotGreater, a[i] > divider
//   * for firstNotGreater <= i < firstLess, a[i] == divider
//   * for firstLess <= i < n, a[i] < divider
// All the elements > divider end up in no particular order.
// All the elements < divider end up in no particular order.
void divide(double a[], int n, double divider,
            int& firstNotGreater, int& firstLess)
{
    if (n < 0)
        n = 0;
    
    // It will always be the case that just before evaluating the loop
    // condition:
    //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
    //  Every element earlier than position firstNotGreater is > divider
    //  Every element from position firstNotGreater to firstUnknown-1 is
    //    == divider
    //  Every element from firstUnknown to firstLess-1 is not known yet
    //  Every element at position firstLess or later is < divider
    
    firstNotGreater = 0;
    firstLess = n;
    int firstUnknown = 0;
    while (firstUnknown < firstLess)
    {
        if (a[firstUnknown] < divider)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > divider)
            {
                exchange(a[firstNotGreater], a[firstUnknown]);
                firstNotGreater++;
            }
            firstUnknown++;
        }
    }
}


// Rearrange the elements of the array so that
// a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
// If n <= 1, do nothing.
void order(double a[], int n)
{
    
    int t_firstNotGreater;
    int t_firstLess;
    
    //Base
    if (n < 2) {
        return; } //empty array OR array with one element are already ordered
    
   
    
    //Recursive step
    //Order with some random partition in the middle of the array
    //Then recursively order both halves
    //So I don't have to scroll: divide(array, size, divider, firstNotGreater, firstLess)
    
    
    divide(a, n, a[n/2], t_firstNotGreater, t_firstLess);
    //Now t_firstNotGreater holds the index after where the divider is
    //Now t_firstLess holds the index of after the divider of an element != divider
    order(a, t_firstNotGreater);
    //Skip the pivot (and any repeats) to ensure that problem size shrinks
    order(a+t_firstLess, n-(t_firstLess));
    
    return;  // This is not always correct.

}
 

int main(){
    double arr[6] = {1,2,3,3, 4, 3};
    double arr2[3] = {1,2,3};
    double arr3[20] = {-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,1,2,3,4,5,6,7,8,9,10};
    
    int x,y;
    order(arr3, 20);
    for(int i = 0; i < 20; i++){ cout << arr3[i] << " " ;}
}
    
