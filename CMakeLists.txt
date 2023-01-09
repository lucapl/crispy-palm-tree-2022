cmake_minimum_required(VERSION 2.8)

file(GLOB co_SRC
     "./src/*.hpp"
     "./src/*.cpp"
)

add_executable(co_proj ${co_SRC})
