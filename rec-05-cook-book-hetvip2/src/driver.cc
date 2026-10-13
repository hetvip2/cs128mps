#include <iostream>

#include "cook_book.hpp"
#include "functions.hpp"
#include "recipe.hpp"

int main() {
  CookBook cookbook;
  AddStartingRecipes(cookbook);

  std::string command;

  while (true) {
    std::cout << "Enter a recipe or exit: ";
    std::cin >> command;

    if (command == "exit") return 0;

    Recipe recipe = cookbook.GetRecipe(command);

    while (true) {
      std::cout << "Enter step or exit: ";
      std::cin >> command;
      if (command == "step") {
        std::cout << recipe.GetNextStep() << std::endl;
      } else if (command == "exit")
        return 0;
    }
  }
  return 0;
}