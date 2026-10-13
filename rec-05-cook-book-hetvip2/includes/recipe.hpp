#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <iostream>
#include <map>
#include <vector>

class Recipe {
public:
  // This is the constructor that initializes the member variables of a Recipe
  Recipe(const std::vector<std::string>& steps_in,
         const std::map<std::string, double>& ingredients_in,
         const std::string& title_in);

  // Defualt constructor
  Recipe();

  // This function returns the next step in the recipe starting at the first
  // step. Everytime this function is called it returns the following step.
  std::string GetNextStep();

  // This function returns true if the recipe includes the passed in ingredient
  bool IncludesIngredient(const std::string& ingredient) const;

  // This function returns the amount of the passed in ingredient that is needed
  // for this recipe
  double GetIngredientAmount(const std::string& ingredient) const;

  // This function returns the title of the recipe
  std::string GetTitle() const;

private:
  // Keeps track of the steps in the recipe, order does matter!
  std::vector<std::string> steps_;

  // Name and amount of ingredient (in grams)
  std::map<std::string, double> ingredients_;

  // Title of the recipe
  std::string title_;

  // The current step the user is on in the recipe
  int current_step_index_ = 0;
};

#endif
