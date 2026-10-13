#include "cord_utilities.hpp"

#include <stdexcept>

SharedPointer<Cord> ConcatCords(SharedPointer<Cord> left_cord,
                                SharedPointer<Cord> right_cord) {
  if (left_cord.Get() == nullptr || right_cord.Get() == nullptr) {
    throw std::invalid_argument("right or left is empty");
  }
  Cord* cord = new Cord();
  cord->length_ = left_cord->length_ + right_cord->length_;
  cord->right_ = right_cord;
  cord->left_ = left_cord;

  SharedPointer<Cord> sp(cord, kSharedPointerType::kObject);
  return sp;
}

SharedPointer<Cord> SubString(SharedPointer<Cord> curr_cord,
                              unsigned int lower_idx,
                              unsigned int upper_idx) {
  if (curr_cord.Get() == nullptr) {
    throw std::invalid_argument("not valid");
  }
  if (lower_idx >= upper_idx || lower_idx < 0 ||
      upper_idx > curr_cord->Length()) {
    throw std::invalid_argument("invalid substring indices");
  }
  unsigned int l = upper_idx - lower_idx;
  if (curr_cord->Length() == l) {
    return curr_cord;
  }
  if (curr_cord->Left().Get() == nullptr ||
      curr_cord->Right().Get() == nullptr) {
    auto data = curr_cord->Data().substr(lower_idx, (l));
    Cord* cordobj = new Cord(data);
    SharedPointer<Cord> r = SharedPointer(cordobj);
    return r;
  }
  if (upper_idx <= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Left(), lower_idx, upper_idx);
  }

  if (lower_idx >= curr_cord->Left()->Length()) {
    return SubString(curr_cord->Right(),
                     lower_idx - curr_cord->Left()->Length(),
                     upper_idx - curr_cord->Left()->Length());
  }
  SharedPointer<Cord> left_substring =
      SubString(curr_cord->Left(), lower_idx, curr_cord->Left()->Length());
  SharedPointer<Cord> right_substring =
      SubString(curr_cord->Right(), 0, upper_idx - curr_cord->Left()->Length());

  return ConcatCords(left_substring, right_substring);
}
