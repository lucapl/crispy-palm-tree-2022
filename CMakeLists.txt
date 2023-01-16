cmake_minimum_required(VERSION 2.8)

include_directories(./include)

set(CMAKE_CXX_STANDARD 14)

project("co_project")

file(GLOB co_SRC
     "./src/*.hpp"
     "./src/*.cpp"
)

add_executable(co_proj ${co_SRC})
