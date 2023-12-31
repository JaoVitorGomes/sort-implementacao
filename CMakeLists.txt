cmake_minimum_required(VERSION 3.14)
project(lab2-sorting CXX)

set(INPUT_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/tests/data/")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/include/config.h) 

# Build the library
include_directories(include)
file(GLOB source_files src/*.cc)
add_library(siga ${source_files})
target_include_directories(siga PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Build the ctest executable
add_subdirectory(tests)
enable_testing()
add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)
add_test(NAME test3 COMMAND test3)
add_test(NAME test4 COMMAND test4)
add_test(NAME test5 COMMAND test5)
add_test(NAME test6 COMMAND test6)

# Build the main executable
add_executable(performance app/performance.cc)
target_link_libraries(performance siga)

add_executable(classifica app/classifica.cc)
target_link_libraries(classifica siga)

