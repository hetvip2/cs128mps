CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -O0 -gdwarf-4 

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/functions.cc ./includes/functions.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/functions.cc -o $@

bin/tests: ./tests/tests.cc ./src/functions.cc ./includes/functions.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/functions.cc -o $@


.DEFAULT_GOAL := exec
.PHONY: exec tests

clean:
	rm -rf bin/*
