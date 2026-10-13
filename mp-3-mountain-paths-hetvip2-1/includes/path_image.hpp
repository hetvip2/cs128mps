#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cmath>
#include <cstdlib>  // for size_t
#include <string>
#include <vector>
#include <iostream>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const std::vector<Path>& Paths() const;
  const std::vector<std::vector<Color>>& GetPathImage() const;
  void ToPpm(const std::string& name) const;

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  size_t best_path_row_ = 0;
  unsigned int row_min_ = INT32_MAX;
  void UpdatePathAndElevation(Path& pat, const ElevationDataset& dataset, size_t col);
};

#endif