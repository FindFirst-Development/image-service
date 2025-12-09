cmake_minimum_required(VERSION 3.15)
project(Hello_Crow CXX)

find_package(Crow REQUIRED)

# find_package(crowcpp-crow CONFIG REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Hello_Crow src/main.cpp)

add_custom_target(copy-compile-commands ALL
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
          ${CMAKE_BINARY_DIR}/compile_commands.json
          ${CMAKE_SOURCE_DIR}/compile_commands.json
  COMMENT "Copying compile_commands.json to project root" 
  VERBATIM)

add_custom_target(run
  COMMAND $<TARGET_FILE:Hello_Crow>
  DEPENDS Hello_Crow 
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)


target_link_libraries(Hello_Crow Crow::Crow)
