cmake_minimum_required(VERSION 3.0.0)
project(CS014_Lab1 VERSION 1.0.0)

include(CTest)
enable_testing()

add_executable(playlist 
    src/main.cpp 
    src/playlist.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

