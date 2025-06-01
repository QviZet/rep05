cmake_minimum_required(VERSION 3.4)
project(Tests)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_link_options(--coverage)
add_compile_options(--coverage)

add_subdirectory(banking)
add_subdirectory(testing)
add_subdirectory(googletest)
