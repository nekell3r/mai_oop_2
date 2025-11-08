#include "array.hpp"

#include <stdexcept>

namespace lab2 {

Array::Array() : size_(0), data_(nullptr) {}

Array::Array(const size_t& n, unsigned char val) {
  size_ = n;
  data_ = new unsigned char[n];
  for (size_t i = 0; i < n; i++) {
    data_[i] = val;
  }
}

Array::Array(const std::initializer_list<unsigned char>& lst) {
  size_ = lst.size();
  data_ = new unsigned char[size_];
  size_t idx = 0;
  for (const auto& elem : lst) {
    data_[idx] = elem;
    idx++;
  }
}

Array::Array(const std::string& str) {
  size_ = str.size();
  data_ = new unsigned char[size_];
  for (size_t i = 0; i < size_; i++) {
    data_[i] = (unsigned char)str[i];
  }
}

Array::Array(const Array& other) {
  size_ = other.size_;
  if (size_ > 0) {
    data_ = new unsigned char[size_];
    for (size_t i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  } else {
    data_ = nullptr;
  }
}

Array::Array(Array&& other) noexcept {
  size_ = other.size_;
  data_ = other.data_;
  other.size_ = 0;
  other.data_ = nullptr;
}

Array& Array::operator=(const Array& other) {
  if (this == &other) {
    return *this;
  }
  delete[] data_;
  size_ = other.size_;
  data_ = new unsigned char[size_];
  for (size_t i = 0; i < size_; i++) {
    data_[i] = other.data_[i];
  }
  return *this;
}

Array& Array::operator=(Array&& other) noexcept {
  if (this != &other) {
    delete[] data_;
    size_ = other.size_;
    data_ = other.data_;
    other.size_ = 0;
    other.data_ = nullptr;
  }
  return *this;
}

bool Array::Equals(const Array& other) const {
  if (size_ != other.size_) {
    return false;
  }
  for (size_t i = 0; i < size_; i++) {
    if (data_[i] != other.data_[i]) {
      return false;
    }
  }
  return true;
}

bool Array::MoreThan(const Array& other) const {
  if (size_ != other.size_) {
    return size_ > other.size_;
  }
  for (size_t i = 0; i < size_; i++) {
    if (data_[i] > other.data_[i]) {
      return true;
    }
    if (data_[i] < other.data_[i]) {
      return false;
    }
  }
  return false;
}

bool Array::LessThan(const Array& other) const {
  if (other.size_ != size_) {
    return size_ < other.size_;
  }
  for (size_t i = 0; i < size_; i++) {
    if (data_[i] > other.data_[i]) {
      return false;
    }
    if (data_[i] < other.data_[i]) {
      return true;
    }
  }
  return false;
}

void Array::InsertIndex(size_t index, char toInsert) {
  if (index >= size_) {
    throw std::out_of_range("Index out of array bounds");
  }
  data_[index] = (unsigned char)toInsert;
}

std::ostream& Array::Print(std::ostream& os) {
  for (size_t i = 0; i < size_; i++) {
    os << data_[i];
  }
  return os;
}

size_t Array::GetSize() const {
  return size_;
}

unsigned char* Array::GetData() const {
  return data_;
}

void Array::SetData(size_t sz, unsigned char* d) {
  delete[] data_;
  size_ = sz;
  data_ = d;
}

void Array::SetSize(size_t sz) {
  if (sz == size_) {
    return;
  }
  unsigned char* newData = new unsigned char[sz];
  size_t copyLen = sz < size_ ? sz : size_;
  for (size_t i = 0; i < copyLen; i++) {
    newData[i] = data_[i];
  }
  for (size_t i = copyLen; i < sz; i++) {
    newData[i] = '0';
  }
  delete[] data_;
  data_ = newData;
  size_ = sz;
}

Array::~Array() noexcept {
  delete[] data_;
  data_ = nullptr;
  size_ = 0;
}

}  // namespace lab2
