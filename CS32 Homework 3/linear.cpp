//
//  linear.cpp
//  cs32hw3
//
//  Created by Maeneka Grewal on 2/12/18.
//  Copyright © 2018 Maeneka Grewal. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (n == 0)
        return true;
    
    if (somePredicate(*a))
    {
         return allTrue(a+1, n-1);
    }
    else
        return false;
    
    return true;
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n == 0)
        return 0;
    
    if (!somePredicate(*a))
    {
        return 1 + countFalse(a+1, n-1);
    }
    else
        return 0 + countFalse(a+1, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.
int firstFalse(const double a[], int n)
{
    if (n == 0)
        return -1;
    
    if (!somePredicate(*a))
        return 0;
    
    int posRestList = firstFalse(a+1, n-1);
    
    if (posRestList == -1)
        return -1;
    else
        return posRestList + 1;
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    if (n == 0)
        return -1;
    if (n == 1)
        return 0;
    
    n -= 1;
    int index = indexOfMin(a, n);
    if (a[n] < a[index])
        return n;
    else
        return index;
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
    if (n2 == 0)
        return true;

    if (n1 == 0)
        return false;
    
    
    if (a1[0] != a2[0])
        return includes(a1+1, n1-1, a2, n2);
    else
        return includes(a1+1, n1-1, a2+1, n2-1);
}

/*int main()
{
    double arr[] = {5,2,9,8,9};
    double arr2[] = {9,5};
    int num = 4;
    
    cerr << indexOfMin(arr, num) << endl;
    cerr << firstFalse(arr, num) << endl;
    cerr << countFalse(arr, num) << endl;
    if (allTrue(arr, num))
        cerr << "all true!" << endl;
    else
        cerr << "falsito!" << endl;
    if (includes(arr, 5, arr2, 2))
        cerr << "yep includes" << endl;
    else
        cerr << "not includes" << endl;
}*/
