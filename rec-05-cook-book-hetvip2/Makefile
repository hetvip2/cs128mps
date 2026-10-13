CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/cook_book.cc ./src/recipe.cc ./src/functions.cc ./includes/recipe.hpp ./includes/cook_book.hpp ./includes/functions.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/cook_book.cc ./src/recipe.cc ./src/functions.cc -o $@

bin/tests: ./tests/tests.cc ./src/cook_book.cc ./src/recipe.cc ./src/functions.cc ./includes/recipe.hpp ./includes/cook_book.hpp ./includes/functions.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/cook_book.cc ./src/recipe.cc ./src/functions.cc -o $@


.DEFAULT_GOAL := exec
.PHONY: exec tests

clean:
	rm -rf bin/*
