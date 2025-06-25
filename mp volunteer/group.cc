#include "group.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

#include "constants.hpp"
#include "volunteer.hpp"

void Group::AddVolunteer(const Volunteer& vol) { volunteerVec_.push_back(vol); }

double Group::GetAvgBuildingExp() const {
  if (volunteerVec_.empty()) {
    return 0.0;
  }
  double sum = 0.0;
  auto length = (double)volunteerVec_.size();
  for (unsigned int i = 0; i < volunteerVec_.size(); ++i) {
    sum += volunteerVec_.at(i).GetBuildingExperience();
  }
  return sum / length;
}

int Group::GetReturningMembers() const {
  int members = 0;
  for (unsigned int i = 0; i < volunteerVec_.size(); ++i) {
    if (volunteerVec_.at(i).IsReturning()) {
      members++;
    }
  }
  return members;
}

double Group::GetAvgStamina() const {
  double sum = 0.0;
  if (volunteerVec_.empty()) {
    return 0.0;
  }
  auto length = (double)volunteerVec_.size();
  for (unsigned int i = 0; i < volunteerVec_.size(); ++i) {
    sum += volunteerVec_.at(i).GetPhysicalStamina();
  }
  return sum / length;
}

std::ostream& operator<<(std::ostream& os, const Group& g_in) {
  os << "Group:" << g_in.volunteerVec_.size() << std::endl;
  for (size_t i = 0; i < g_in.volunteerVec_.size(); ++i) {
    os << g_in.volunteerVec_[i].GetName() << std::endl;
  }
  return os;
}

Volunteer& Group::GetRandomVolunteer() {
  if (volunteerVec_.empty()) {
    throw std::invalid_argument("no volunteers present");
  }
  int r = int(rand() % volunteerVec_.size());
  return volunteerVec_[r];
}
