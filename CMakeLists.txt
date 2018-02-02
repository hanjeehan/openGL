cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl ./gllab1/main.cpp ./gllab1/MyGlWindow.cpp gllab1/ColorCube.cpp gllab1/ColorCube.h)

target_link_libraries(opengl GLEW)
target_link_libraries(opengl GL)
target_link_libraries(opengl glfw)