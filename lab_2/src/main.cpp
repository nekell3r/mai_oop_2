#include "binary.hpp"

#include <iostream>

int main() {
  std::cout << "=== Тест Binary ===\n\n";

  lab2::Binary b1("1010");
  lab2::Binary b2("11");

  std::cout << "Числа: ";
  b1.Print(std::cout);
  std::cout << " и ";
  b2.Print(std::cout);
  std::cout << "\n\n";

  std::cout << "Сложение: ";
  lab2::Binary sum = b1.Add(b2);
  sum.Print(std::cout);
  std::cout << "\n";

  std::cout << "Вычитание: ";
  lab2::Binary diff = b1.Subtract(b2);
  diff.Print(std::cout);
  std::cout << "\n\n";

  std::cout << "Сравнение:\n";
  std::cout << "  равны? " << (b1.IsEqual(b2) ? "да" : "нет") << "\n";
  std::cout << "  больше? " << (b1.IsGreater(b2) ? "да" : "нет") << "\n\n";

  lab2::Binary x("1111");
  lab2::Binary y("1");
  std::cout << "Цепочка: (1111 + 1) - 1010 = ";
  lab2::Binary temp = x.Add(y);
  lab2::Binary result = temp.Subtract(lab2::Binary("1010"));
  result.Print(std::cout);
  std::cout << "\n\n";

  std::cout << "Проверка ошибок:\n";
  try {
    lab2::Binary bad("102");
  } catch (const std::invalid_argument& e) {
    std::cout << "  ошибка: " << e.what() << "\n";
  }

  try {
    lab2::Binary a("10");
    lab2::Binary b("1010");
    a.Subtract(b);
  } catch (const std::invalid_argument& e) {
    std::cout << "  ошибка вычитания: " << e.what() << "\n";
  }

  std::cout << "\nГотово!\n";
  return 0;
}
