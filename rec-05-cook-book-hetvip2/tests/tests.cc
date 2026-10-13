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
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "cook_book.hpp"
#include "recipe.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

// Two vectors are equal if they have the same recipes, order does not matter.
bool VectorCompare(const std::vector<Recipe>& vec1,
                   const std::vector<Recipe>& vec2) {
  if (vec1.size() != vec2.size()) return false;

  for (unsigned int i = 0; i < vec1.size(); i++) {
    bool found = false;
    for (unsigned int j = 0; j < vec2.size(); j++) {
      if (vec1.at(i).GetTitle() == vec2.at(j).GetTitle()) found = true;
    }
    if (found == false) return false;
  }
  return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("MealPrep Basic Test", "[MealPrep-Basic]") {
  CookBook c1;

  std::vector<std::string> steps_r1 = {"Doesn't matter for this test"};
  std::map<std::string, double> ingredients_r1 = {{"eggs", 200.0},
                                                  {"spinach", 100}};
  std::string title_r1 = "Recipe 1";
  Recipe r1(steps_r1, ingredients_r1, title_r1);
  c1.AddRecipe(r1);

  std::vector<std::string> steps_r2 = {"Doesn't matter for this test"};
  std::map<std::string, double> ingredients_r2 = {{"flour", 500.0},
                                                  {"eggs", 100}};
  std::string title_r2 = "Recipe 2";
  Recipe r2(steps_r2, ingredients_r2, title_r2);
  c1.AddRecipe(r2);

  std::vector<Recipe> actual = c1.MealPrep("eggs", 300, 2);
  std::vector<Recipe> expected = {r1, r2};

  REQUIRE(VectorCompare(expected, actual));
}


/////////////////////////////////////////////////////////////////////////////////////////////