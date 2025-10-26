cmake_minimum_required(VERSION 3.14)
project(lab2 CXX)

# Устанавливаем стандарт C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Флаги компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

# Пути к заголовочным файлам
include_directories(${PROJECT_SOURCE_DIR}/include)

# Библиотека с классами
add_library(lab2_lib STATIC
    src/array.cpp
    src/binary.cpp
)

# Подключаем Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# Для Windows: предотвращаем перезапись флагов компиляции родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Включаем тестирование
enable_testing()

# Тесты для Binary
add_executable(test_binary tests/test_binary.cpp)
target_link_libraries(test_binary lab2_lib gtest_main)
add_test(NAME BinaryTests COMMAND test_binary)

# Исполняемый файл с демонстрацией
add_executable(lab2_demo src/main.cpp)
target_link_libraries(lab2_demo lab2_lib)

# Общая цель для запуска всех тестов
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_binary
)
