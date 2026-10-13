#include "Sport.hpp"

// This function adds the passed in Sport object, value,
// to the passed in array, arr. If the array doesn't have
// space for another object, the function grows the array.
// capacity is the total availble space in arr while the
// size is the number of spaces that are being used
// in arr.
void PushBackToSportArray(Sport*& arr,
                          unsigned int& size,
                          unsigned int& capacity,
                          Sport value) {
  if (size == capacity) {
    capacity = capacity * 2;
    Sport* new_arr = new Sport[capacity];
    for (unsigned int i = 0; i < size; i++) {
      new_arr[i] = std::move(arr[i]);
    }
    delete[] arr;
    arr = new_arr;
  }
  arr[size] = std::move(value);
  size++;
}

// This function takes in an array of Sport objects called arr
// of size size. It then takes in another array called change
// of size change_size that holds the indicies of the Sport
// objects in arr that need to be adjusted. This function adjusts
// a Sports object by changing its number_players to be one greater.
//
// For example, if the change array has the values 1 and 3 then
// this function will add one to the number_players for the Sport
// objects in position 1 and 3 in arr.
Sport* AddToPlayerCount(Sport arr[],
                        unsigned int size,
                        int change[],
                        int change_size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < change_size; j++) {
      if (i == change[j]) {
        arr[i].number_players++;
      }
    }
  }
  return arr;
}

// This function takes in a name and a size returns the address
// of a Sport object with those parameters that can then be used.
Sport* MakeSport(const std::string& name_in, int number_players_in) {
  Sport* sp = new Sport{name_in, number_players_in};
  return sp;
}