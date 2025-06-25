#include "seam_carver.hpp"

#include <iostream>

#include "image_ppm.hpp"
#include "pixel.hpp"

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}
// returns the instance's image_
const ImagePPM& SeamCarver::GetImage() const { return image_; }

// returns the image's height
int SeamCarver::GetHeight() const { return height_; }

// returns the image's width
int SeamCarver::GetWidth() const { return width_; }

// returns the energy of the pixel at row col in image_
int SeamCarver::GetEnergy(int row, int col) const {
  int h = image_.GetHeight();
  int w = image_.GetWidth();
  int r = row;
  int rp = row + 1;
  int rm = row - 1;
  int c = col;
  int cp = col + 1;
  int cm = col - 1;

  if (cp >= w) {
    cp = 0;
  }
  if (cm < 0) {
    cm = w - 1;
  }
  if (rp >= h) {
    rp = 0;
  }
  if (rm < 0) {
    rm = h - 1;
  }

  int r_col = image_.GetPixel(r, cm).GetRed() - image_.GetPixel(r, cp).GetRed();
  int g_col =
      image_.GetPixel(r, cm).GetGreen() - image_.GetPixel(r, cp).GetGreen();
  int b_col =
      image_.GetPixel(r, cm).GetBlue() - image_.GetPixel(r, cp).GetBlue();

  int r_row = image_.GetPixel(rm, c).GetRed() - image_.GetPixel(rp, c).GetRed();
  int g_row =
      image_.GetPixel(rm, c).GetGreen() - image_.GetPixel(rp, c).GetGreen();
  int b_row =
      image_.GetPixel(rm, c).GetBlue() - image_.GetPixel(rp, c).GetBlue();

  int energy = (r_col * r_col) + (g_col * g_col) + (b_col * b_col) +
               (r_row * r_row) + (g_row * g_row) + (b_row * b_row);
  return energy;
}

// returns the horizontal seam of image_ with the least amount of
// energy
//
// the ith int in the returned array corresponds to which row at
// col i is in the seam. example:
//
//    | x |   |
// ---+---+---+---
//  x |   | x |
// ---+---+---+---
//    |   |   | x
// returns {1, 0, 1, 2}

void SeamCarver::HorzHelp(int** v) const {
  int** hseam = v;
  int height = image_.GetHeight();
  int width = image_.GetWidth();
  for (int col = width - 2; col >= 0; col--) {
    for (int row = 0; row < height; row++) {
      if (row == 0) {
        int right = hseam[row][col + 1];
        int br = hseam[row + 1][col + 1];
        hseam[row][col] = GetEnergy(row, col) + std::min(right, br);
      } else if (row == height - 1) {
        int tr = hseam[row - 1][col + 1];
        int r = hseam[row][col + 1];
        hseam[row][col] = GetEnergy(row, col) + std::min(tr, r);
      } else {
        int tr = hseam[row - 1][col + 1];
        int r = hseam[row][col + 1];
        int br = hseam[row + 1][col + 1];
        hseam[row][col] = GetEnergy(row, col) + std::min({tr, r, br});
      }
    }
  }
}
void SeamCarver::HorzHelp2(int** v, int* s) const {
  int* seam = s;
  int** hseam = v;
  int height = image_.GetHeight();
  int width = image_.GetWidth();
  for (int col = 0; col < width - 1; col++) {
    if (seam[col] == 0) {
      int row = 0;
      int r = hseam[row][col + 1];
      int br = hseam[row + 1][col + 1];
      seam[col + 1] = (r <= br) ? row : row + 1;
    } else if (seam[col] == height - 1) {
      int row = seam[col];
      int tr = hseam[row - 1][col + 1];
      int r = hseam[row][col + 1];
      seam[col + 1] = (r <= tr) ? row : row - 1;
    } else {
      int row = seam[col];
      int tr = hseam[row - 1][col + 1];
      int r = hseam[row][col + 1];
      int br = hseam[row + 1][col + 1];
      if (r <= tr && r <= br) {
        seam[col + 1] = row;
      } else if (tr <= r && tr <= br) {
        seam[col + 1] = row - 1;
      } else {
        seam[col + 1] = row + 1;
      }
    }
  }
}
int* SeamCarver::GetHorizontalSeam() const {
  int height = image_.GetHeight();
  int width = image_.GetWidth();
  int* seam = new int[width];
  int** hseam = new int*[height];
  for (int row = 0; row < height; ++row) {
    hseam[row] = new int[width];
  }
  for (int row = 0; row < height; row++) {
    hseam[row][width - 1] = GetEnergy(row, width - 1);
  }
  HorzHelp(hseam);
  int start = hseam[0][0];
  int minval = 0;
  for (int i = 0; i < height; i++) {
    if (hseam[i][0] < start) {
      start = hseam[i][0];
      minval = i;
    }
  }
  seam[0] = minval;
  HorzHelp2(hseam, seam);
  for (int j = 0; j < height; ++j) {
    delete[] hseam[j];
  }
  delete[] hseam;
  return seam;
}
// returns the vertical seam of image_ with the least amount of
// energy
//
// the ith int in the returned array corresponds to which col at
// row i is in the seam. example:
//
//    | x |   |
// ---+---+---+---
//    |   | x |
// ---+---+---+---
//    |   | x |
// returns {1, 2, 2}

