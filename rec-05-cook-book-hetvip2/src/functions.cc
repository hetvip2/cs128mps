#include "functions.hpp"

void AddStartingRecipes(CookBook& c1) {
  // Recipe 1: Pancakes
  std::vector<std::string> pancake_steps = {
      "Step 1: Mix flour, sugar, and baking powder in a bowl",
      "Step 2: Add milk and eggs, whisk until smooth",
      "Step 3: Heat a frying pan and pour batter onto it",
      "Step 4: Cook until bubbles form, then flip and cook until golden brown"};
  std::map<std::string, double> pancake_ingredients = {
      {"Flour", 200.0},
      {"Sugar", 50.0},
      {"Baking Powder", 5.0},  // Assuming baking powder is in grams
      {"Milk", 250.0},
      {"Eggs", 100.0}};  // Assuming each egg is around 50 grams
  std::string pancake_title = "Pancakes";

  Recipe pancakes_recipe(pancake_steps, pancake_ingredients, pancake_title);
  c1.AddRecipe(pancakes_recipe);

  // Recipe 2: Caesar Salad
  std::vector<std::string> caesar_salad_steps = {
      "Step 1: Wash and chop lettuce",
      "Step 2: Make croutons by toasting bread cubes",
      "Step 3: Mix chopped lettuce with croutons and Caesar dressing",
      "Step 4: Add grated parmesan cheese and toss well"};
  std::map<std::string, double> caesar_salad_ingredients = {
      {"Lettuce", 150.0},
      {"Bread", 100.0},
      {"Parmesan Cheese", 50.0},
      {"Caesar Dressing", 50.0}};
  std::string caesar_salad_title = "Caesar_Salad";

  Recipe caesar_salad_recipe(
      caesar_salad_steps, caesar_salad_ingredients, caesar_salad_title);
  c1.AddRecipe(caesar_salad_recipe);

  // Recipe 3: Spaghetti Carbonara
  std::vector<std::string> carbonara_steps = {
      "Step 1: Cook spaghetti according to package instructions",
      "Step 2: Fry pancetta until crispy",
      "Step 3: Whisk eggs, parmesan cheese, and black pepper in a bowl",
      "Step 4: Drain spaghetti and toss with pancetta and egg mixture"};
  std::map<std::string, double> carbonara_ingredients = {
      {"Spaghetti", 200.0},
      {"Pancetta", 100.0},
      {"Eggs", 100.0},
      {"Parmesan Cheese", 50.0},
      {"Black Pepper", 2.0}};
  std::string carbonara_title = "Spaghetti_Carbonara";

  Recipe carbonara_recipe(
      carbonara_steps, carbonara_ingredients, carbonara_title);
  c1.AddRecipe(carbonara_recipe);

  // Recipe 4: Chicken Stir-Fry
  std::vector<std::string> stir_fry_steps = {
      "Step 1: Marinate chicken strips in soy sauce and ginger",
      "Step 2: Heat oil in a wok and stir-fry chicken until cooked",
      "Step 3: Add sliced vegetables and stir-fry until tender",
      "Step 4: Season with salt, pepper, and additional soy sauce if needed"};
  std::map<std::string, double> stir_fry_ingredients = {
      {"Chicken Breast", 300.0},
      {"Soy Sauce", 50.0},
      {"Ginger", 10.0},
      {"Vegetables", 200.0}};
  std::string stir_fry_title = "Chicken_Stir-Fry";

  Recipe stir_fry_recipe(stir_fry_steps, stir_fry_ingredients, stir_fry_title);

  c1.AddRecipe(stir_fry_recipe);

  // Recipe 5: Vegetable Soup
  std::vector<std::string> soup_steps = {
      "Step 1: Chop assorted vegetables (carrots, celery, onions, potatoes)",
      "Step 2: Saute vegetables in a pot until softened",
      "Step 3: Add broth and simmer until vegetables are tender",
      "Step 4: Season with salt, pepper, and herbs to taste"};
  std::map<std::string, double> soup_ingredients = {{"Carrots", 200.0},
                                                    {"Celery", 100.0},
                                                    {"Onions", 100.0},
                                                    {"Potatoes", 150.0},
                                                    {"Broth", 500.0}};
  std::string soup_title = "Vegetable_Soup";

  Recipe soup_recipe(soup_steps, soup_ingredients, soup_title);

  c1.AddRecipe(soup_recipe);
}