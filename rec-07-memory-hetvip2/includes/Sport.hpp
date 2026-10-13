#ifndef SPORT_HPP
#define SPORT_HPP

#include <iostream>
#include <map>
#include <vector>

struct Sport {
  std::string name;
  int number_players;
};

void PushBackToSportArray(Sport*& arr,
                          unsigned int& size,
                          unsigned int& capacity,
                          Sport value);

Sport* AddToPlayerCount(Sport arr[],
                        unsigned int size,
                        int change[],
                        int change_size);

Sport* MakeSport(const std::string& name_in, int number_players_in);

#endif
