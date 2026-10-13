#include <ctime>
#include <fstream>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "group.hpp"

/*Write your main driver in this file! Remember to seperate
out things into functions to help with readability and reusability.

See specifications for how to get started and
go to office hours if you need help!*/
std::vector<Group> GroupHelper(const std::string& fileInput) {
  std::vector<Group> groups;
  Group g;

  int group_num = 0;
  std::ifstream ifs(fileInput);
  std::string name;
  int stamina = 0;
  int exp = 0;
  bool r = false;

  while (ifs >> name >> exp >> stamina >> r) {
    Volunteer v(name, exp, stamina, r);
    std::cout << v.GetName() << std::endl;
    g.AddVolunteer(v);
    group_num++;
    if (group_num % kSizeGroups == 0) {
      groups.push_back(g);
      g = Group();
      group_num = 0;
    }
  }

  return groups;
}
bool ConditionCheck(const std::vector<Group>& kGroups) {
  for (unsigned int i = 0; i < kGroups.size(); ++i) {
    if (kGroups[i].GetAvgBuildingExp() < kMinAvgBuildingExp ||
        kGroups[i].GetAvgStamina() < kMinAvgStamina ||
        kGroups[i].GetReturningMembers() < kMinReturning) {
      return false;
    }
  }
  return true;
}
void SwapVolunteers(std::vector<Group>& groups) {
  int v1 = int(rand() % groups.size());
  int v2 = int(rand() % groups.size());
  std::swap(groups[v1].GetRandomVolunteer(), groups[v2].GetRandomVolunteer());
}

int main(int argc, char* argv[]) {
  // DO NOT EDIT THIS LINE or add another srand call.
  srand(time(nullptr));
  if (argc != 4) {
    return 1;
  }
  std::string in = argv[1];
  std::string output_file = argv[3];

  std::vector<Group> g = GroupHelper(in);

  unsigned int iterations = 0;

  while (!ConditionCheck(g)) {
    SwapVolunteers(g);
    iterations++;

    if (iterations == kMaxIterations) {
      break;
    }
  }
  std::cout << g.size() << std::endl;
  if (ConditionCheck(g)) {
    std::ofstream ofs(output_file);
    for (Group& gr : g) {
      ofs << gr;
      ofs << "\n";
    }
    ofs.close();
  } else {
    std::cout << "No groups found" << std::endl;
  }
}
