#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <map>
#include <vector>

// Write a function that returns the max element in
// an array of doubles.
int MaxElement(int arr[], unsigned int size);

// Write a function that returns true if any set of consecutive
// 2 elements in the array sum together to the value k
bool SumFinder(int arr[], unsigned int size, int k);

// Write a function that reverses an array
void ReverseArray(int arr[], unsigned int size);

//-------------- Challenge Problems Below --------------------

// Write a function that takes in two sorted arrays, arr1 and arr2,
// and merges them into a third sorted arr3. Note arr3 is the size of arr1 +
// arr2
void MergeArrays(
    int arr1[], unsigned int size1, int arr2[], unsigned int size2, int arr3[]);

// Write a function that removes duplicate elements from an
// array. Make sure the passed in size also gets updated based
// on many elements you had to remove.
void RemoveDuplicates(int arr[], int& size);

// Write a function that rotates an array to the right num_rotations
// number of times.
void RotateArray(int arr[], unsigned int size, unsigned int num_rotations);

// Write a function that rotates an array to the right num_rotations
// but this time you may not use another data structure, like an array,
// vector, or map.
void RotateArrayInPlace(int arr[],
                        unsigned int size,
                        unsigned int num_rotations);
#endif
