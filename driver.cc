#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "illini_book.hpp"

int main() {
  std::string ppl = "example/persons.csv";
  std::string rel = "example/relations.csv";

  auto* book = new IlliniBook(ppl, rel);

  size_t b = book->CountGroups();
  size_t c = book->CountGroups("128");
  size_t d = book->CountGroups(std::vector<std::string>{ "128", "173" });
  size_t e = book->CountGroups(std::vector<std::string>{ "128", "124", "173" });
  
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;
  std::cout << e << std::endl;
}

// errors
