#include "cord.hpp"

#include <stdexcept>

#include "cord_utilities.hpp"

Cord::Cord(std::string_view sv) {
  if (sv.empty()) {
    throw std::invalid_argument("size 0");
  }

  data_ = new char[sv.size() + 1];
  length_ = sv.size();

  for (size_t i = 0; i < sv.size(); ++i) {
    data_[i] = sv.at(i);
  }
  data_[sv.size()] = '\0';
}

Cord::~Cord() { delete[] data_; }

SharedPointer<char> Cord::ToString() const {
  if (data_ != nullptr) {
    unsigned int l = Length() + 1;
    char* new_char = new char[l];
    for (unsigned int i = 0; i < l; ++i) {
      new_char[i] = data_[i];
    }
    new_char[l - 1] = '\0';
    SharedPointer<char> s =
        SharedPointer<char>(new_char, kSharedPointerType::kArray);
    return s;
  }
  SharedPointer<char> left = left_->ToString();
  SharedPointer<char> right = right_->ToString();
  unsigned int left_length = left_->Length();
  unsigned int right_length = right_->Length();
  unsigned int total_length = left_length + right_length + 1;
  char* concatenated_string = new char[total_length];
  for (unsigned int i = 0; i < left_length; ++i) {
    concatenated_string[i] = left.Get()[i];
  }
  for (unsigned int i = 0; i < right_length; ++i) {
    concatenated_string[left_length + i] = right.Get()[i];
  }
  concatenated_string[total_length - 1] = '\0';
  SharedPointer<char> r =
      SharedPointer<char>(concatenated_string, kSharedPointerType::kArray);
  return r;
}
