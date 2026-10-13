#ifndef SOCIAL_NETWORK_HPP
#define SOCIAL_NETWORK_HPP

#include <iostream>
#include <map>
#include <vector>

class SocialNetwork {
public:
  // Adds a connection between two people. Assumes the connection
  // does not already exist. The connected is added in both directions
  void AddFriends(const std::string& p1, const std::string& p2);

  // This function returns true if p1 is friends with p2
  bool AreFriends(const std::string& p1, const std::string& p2);

  // This function returns a vector of suggested friends for p1.
  // Someone is a suggested friend for p1 if they are:
  //   1. Not p1
  //   2. Not already friends with p1
  //   3. Have at least 1 mutual friend with p1
  // Additionally, this returned vector must be sorted in terms of most mutual
  // friends being in position 0 in the vector and the least number of mutual
  // friends being in the last position in the vector. Ties can be handled
  // arbitrarily.
  std::vector<std::string> SuggestFriends(const std::string& p1);

private:
  // Decide what member variables need to be here
  std::map<std::string, std::vector<std::string>> SocialNetwork networkMap_;

#endif
