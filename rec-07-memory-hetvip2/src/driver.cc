#include <iostream>
#include "Sport.hpp"

int main() {
  Sport* sports = new Sport[2];
  unsigned int size = 0;
  unsigned int capacity = 2;

  Sport football = {"Football", 10};
  Sport volleyball = {"Volleyball", 5};
  PushBackToSportArray(sports, size, capacity, football);
  PushBackToSportArray(sports, size, capacity, volleyball);

  Sport* ultimate_frisbee = new Sport{"Ultimate Frisbee", 7};
  PushBackToSportArray(sports, size, capacity, *ultimate_frisbee);
  delete ultimate_frisbee;
  Sport* hockey = MakeSport("Hockey", 6);
  PushBackToSportArray(sports, size, capacity, *hockey);
  delete hockey;
  int* to_change = new int[2];
  to_change[0] = 0;
  to_change[1] = 1;
  AddToPlayerCount(sports, size, to_change, 2);
  delete[] to_change;
  delete[] sports;
}