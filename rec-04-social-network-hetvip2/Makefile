CXX=clang++
CXX_FLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -O0 -gdwarf-4 -fsanitize=address,undefined,implicit-conversion,local-bounds -fno-omit-frame-pointer -fno-optimize-sibling-calls -fsanitize-address-use-after-return=always

exec: bin/exec
tests_pt1: bin/tests_pt1
tests_pt2: bin/tests_pt2


bin/exec: ./src/driver.cc ./src/social_network.cc ./includes/social_network.hpp
	$(CXX) $(CXX_FLAGS) ./src/driver.cc ./src/social_network.cc -o $@

bin/tests_pt1: ./tests/tests_part_1.cc ./src/social_network.cc ./includes/social_network.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests_part_1.cc ./src/social_network.cc -o $@

bin/tests_pt2: ./tests/tests_part_2.cc ./src/social_network.cc ./includes/social_network.hpp
	$(CXX) $(CXX_FLAGS) ./tests/tests_part_2.cc ./src/social_network.cc -o $@


.DEFAULT_GOAL := exec
.PHONY: exec tests_pt1 tests_pt2 clean

clean:
	rm -rf bin/*
