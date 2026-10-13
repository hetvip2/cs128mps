#ifndef COOK_BOOK_HPP
#define COOK_BOOK_HPP

#include <iostream>
#include <map>
#include <vector>

#include "recipe.hpp"

class CookBook {
public:
  // This function helps a user select meals to cook given they have an
  // abundance of a particular ingredient. The user passes in the ingredient
  // name, the amount they have, and the max number of meals they would like to
  // make. The function returns the MAX number of recipes less than or equal to
  // num_meals that use up as much of the abundant ingredient as possible.
  std::vector<Recipe> MealPrep(const std::string& ingredient,
                               double amount,
                               unsigned int num_meals);

  // This functions adds the passed in recipe to the CookBook
  void AddRecipe(const Recipe& r_in);

  // This function returns a recipe based on its title
  Recipe GetRecipe(const std::string& title);

private:
  std::map<std::string, Recipe> recipes_;
};

#endif
