CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always

exec: bin/exec
tests: bin/tests

bin/exec: ./src/driver.cc ./src/Sport.cc ./includes/Sport.hpp 
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/Sport.cc -o $@

bin/tests: ./tests/tests.cc ./src/Sport.cc ./includes/Sport.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests.cc ./src/Sport.cc -o $@


.DEFAULT_GOAL := exec
.PHONY: exec tests

clean:
	rm -rf bin/*
