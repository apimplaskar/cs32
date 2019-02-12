//
//  main.cpp
//  hw3-linear
//
//  Created by Aditya Pimplaskar on 2/5/19.
//  Copyright © 2019 Aditya Pimplaskar. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
#include <cassert>

using namespace std;

bool somePredicate(double x){
    return x < 0;
}

// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
    if (n<1) { return false; } //trivial case
    
    //array traversal by recursion
    if (somePredicate(a[0]) == true) { return true; }
    return anyTrue(a+1, n-1);
}


// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if(n<1){ return 0;} //don't want empty array/negative number of elements
    if( somePredicate(a[0]) ){ return countTrue(a+1, n-1)+1; } //if we find it, increment
    else{ return countTrue(a+1,n-1); } //if not return the subsolution
}


// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.

int firstTrue(const double a[], int n)
{
    //similar idea to previous problem
    if(somePredicate(a[0])){ return 0; }//base: if we have one element and we find it, return
    else if (n < 1 || firstTrue(a+1, n-1) == -1){ return -1; } //base: less than one element, and elements down the line not true
    else{ return firstTrue(a+1,n-1)+1; }//if element down the line WAS true
    
}




// Return the subscript of the smallest element in the array (i.e.,
// return the smallest subscript m such that a[m] <= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMin(const double a[], int n)
{
    if(n<1){ return -1; } //base: avoid array of size <= 0
    if(n==1){ return 0; }
    // here that will break recursion before we reach size = 0
    //"magic function" finds minimum position in a+1, n-1
    //if the value there is < a[0], we return
    //if the value is > a[0], return 0
    int loc = positionOfMin(a+1, n-1);
    if (a[loc+1] < a[0]){ return loc+1; }
    else{ return 0; }
    
    
}


// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    // Sanity checks/base cases
    if(n2 == 0){ return true; }
    if(n1 < n2 || n1 < 1){ return false; }
    
    //if a1's first element is a2's first element, we can move on to the next element of a2
        //recursively call moving forward one step in BOTH arrays
    //if not
        //recursively call moving forward one step in a1 NOT in a2
    
    if(a1[0] == a2[0]){ //can step forward in a2
        return includes(a1+1, n1-1, a2+1, n2-1);
    }
    else{ //cannot step forward in a2
        return includes(a1+1, n1-1, a2, n2);
    }
}


int main(){
    double arr[4] = {1,2,3,5};
    double arr2[5] = {1,2,3,-4,5};
    double arr3[6] = {-1,9,3,4,-299,7};
    double arr4[0] ={};
    
    cout << includes(arr2, 5, arr, 4);
    cout << includes(arr, 4, arr2, 5);
    cout << includes(arr2, 5, arr4, 0);
    
    /*
    assert(!anyTrue(arr, 4));
    assert(anyTrue(arr2,5));
    assert(countTrue(arr, 4) == 0);
    assert(countTrue(arr2,5)==1);
    assert(firstTrue(arr,4) == -1);
    cout << firstTrue(arr2,5);
    //assert(firstTrue(arr2, 5) == 3);
    cout << "All tests passed";
     */
}
