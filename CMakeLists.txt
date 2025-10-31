cmake_minimum_required (VERSION 3.8)

project ("BarkBrowser")

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED True)
set (CMAKE_CXX_EXTENSIONS False)

add_subdirectory ("src")
add_subdirectory ("test")
