#include "recipe.hpp"

#include <fstream>

Recipe::Recipe() {}

Recipe::Recipe(const std::vector<std::string>& steps_in,
               const std::map<std::string, double>& ingredients_in,
               const std::string& title_in):
    steps_(steps_in), ingredients_(ingredients_in), title_(title_in) {}

std::string Recipe::GetTitle() const { return title_; }

bool Recipe::IncludesIngredient(const std::string& ingredient) const {
  return ingredients_.contains(ingredient);
}

double Recipe::GetIngredientAmount(const std::string& ingredient) const {
  return ingredients_.at(ingredient);
}

std::string Recipe::GetNextStep() {
  current_step_index_++;
  return steps_[current_step_index_ - 1];
}