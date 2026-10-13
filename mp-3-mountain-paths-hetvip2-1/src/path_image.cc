#include "path_image.hpp"

#include <cmath>
#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(dataset.Width()),
    height_(dataset.Height()),
    path_image_(image.GetImage()) {
  for (size_t row = 0; row < dataset.Height(); ++row) {
    Path pat(dataset.Width(), row);
    pat.SetLoc(0, pat.StartingRow());
    for (size_t col = 1; col < dataset.Width(); ++col) {
      UpdatePathAndElevation(pat, dataset, col);
    }
    paths_.push_back(pat);
    if (pat.EleChange() < row_min_) {
      row_min_ = pat.EleChange();
      best_path_row_ = row;
    }
  }

  const Color kGreen(31, 253, 13);
  const Color kRed(252, 25, 63);

  for (size_t i = 0; i < paths_.size(); ++i) {
    for (size_t j = 0; j < paths_.at(i).Length(); ++j) {
      path_image_.at(paths_.at(i).GetPath().at(j)).at(j) = kRed;
    }
  }

  for (size_t i = 0; i < paths_.at(best_path_row_).Length(); ++i) {
    path_image_.at(paths_.at(best_path_row_).GetPath().at(i)).at(i) = kGreen;
  }
}
size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
/*A "magic number" for identifying the file type, followed by a new line.
We will use "P3" in this assignment to identify a plain PPM file
The width followed by the height of the image in pixels. Both are integers
separated by a space. On its own line, the maximum color value, which must be
between 0 and 65536, exclusive. For our assignment, this value will be 255. Each
following line represents the R, then G, then B values for each pixel. Include
an empty line at the end of the file.*/
void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3\n";
  ofs << width_ << " " << height_;
  ofs << "\n" << kMaxColorValue << "\n";
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      ofs << path_image_.at(i).at(j).Red() << " "
          << path_image_.at(i).at(j).Green() << " "
          << path_image_.at(i).at(j).Blue() << " ";
    }
    ofs << "\n";
  }
}
// Helper function to update the path and elevation changes for a given column
void PathImage::UpdatePathAndElevation(Path& pat,
                                       const ElevationDataset& dataset,
                                       size_t col) {
  
  int down = INT16_MAX;
  size_t p = pat.GetPath().at(col - 1);
  if (p < dataset.Height() - 1) {
    down = dataset.DatumAt(p + 1, col);
  }
  int up = INT16_MAX;
  if (p > 0) {
    up = dataset.DatumAt(p - 1, col);
  }
  int back = dataset.DatumAt(p, col - 1);
  int forward = abs(dataset.DatumAt(p, col) - back);
  int movedown = abs(down - back);
  int moveup = abs(up - back);
  int min = std::min(forward, std::min(movedown, moveup));
  pat.IncEleChange(min);
  if (forward == min) {
    pat.SetLoc(col, p);
  } else if (movedown == min) {
    pat.SetLoc(col, p + 1);
  } else if (moveup == min) {
    pat.SetLoc(col, p - 1);
  }
}
