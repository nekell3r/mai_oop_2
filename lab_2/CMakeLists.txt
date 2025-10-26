cmake_minimum_required(VERSION 3.14)
project(lab2 CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(lab2_lib STATIC
    src/array.cpp
    src/binary.cpp
)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_binary tests/test_binary.cpp)
target_link_libraries(test_binary lab2_lib gtest_main)
add_test(NAME BinaryTests COMMAND test_binary)

add_executable(lab2_demo src/main.cpp)
target_link_libraries(lab2_demo lab2_lib)

add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS test_binary
)
