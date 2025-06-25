#include "color.hpp"

#include <stdexcept>

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed...
  if (red_ < kColorValueMin || red_ > kColorValueMax) {
    throw std::invalid_argument("not valid red");
  }
  if (green_ < kColorValueMin || green_ > kColorValueMax) {
    throw std::invalid_argument("not valid green");
  }
  if (blue_ < kColorValueMin || blue_ > kColorValueMax) {
    throw std::invalid_argument("not valid blue");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}
