cmake_minimum_required(VERSION 3.4)
project(banking)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Account STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Account.cpp)
add_library(Transaction STATIC ${CMAKE_CURRENT_SOURCE_DIR}/Transaction.cpp)

target_link_libraries(Transaction Account)

target_include_directories(Account PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Transaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
