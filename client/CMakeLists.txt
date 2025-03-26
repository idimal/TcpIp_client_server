cmake_minimum_required(VERSION 3.22.1)
project(client)
set(SOURCES client.cpp)
include_directories(include)

find_package(pugixml REQUIRED)
find_package(LibParserSaver REQUIRED)

add_executable(client src/client.cpp src/class_client.cpp)

target_link_libraries(client PRIVATE LibParserSaver)