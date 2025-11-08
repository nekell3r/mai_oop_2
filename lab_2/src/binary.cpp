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
  for (const auto& digit : lst) {
    if (digit != '0' && digit != '1') {
      throw std::invalid_argument("Binary digit must be '0' or '1'");
    }
  }
  std::string temp(lst.begin(), lst.end());
  std::reverse(temp.begin(), temp.end());
  digits_ = Array(temp);
}

Binary::Binary(const std::string& s) {
  validate(s);
  std::string reversed = s;
  std::reverse(reversed.begin(), reversed.end());
  digits_ = Array(reversed);
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
  for (size_t i = 0; i < s.length(); i++) {
    if (s[i] != '0' && s[i] != '1') {
      throw std::invalid_argument("Binary string must contain only '0' and '1'");
    }
  }
}

Binary Binary::Add(const Binary& other) const {
  size_t maxSize = std::max(digits_.GetSize(), other.digits_.GetSize());
  size_t resultSize = maxSize + 1;
  Binary result(resultSize, '0');
  unsigned char carry = 0;

  for (size_t i = 0; i < resultSize; i++) {
    unsigned char digit1 = (i < digits_.GetSize()) ? digits_.GetData()[i] : '0';
    unsigned char digit2 = (i < other.digits_.GetSize()) ? other.digits_.GetData()[i] : '0';
    unsigned char val1 = digit1 - '0';
    unsigned char val2 = digit2 - '0';
    unsigned char sum = val1 + val2 + carry;
    carry = sum / 2;
    unsigned char resultDigit = (sum % 2) + '0';
    result.digits_.InsertIndex(i, resultDigit);
  }

  size_t finalSize = resultSize;
  while (finalSize > 1 && result.digits_.GetData()[finalSize - 1] == '0') {
    finalSize--;
  }
  result.digits_.SetSize(finalSize);
  return result;
}

Binary Binary::Subtract(const Binary& other) const {
  if (IsLess(other)) {
    throw std::invalid_argument("Cannot subtract: result would be negative");
  }
  size_t maxSize = std::max(digits_.GetSize(), other.digits_.GetSize());
  Binary result(maxSize, '0');
  unsigned char borrow = 0;

  for (size_t i = 0; i < maxSize; i++) {
    unsigned char digit1 = (i < digits_.GetSize()) ? digits_.GetData()[i] : '0';
    unsigned char digit2 = (i < other.digits_.GetSize()) ? other.digits_.GetData()[i] : '0';
    int val1 = digit1 - '0';
    int val2 = digit2 - '0';
    int diff = val1 - val2 - borrow;
    if (diff < 0) {
      diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    result.digits_.InsertIndex(i, (char)(diff + '0'));
  }

  size_t finalSize = maxSize;
  while (finalSize > 1 && result.digits_.GetData()[finalSize - 1] == '0') {
    finalSize--;
  }
  result.digits_.SetSize(finalSize);
  return result;
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
  size_t len = digits_.GetSize();
  for (size_t i = len; i > 0; i--) {
    os << digits_.GetData()[i - 1];
  }
  return os;
}

size_t Binary::GetSize() const {
  return digits_.GetSize();
}

std::string Binary::ToString() const {
  std::string str;
  size_t len = digits_.GetSize();
  for (size_t i = len; i > 0; i--) {
    str += (char)digits_.GetData()[i - 1];
  }
  return str;
}

}  // namespace lab2
