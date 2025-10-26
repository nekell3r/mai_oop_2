#include "binary.hpp"

#include <algorithm>
#include <stdexcept>

namespace lab2 {

Binary::Binary() : digits_() {}

Binary::Binary(const size_t& n, unsigned char t) : digits_(n, t) {
  if (t != '0' && t != '1') {
    throw std::invalid_argument("Binary digit must be '0' or '1'");
  }
}

Binary::Binary(const std::initializer_list<unsigned char>& lst) {
  for (const auto& d : lst) {
    if (d != '0' && d != '1') {
      throw std::invalid_argument("Binary digit must be '0' or '1'");
    }
  }
  std::string s(lst.begin(), lst.end());
  std::reverse(s.begin(), s.end());
  digits_ = Array(s);
}

Binary::Binary(const std::string& s) {
  validate(s);
  std::string rev = s;
  std::reverse(rev.begin(), rev.end());
  digits_ = Array(rev);
}

Binary::Binary(const Binary& other) : digits_(other.digits_) {}

Binary::Binary(Binary&& other) noexcept : digits_(std::move(other.digits_)) {}

Binary& Binary::operator=(const Binary& other) {
  if (this != &other) {
    digits_ = other.digits_;
  }
  return *this;
}

Binary& Binary::operator=(Binary&& other) noexcept {
  if (this != &other) {
    digits_ = std::move(other.digits_);
  }
  return *this;
}

void Binary::validate(const std::string& s) const {
  if (s.empty()) {
    throw std::invalid_argument("Binary string cannot be empty");
  }
  for (const char c : s) {
    if (c != '0' && c != '1') {
      throw std::invalid_argument("Binary string must contain only '0' and '1'");
    }
  }
}

Binary Binary::Add(const Binary& other) const {
  const size_t mx = std::max(digits_.GetSize(), other.digits_.GetSize());
  const size_t sz = mx + 1;
  Binary res(sz, '0');
  unsigned char carry = 0;

  for (size_t i = 0; i < sz; ++i) {
    unsigned char d1 = (i < digits_.GetSize()) ? digits_.GetData()[i] : '0';
    unsigned char d2 = (i < other.digits_.GetSize()) ? other.digits_.GetData()[i] : '0';
    unsigned char v1 = d1 - '0';
    unsigned char v2 = d2 - '0';
    unsigned char sum = v1 + v2 + carry;
    carry = sum / 2;
    unsigned char dr = (sum % 2) + '0';
    res.digits_.InsertIndex(i, dr);
  }

  size_t actual = sz;
  while (actual > 1 && res.digits_.GetData()[actual - 1] == '0') {
    --actual;
  }
  res.digits_.SetSize(actual);
  return res;
}

Binary Binary::Subtract(const Binary& other) const {
  if (IsLess(other)) {
    throw std::invalid_argument("Cannot subtract: result would be negative");
  }
  const size_t mx = std::max(digits_.GetSize(), other.digits_.GetSize());
  Binary res(mx, '0');
  unsigned char borrow = 0;

  for (size_t i = 0; i < mx; ++i) {
    unsigned char d1 = (i < digits_.GetSize()) ? digits_.GetData()[i] : '0';
    unsigned char d2 = (i < other.digits_.GetSize()) ? other.digits_.GetData()[i] : '0';
    unsigned char v1 = d1 - '0';
    unsigned char v2 = d2 - '0';
    int diff = v1 - v2 - borrow;
    if (diff < 0) {
      diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    res.digits_.InsertIndex(i, static_cast<char>(diff + '0'));
  }

  size_t actual = mx;
  while (actual > 1 && res.digits_.GetData()[actual - 1] == '0') {
    --actual;
  }
  res.digits_.SetSize(actual);
  return res;
}

bool Binary::IsEqual(const Binary& other) const {
  return digits_.Equals(other.digits_);
}

bool Binary::IsGreater(const Binary& other) const {
  return digits_.MoreThan(other.digits_);
}

bool Binary::IsLess(const Binary& other) const {
  return digits_.LessThan(other.digits_);
}

Binary Binary::Copy() const {
  return Binary(*this);
}

std::ostream& Binary::Print(std::ostream& os) const {
  for (size_t i = digits_.GetSize(); i > 0; --i) {
    os << digits_.GetData()[i - 1];
  }
  return os;
}

size_t Binary::GetSize() const {
  return digits_.GetSize();
}

std::string Binary::ToString() const {
  std::string s;
  for (size_t i = digits_.GetSize(); i > 0; --i) {
    s += static_cast<char>(digits_.GetData()[i - 1]);
  }
  return s;
}

}  // namespace lab2
