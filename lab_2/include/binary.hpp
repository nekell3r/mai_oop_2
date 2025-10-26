#pragma once

#include "array.hpp"

#include <cstddef>
#include <iostream>
#include <string>

namespace lab2 {

class Binary {
 public:
  Binary();
  Binary(const size_t& n, unsigned char t = '0');
  Binary(const std::initializer_list<unsigned char>& t);
  Binary(const std::string& t);
  Binary(const Binary& other);
  Binary(Binary&& other) noexcept;

  Binary& operator=(const Binary& other);
  Binary& operator=(Binary&& other) noexcept;

  virtual ~Binary() noexcept = default;

  Binary Add(const Binary& other) const;
  Binary Subtract(const Binary& other) const;

  bool IsEqual(const Binary& other) const;
  bool IsGreater(const Binary& other) const;
  bool IsLess(const Binary& other) const;

  Binary Copy() const;
  std::ostream& Print(std::ostream& outputStream) const;
  size_t GetSize() const;
  std::string ToString() const;

 private:
  Array digits_;
  void validate(const std::string& str) const;
};

}  // namespace lab2
