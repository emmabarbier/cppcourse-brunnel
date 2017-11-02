cmake_minimum_required (VERSION 2.6)
project (Neuron)
set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

enable_testing()
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test3 neuron.cpp test3.cpp)
add_executable(test4 network.cpp neuron.cpp test4.cpp)

add_executable(NeuronProject_unittest neuron.cpp network.cpp NeuronProject_unittest.cpp)

target_link_libraries(NeuronProject_unittest gtest gtest_main)
add_test(NeuronProject_unittest NeuronProject_unittest)
