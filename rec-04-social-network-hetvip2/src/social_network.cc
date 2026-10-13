#include "social_network.hpp"

// Define your SocialNetwork member functions below
void AddFriends(const std::string& p1, const std::string& p2) {
  if (networkMap.contains(p1)) {
    networkMap.at(p1).push_back(p2);
  } else {
    std::vector<std::string> v;
    networkMap.insert({p1, v});
  }
  if (networkMap.contains(p2)) {
    networkMap.at(p2).push_back(p1);
  } else {
    std::vector<std::string> v;
    networkMap.insert({p2, v});
  }
}

// This function returns true if p1 is friends with p2
bool AreFriends(const std::string& p1, const std::string& p2) {
  if (networkMap.contains(p1)) {
    for (unsigned int i = 0; i < networkMap.at(p1).length(); ++i) {
      if (networkMap.at(p1)[i].equals(p2)) {
        return true;
      }
    }
  }
  if (networkMap.contains(p2)) {
    for (unsigned int i = 0; i < networkMap.at(p2).length(); ++i) {
      if (networkMap.at(p2)[i].equals(p1)) {
        return true;
      }
    }
  }
  return false;
}
std::vector<std::string> SuggestFriends(const std::string& p1);
// This function returns a vector of suggested friends for p1.
// Someone is a suggested friend for p1 if they are:
//   1. Not p1
//   2. Not already friends with p1
//   3. Have at least 1 mutual friend with p1
// Additionally, this returned vector must be sorted in terms of most mutual
// friends being in position 0 in the vector and the least number of mutual
// friends being in the last position in the vector. Ties can be handled
// arbitrarily.