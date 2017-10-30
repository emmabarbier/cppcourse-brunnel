cmake_minimum_required (VERSION 2.6)
project (Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test3 neuron.cpp test3.cpp)
add_executable(test4 network.cpp neuron.cpp test4.cpp)

add_executable(neuron_unittest neuron.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)
