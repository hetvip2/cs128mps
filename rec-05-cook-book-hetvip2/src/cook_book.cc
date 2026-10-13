#include "cook_book.hpp"

#include <fstream>

std::vector<Recipe> CookBook::MealPrep(const std::string& ingredient,
                                       double amount,
                                       unsigned int num_meals) {
  std::vector<Recipe> selected_recipes;

  for (const auto& [key, value] : recipes_) {
    const Recipe& recipe = value;

    if (recipe.IncludesIngredient(ingredient)) {
      double recipe_amount = recipe.GetIngredientAmount(ingredient);

      if (recipe_amount <= amount && selected_recipes.size() < num_meals) {
        selected_recipes.push_back(recipe);
        amount -= recipe_amount;
      }
    }
  }
  return selected_recipes;
}

void CookBook::AddRecipe(const Recipe& r_in) {
  recipes_[r_in.GetTitle()] = r_in;
}

Recipe CookBook::GetRecipe(const std::string& title) { return recipes_[title]; }
