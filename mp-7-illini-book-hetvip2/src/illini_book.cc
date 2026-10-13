#include "illini_book.hpp"

#include <fstream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "utilities.hpp"

// Your code here!
IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream people_stream(people_fpath);
  std::ifstream rel_stream(relations_fpath);
  std::string line;
  while (std::getline(people_stream, line)) {
    int p = std::stoi(line);
    relations_.emplace(p, std::list<std::pair<int, std::string>>{});
    line = "";
    peeps_.insert(p);
  }
  while (std::getline(rel_stream, line)) {
    std::vector<std::string> indline = utilities::Split(line, ',');
    int uin1 = std::stoi(indline.at(0));
    int uin2 = std::stoi(indline.at(1));
    std::string relation;
    relation = indline.at(2);
    relations_.find(uin1)->second.emplace_back(uin2, relation);
    relations_.find(uin2)->second.emplace_back(uin1, relation);
    line = "";
  }
}

// IlliniBook::~IlliniBook() {}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  if (peeps_.find(uin_1) == peeps_.end() ||
      peeps_.find(uin_2) == peeps_.end()) {
    return false;
  }
  std::queue<int> q;
  std::set<int> connect;
  q.push(uin_1);
  connect.insert(uin_1);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (const auto& next : relations_.at(curr)) {
      int n = next.first;
      if (n == uin_2) {
        return true;
      }
      if (connect.find(n) == connect.end()) {
        q.push(n);
        connect.insert(n);
      }
    }
  }
  return false;
}
bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  if (peeps_.find(uin_1) == peeps_.end() ||
      peeps_.find(uin_2) == peeps_.end()) {
    return false;
  }
  std::queue<int> q;
  std::set<int> connect;
  q.push(uin_1);
  connect.insert(uin_1);
  while (!q.empty()) {
    int curr = q.front();
    q.pop();
    for (const auto& next : relations_.at(curr)) {
      int n = next.first;
      const std::string& r = next.second;
      if (n == uin_2 && r == relationship) {
        return true;
      }
      if (connect.find(n) == connect.end() && r == relationship) {
        q.push(n);
        connect.insert(n);
      }
    }
  }
  return false;
}
int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  if (peeps_.find(uin_1) == peeps_.end() ||
      peeps_.find(uin_2) == peeps_.end()) {
    return -1;
  }
  std::queue<std::pair<int, int>> q;
  std::set<int> connect;
  q.push({uin_1, 0});
  connect.insert(uin_1);
  while (!q.empty()) {
    int curr = q.front().first;
    int distance = q.front().second;
    q.pop();
    if (curr == uin_2) {
      return distance;
    }
    for (const auto& next : relations_.at(curr)) {
      int n = next.first;
      if (connect.find(n) == connect.end()) {
        q.push({n, distance + 1});
        connect.insert(n);
      }
    }
  }
  return -1;
}
int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (peeps_.find(uin_1) == peeps_.end() ||
      peeps_.find(uin_2) == peeps_.end()) {
    return -1;
  }
  std::queue<std::pair<int, int>> q;
  std::set<int> connect;
  q.push({uin_1, 0});
  connect.insert(uin_1);
  while (!q.empty()) {
    int curr = q.front().first;
    int distance = q.front().second;
    q.pop();
    if (curr == uin_2) {
      return distance;
    }
    for (const auto& next : relations_.at(curr)) {
      int n = next.first;
      const std::string& rel = next.second;
      if (rel == relationship && connect.find(n) == connect.end()) {
        q.push({n, distance + 1});
        connect.insert(n);
      }
    }
  }
  return -1;
}
std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  std::vector<int> returnsteps;
  if (peeps_.find(uin) == peeps_.end()) {
    return returnsteps;
  }
  std::queue<std::pair<int, int>> q;
  std::set<int> connect;
  q.push({uin, 0});
  connect.insert(uin);
  while (!q.empty()) {
    int curr = q.front().first;
    int distance = q.front().second;
    q.pop();
    if (distance == n) {
      returnsteps.push_back(curr);
      continue;
    }
    for (const auto& next : relations_.at(curr)) {
      int n = next.first;
      if (connect.find(n) == connect.end()) {
        q.push({n, distance + 1});
        connect.insert(n);
      }
    }
  }
  return returnsteps;
}

size_t IlliniBook::CountGroups() const {
  size_t count = 0;
  std::set<int> connect;

  for (const auto& [uin, _] : relations_) {
    if (connect.find(uin) == connect.end()) {
      std::queue<int> q;
      q.push(uin);
      connect.insert(uin);
      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (const auto& next : relations_.at(curr)) {
          int n = next.first;
          if (connect.find(n) == connect.end()) {
            q.push(n);
            connect.insert(n);
          }
        }
      }
      count++;
    }
  }
  return count;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  size_t count = 0;
  std::set<int> connect;

  for (const auto& [uin, _] : relations_) {
    if (connect.find(uin) == connect.end()) {
      std::queue<int> q;
      q.push(uin);
      connect.insert(uin);
      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (const auto& next : relations_.at(curr)) {
          int n = next.first;
          const std::string& rel = next.second;
          if (connect.find(n) == connect.end() && rel == relationship) {
            q.push(n);
            connect.insert(n);
          }
        }
      }
      count++;
    }
  }
  return count;
}
size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  size_t count = 0;
  std::set<int> connect;
  for (const auto& [uin, _] : relations_) {
    if (connect.find(uin) == connect.end()) {
      std::queue<int> q;
      q.push(uin);
      connect.insert(uin);
      while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (const auto& next : relations_.at(curr)) {
          int n = next.first;
          const std::string& rel = next.second;
          if (connect.find(n) == connect.end() &&
              std::find(relationships.begin(), relationships.end(), rel) !=
                  relationships.end()) {
            q.push(n);
            connect.insert(n);
          }
        }
      }
      count++;
    }
  }
  return count;
}