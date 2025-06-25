#include "grayscale_image.hpp"

#include <cmath>
#include <cstdlib>  // for size_t
#include <string>
#include <vector>
#include <fstream>

#include "color.hpp"
#include "elevation_dataset.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  image_.resize(height_, std::vector<Color>(width_));
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      int shade_of_gray = 0;
      if (dataset.MaxEle() == dataset.MinEle()) {
        shade_of_gray = 0;
      } else {
        shade_of_gray = static_cast<int>(
            std::round(static_cast<double>(dataset.DatumAt(row, col) - dataset.MinEle()) /
                       static_cast<double>(dataset.MaxEle() - dataset.MinEle()) * kMaxColorValue));
      }
      image_.at(row).at(col) =
          Color(shade_of_gray, shade_of_gray, shade_of_gray);
    }
  }
}
GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    GrayscaleImage(ElevationDataset(filename, width, height)) {}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
/*A "magic number" for identifying the file type, followed by a new line.
We will use "P3" in this assignment to identify a plain PPM file
The width followed by the height of the image in pixels. Both are integers
separated by a space. On its own line, the maximum color value, which must be
between 0 and 65536, exclusive. For our assignment, this value will be 255. Each
following line represents the R, then G, then B values for each pixel. Include
an empty line at the end of the file.*/
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream output(name);
  output << "P3\n";
  output << width_ << " " << height_;
  output << "\n" << kMaxColorValue << "\n";
  for (size_t row = 0; row < height_; ++row) {
    for (size_t col = 0; col < width_; ++col) {
      output << image_.at(row).at(col).Red() << " "
             << image_.at(row).at(col).Green() << " "
             << image_.at(row).at(col).Blue() << " ";
    }
    output << "\n";
  }
  
}
