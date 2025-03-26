cmake_minimum_required(VERSION 3.22.1)
project(server)

include_directories(include)

find_package(pugixml REQUIRED)
find_package(LibParserSaver REQUIRED)

add_executable(server src/server.cpp src/class_server.cpp)

target_link_libraries(server PRIVATE LibParserSaver)