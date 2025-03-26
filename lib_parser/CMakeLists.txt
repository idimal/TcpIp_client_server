cmake_minimum_required(VERSION 3.22.1)
project(LibParserSaver VERSION 1.0)

set(SOURCES
    src/class_parser.cpp
    src/class_saver.cpp
    src/structs.cpp
)

set(HEADERS
    include/MyLibrary/class_parser.h
    include/MyLibrary/class_saver.h
)

add_library(LibParserSaver STATIC ${SOURCES})

find_package(pugixml REQUIRED)

target_link_libraries(LibParserSaver PUBLIC pugixml::pugixml)

target_include_directories(LibParserSaver PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS LibParserSaver
    EXPORT LibParserSaverTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/ DESTINATION include)


include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/LibParserSaverConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/LibParserSaverConfig.cmake
    INSTALL_DESTINATION lib/cmake/LibParserSaver
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/LibParserSaverConfigVersion.cmake
    VERSION ${LibParserSaver_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(EXPORT LibParserSaverTargets
    FILE LibParserSaverTargets.cmake
    DESTINATION lib/cmake/LibParserSaver
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/LibParserSaverConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/LibParserSaverConfigVersion.cmake
    DESTINATION lib/cmake/LibParserSaver
)







