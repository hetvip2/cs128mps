CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4

exec: bin/exec
tests: bin/tests

bin/exec: ./src/howdy_world.cc ./includes/utilities.hpp ./src/utilities.cc
	$(CXX) $(CXX_FLAGS) ./src/howdy_world.cc ./src/utilities.cc -o $@

bin/tests: ./tests/tests.cc ./includes/utilities.hpp ./src/utilities.cc
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/utilities.cc  -o $@

.DEFAULT_GOAL := exec
.PHONY: exec tests clean

clean:
	rm -rf bin/*
