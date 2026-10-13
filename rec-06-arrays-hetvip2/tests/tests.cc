// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jule Schatz                    Environment : ubuntu:bionic               //
//  Date ......: 2023/12/29                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "functions.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

// Two vectors are equal if they have the same recipes, order does not matter.
bool ArrayCompareUnordered(int arr1[],
                           unsigned int size1,
                           int arr2[],
                           unsigned int size2) {
  if (size1 != size2) return false;
  for (unsigned int i = 0; i < size1; i++) {
    bool found = false;
    for (unsigned int j = 0; j < size2; j++) {
      if (arr1[i] == arr2[j]) found = true;
    }
    if (!found) return false;
  }
  return true;
}

bool ArrayCompareOrdered(int arr1[],
                         unsigned int size1,
                         int arr2[],
                         unsigned int size2) {
  if (size1 != size2) return false;
  for (unsigned int i = 0; i < size1; i++) {
    if (arr1[i] != arr2[i]) return false;
  }
  return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Max Element", "[MaxElement]") {
  int arr1[3] = {2, 3, 4};
  int arr2[3] = {-1, -2, -3};

  REQUIRE(MaxElement(arr1, 3) == 4);
  REQUIRE(MaxElement(arr2, 3) == -1);
}

TEST_CASE("Sum Finder", "[SumFinder]") {
  int arr1[5] = {1, 2, 3, 4, 5};
  int arr2[5] = {-1, -2, -3, 1, 2};

  REQUIRE(SumFinder(arr1, 5, 5) == true);
  REQUIRE(SumFinder(arr1, 5, 6) == false);
  REQUIRE(SumFinder(arr2, 5, 4) == false);
}

TEST_CASE("Reverse Array", "[ReverseArray]") {
  int arr1[3] = {2, 3, 4};
  int arr1_rev[3] = {4, 3, 2};
  ReverseArray(arr1, 3);
  REQUIRE(ArrayCompareOrdered(arr1, 3, arr1_rev, 3));

  int arr2[4] = {2, 3, 4, 5};
  int arr2_rev[4] = {5, 4, 3, 2};
  ReverseArray(arr2, 4);
  REQUIRE(ArrayCompareOrdered(arr2, 4, arr2_rev, 4));
}

TEST_CASE("Merge Arrays", "[MergeArrays]") {
  int arr1[3] = {2, 4, 6};
  int arr2[3] = {1, 4, 5};
  int arr_pre_merged[6];
  int arr_merged[6] = {1, 2, 4, 4, 5, 6};
  MergeArrays(arr1, 3, arr2, 3, arr_pre_merged);
  REQUIRE(ArrayCompareOrdered(arr_pre_merged, 6, arr_merged, 6));

  int arr1_2[1] = {3};
  int arr2_2[3] = {1, 4, 5};
  int arr_pre_merged_2[4];
  int arr_merged_2[4] = {1, 3, 4, 5};
  MergeArrays(arr1_2, 1, arr2_2, 3, arr_pre_merged_2);
  REQUIRE(ArrayCompareOrdered(arr_pre_merged_2, 4, arr_merged_2, 4));

  int arr1_3[3] = {3, 6, 10};
  int arr2_3[2] = {1, 5};
  int arr_pre_merged_3[5];
  int arr_merged_3[5] = {1, 3, 5, 6, 10};
  MergeArrays(arr1_3, 3, arr2_3, 2, arr_pre_merged_3);
  REQUIRE(ArrayCompareOrdered(arr_pre_merged_3, 5, arr_merged_3, 5));
}

TEST_CASE("Remove Duplicates", "[RemoveDuplicates]") {
  int arr1[4] = {2, 4, 4, 6};
  int arr1_removed[3] = {2, 4, 6};
  int size1 = 4;
  RemoveDuplicates(arr1, size1);
  REQUIRE(ArrayCompareUnordered(arr1, size1, arr1_removed, 3));

  int arr2[4] = {2, 4, 1, 6};
  int arr2_removed[4] = {2, 4, 1, 6};
  int size2 = 4;
  RemoveDuplicates(arr2, size2);
  REQUIRE(ArrayCompareUnordered(arr2, size2, arr2_removed, 4));

  int arr3[3] = {2, 2, 2};
  int arr3_removed[1] = {2};
  int size3 = 3;
  RemoveDuplicates(arr3, size3);
  REQUIRE(ArrayCompareUnordered(arr3, size3, arr3_removed, 1));

  int arr4[4] = {2, 1, 4, 2};
  int arr4_removed[3] = {2, 1, 4};
  int size4 = 4;
  RemoveDuplicates(arr4, size4);
  REQUIRE(ArrayCompareUnordered(arr4, size4, arr4_removed, 3));
}

TEST_CASE("Rotate Array", "[RotateArray]") {
  int arr1[3] = {2, 4, 6};
  int arr1_rot[3] = {6, 2, 4};
  RotateArray(arr1, 3, 1);
  REQUIRE(ArrayCompareOrdered(arr1, 3, arr1_rot, 3));

  int arr2[3] = {2, 4, 6};
  int arr2_rot[3] = {4, 6, 2};
  RotateArray(arr2, 3, 2);
  REQUIRE(ArrayCompareOrdered(arr2, 3, arr2_rot, 3));

  int arr3[3] = {2, 4, 6};
  int arr3_rot[3] = {2, 4, 6};
  RotateArray(arr3, 3, 3);
  REQUIRE(ArrayCompareOrdered(arr3, 3, arr3_rot, 3));

  int arr4[1] = {2};
  int arr4_rot[1] = {2};
  RotateArray(arr4, 1, 234);
  REQUIRE(ArrayCompareOrdered(arr4, 1, arr4_rot, 1));
}

TEST_CASE("Rotate Array In Place", "[RotateArrayInPlace]") {
  int arr1[3] = {2, 4, 6};
  int arr1_rot[3] = {6, 2, 4};
  RotateArrayInPlace(arr1, 3, 1);
  REQUIRE(ArrayCompareOrdered(arr1, 3, arr1_rot, 3));

  int arr2[3] = {2, 4, 6};
  int arr2_rot[3] = {4, 6, 2};
  RotateArrayInPlace(arr2, 3, 2);
  REQUIRE(ArrayCompareOrdered(arr2, 3, arr2_rot, 3));

  int arr3[3] = {2, 4, 6};
  int arr3_rot[3] = {2, 4, 6};
  RotateArrayInPlace(arr3, 3, 3);
  REQUIRE(ArrayCompareOrdered(arr3, 3, arr3_rot, 3));

  int arr4[1] = {2};
  int arr4_rot[1] = {2};
  RotateArrayInPlace(arr4, 1, 234);
  REQUIRE(ArrayCompareOrdered(arr4, 1, arr4_rot, 1));
}

/////////////////////////////////////////////////////////////////////////////////////////////