#include "elevation_dataset.hpp"

#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);

  int e = 0;
  size_t count = 0;
  data_.resize(height_, std::vector<int>(width_));
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      ifs >> e;
      if (ifs.fail()) {
        throw std::invalid_argument("invalid");
      }
      data_.at(row).at(col) = e;
      count++;
    }
  }
  if (ifs >> e) {
    throw std::invalid_argument("data overload");
  }
  if (count != width_ * height_) {
    throw std::invalid_argument("invalid");
  }
  min_ele_ = data_.at(0).at(0);
  max_ele_ = data_.at(0).at(0);

  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      if (data_.at(row).at(col) < min_ele_) {
        min_ele_ = data_.at(row).at(col);
      }
      if (data_.at(row).at(col) > max_ele_) {
        max_ele_ = data_.at(row).at(col);
      }
    }
  }
}

size_t ElevationDataset ::Width() const { return width_; }
size_t ElevationDataset ::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset ::MinEle() const { return min_ele_; }
int ElevationDataset ::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset ::GetData() const {
  return data_;
}