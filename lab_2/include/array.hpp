#pragma once

#include <cstddef>
#include <iostream>
#include <string>

namespace lab2 {

class Array {
 public:
  Array();
  Array(const size_t& n, unsigned char t = 0);
  Array(const std::initializer_list<unsigned char>& t);
  Array(const std::string& t);
  Array(const Array& other);
  Array(Array&& other) noexcept;

  Array& operator=(const Array& other);
  Array& operator=(Array&& other) noexcept;

  bool Equals(const Array& other) const;
  bool MoreThan(const Array& other) const;
  bool LessThan(const Array& other) const;

  void InsertIndex(size_t index, char toInsert);
  std::ostream& Print(std::ostream& outputStream);

  size_t GetSize() const;
  unsigned char* GetData() const;

  void SetData(size_t newSize, unsigned char* newData);
  void SetSize(size_t newSize);

  virtual ~Array() noexcept;

 private:
  size_t size_;
  unsigned char* data_;
};

}  // namespace lab2
