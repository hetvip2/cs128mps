#include "functions.hpp"

#include "catch.hpp"

// Write a function that returns the max element in
// an array of doubles.
int MaxElement(int arr[], unsigned int size) {
  int max_el = 0;
  for (unsigned int i = 0; i < size; i++) {
    if (max_el < arr[i]) max_el = arr[i];
  }
  return max_el;
}

// Write a function that returns true if any set of consecutive
// 2 elements in the array sum together to the value k
// Time: 10 - 15 minutes
bool SumFinder(int arr[], unsigned int size, int k) {
  for (unsigned int i = 0; i < size - 1; i++) {
    if (arr[i] + arr[i + 1] == k) {
      return true;
    }
  }
  return false;
}

// Write a function that reverses an array
// Time: 10 - 15 minutes
void ReverseArray(int arr[], unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
  }
}

//-------------- Challenge Problems Below --------------------

// Write a function that takes in two sorted arrays, arr1 and arr2,
// and merges them into a third sorted arr3. Note arr3 is the size of arr1 +
// arr2
// Time: 30 - 40 minutes
void MergeArrays(int arr1[],
                 unsigned int size1,
                 int arr2[],
                 unsigned int size2,
                 int arr3[]) {
  int i = 0, j = 0, k = 0;
  // Merge arr1 and arr2 into arr3
  while (i < size1 && j < size2) {
    if (arr1[i] <= arr2[j]) {
      arr3[k++] = arr1[i++];
    }

    else {
      arr3[k++] = arr2[j++];
    }
  }
  // Copy remaining elements of arr1 if any
  while (i < size1) {
    arr3[k++] = arr1[i++];
  }
  // Copy remaining elements of arr2 if any
  while (j < size2) {
    arr3[k++] = arr2[j++];
  }
}

// Write a function that removes duplicate elements from an
// array. Make sure the passed in size also gets updated based
// on many elements you had to remove.
// Suggested Time: 30 - 40 minutes
void RemoveDuplicates(int arr[], int& size) {}

// Write a function that rotates an array to the right num_rotations
// number of times.
// Suggested Time: 30 - 40 minutes
void RotateArray(int arr[], unsigned int size, unsigned int num_rotations) {}

// Write a function that rotates an array to the right num_rotations
// but this time you may not use another data structure, like an array,
// vector, or map.
// Suggested Time: 30 - 40 minutes
void RotateArrayInPlace(int arr[],
                        unsigned int size,
                        unsigned int num_rotations) {
  if (size == 0 || num_rotations == 0) return;

  num_rotations %= size;  // Calculate the actual number of rotations

  for (unsigned int r = 0; r < num_rotations; ++r) {
    int last = arr[size - 1];
    for (int i = size - 1; i > 0; --i) {
      arr[i] = arr[i - 1];
    }
    arr[0] = last;
  }
}