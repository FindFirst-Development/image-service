cmake_minimum_required(VERSION 3.15)
project(Hello_Crow CXX)

find_package(Crow REQUIRED)

add_executable(Hello_Crow src/main.cpp)

target_link_libraries(Hello_Crow Crow::Crow)
