// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Jule Schatz                    Environment : ubuntu:bionic               //
//  Date ......: 2023/12/29                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "social_network.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
bool VectorCompare(const std::vector<std::string>& vec1,
                   const std::vector<std::string>& vec2) {
  if (vec1.size() != vec2.size()) return false;

  for (unsigned int i = 0; i < vec1.size(); i++) {
    if (vec1.at(i) != vec2.at(i)) return false;
  }
  return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////
TEST_CASE("Social Network Add and Are Friends",
          "[social-network-add-are-friends]") {
  SocialNetwork network;

  // Setting up Alice with all her friends, Bob, Charlie, Michelle, Mary, Steve,
  // and Amir
  network.AddFriends("Alice", "Bob");
  network.AddFriends("Bob", "Charlie");

  REQUIRE(network.AreFriends("Alice", "Bob"));
  REQUIRE(network.AreFriends("Bob", "Alice"));
  REQUIRE(network.AreFriends("Bob", "Charlie"));
  REQUIRE(network.AreFriends("Charlie", "Bob"));

  REQUIRE(network.AreFriends("Alice", "Charlie") == false);
  REQUIRE(network.AreFriends("Charlie", "Alice") == false);
}

TEST_CASE("Social Network Suggest Friends",
          "[social-network-suggest-friends]") {
  SocialNetwork network;

  // Setting up Alice with all her friends, Bob, Charlie, Michelle, Mary, Steve,
  // and Amir
  network.AddFriends("Alice", "Bob");
  network.AddFriends("Alice", "Charlie");
  network.AddFriends("Alice", "Michelle");
  network.AddFriends("Alice", "Mary");
  network.AddFriends("Alice", "Steve");
  network.AddFriends("Alice", "Amir");

  // Charlie, Michelle, amd Amir are also both friends with Mary
  // Since Mary is already friends with Alice it won't suggest her as potential
  // friend
  network.AddFriends("Mary", "Charlie");
  network.AddFriends("Mary", "Michelle");
  network.AddFriends("Mary", "Amir");

  // Bob, Charlie, Steve, and Amir all made a new friend named May
  network.AddFriends("Bob", "May");
  network.AddFriends("Charlie", "May");
  network.AddFriends("Steve", "May");
  network.AddFriends("Amir", "May");

  // Charlie and Michelle made a new friend named Sara
  network.AddFriends("Charlie", "Sara");
  network.AddFriends("Michelle", "Sara");

  // Sara and May happen to be friends
  network.AddFriends("Sara", "May");

  // Charlie and Steve are also friends with Emma
  network.AddFriends("Charlie", "Emma");
  network.AddFriends("Steve", "Emma");

  // Bob has a friend no one else knows named Lee
  network.AddFriends("Bob", "Lee");

  // Turns out Lee and May know each other
  network.AddFriends("Lee", "May");

  // Suggest friends for Alice
  std::vector<std::string> suggested_friends_alice_actual =
      network.SuggestFriends("Alice");
  std::vector<std::string> suggested_friends_alice_expected = {
      "May", "Emma", "Sara", "Lee"};

  REQUIRE(VectorCompare(suggested_friends_alice_actual,
                        suggested_friends_alice_expected));
}

/////////////////////////////////////////////////////////////////////////////////////////////