int SeamCarver::MinVertical() const {
  int height = image_.GetHeight();
  int width = image_.GetWidth();
  int** path = new int*[height];
  for (int col = 0; col < width; col++) {
    path[height - 1][col] = GetEnergy(height - 1, col);
  }
  for (int row = height - 2; row >= 0; row--) {
    for (int col = 0; col < width; col++) {
      int bl = (col > 0) ? GetEnergy(row + 1, col - 1) : INT16_MAX;
      int b = GetEnergy(row + 1, col);
      int br = (col < width - 1) ? GetEnergy(row + 1, col + 1) : INT16_MAX;
      int min = std::min({br, b, bl});
      path[row][col] = GetEnergy(row, col) + min;
    }
  }
  int val = 0;
  int start = path[0][0];
  for (int col = 0; col < width; ++col)
    if (path[0][col] < start) val = col, start = path[0][col];
  int min = val;
  for (int i = 0; i < height; i++) {
    delete[] path[i];
  }
  delete[] path;
  return min;
}

void SeamCarver::Vert(int** v) const {
  int** values = v;
  int width = image_.GetWidth();
  for (int row = height_ - 2; row >= 0; --row) {
    for (int col = 0; col < width; ++col) {
      values[row][col] =
          (col == 0) ? std::min(values[row + 1][col], values[row + 1][col + 1])
          : (col == width - 1)
              ? std::min(values[row + 1][col - 1], values[row + 1][col])
              : std::min({values[row + 1][col - 1],
                          values[row + 1][col],
                          values[row + 1][col + 1]});
      values[row][col] += GetEnergy(row, col);
    }
  }
}
void SeamCarver::Vhelp(int* seam, int** values) const {
  int val = 0;
  int start = values[0][0];
  for (int col = 0; col < image_.GetWidth(); ++col)
    if (values[0][col] < start) val = col, start = values[0][col];
  seam[0] = val;
}
int* SeamCarver::GetVerticalSeam() const {
  int* seam = new int[height_];
  int** values = new int*[height_];
  for (int row = 0; row < height_; ++row)
    values[row] = new int[image_.GetWidth()];
  for (int col = 0; col < image_.GetWidth(); ++col) {
    values[height_ - 1][col] = GetEnergy(height_ - 1, col);
  }
  Vert(values);
  Vhelp(seam, values);
  for (int row = 1; row < height_; ++row) {
    int col = seam[row - 1];
    int minval = (col == 0) ? std::min(values[row][col], values[row][col + 1])
                 : (col == image_.GetWidth() - 1)
                     ? std::min(values[row][col - 1], values[row][col])
                     : std::min({values[row][col - 1],
                                 values[row][col],
                                 values[row][col + 1]});
    seam[row] = (values[row][col] == minval)       ? col
                : (col == 0)                       ? col + 1
                : (col == image_.GetWidth() - 1)   ? col - 1
                : (values[row][col - 1] == minval) ? col - 1
                                                   : col + 1;
  }
  for (int row = 0; row < height_; ++row) delete[] values[row];
  delete[] values;
  return seam;
}
// removes one horizontal seam in image_. example:
//
// image_ before:
//  0 | 1 | 2 | 3
// ---+---+---+---
//  4 | 5 | 6 | 7
// ---+---+---+---
//  8 | 9 | 10| 11
//
// seam to remove:
//    | x |   |
// ---+---+---+---
//  x |   | x |
// ---+---+---+---
//    |   |   | x
//
// image_ after:
//  0 | 5 | 2 | 3
// ---+---+---+---
//  8 | 9 | 10| 7
void SeamCarver::RemoveHorizontalSeam() {
  int* hseam = GetHorizontalSeam();
  image_.HorizontalCarve(hseam);
  delete[] hseam;
  height_--;
}

// removes one vertical seam in image_. example:
//
// image_ before:
//  0 | 1 | 2 | 3
// ---+---+---+---
//  4 | 5 | 6 | 7
// ---+---+---+---
//  8 | 9 | 10| 11
//
// seam to remove:
//    | x |   |
// ---+---+---+---
//    |   | x |
// ---+---+---+---
//    |   | x |
//
// image_ after:
//  0 | 2 | 3
// ---+---+---
//  4 | 5 | 7
// ---+---+---
//  8 | 9 | 11
void SeamCarver::RemoveVerticalSeam() {
  int* vseam = GetVerticalSeam();
  image_.VerticalCarve(vseam);
  delete[] vseam;
  // width_--;
}