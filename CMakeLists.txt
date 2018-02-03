cmake_minimum_required(VERSION 3.9)
project(opengl)

set(CMAKE_CXX_STANDARD 17)

configure_file(
        simple.vert
        simple.vert
        COPYONLY
)

configure_file(
        simple.frag
        simple.frag
        COPYONLY
)

add_executable(opengl
        ./gllab1/main.cpp
        ./gllab1/MyGlWindow.cpp
        ./gllab1/ColorCube.cpp
        ./gllab1/Viewer.cpp
        ./gllab1/Board.cpp
        )

target_link_libraries(opengl GLEW)
target_link_libraries(opengl GL)
target_link_libraries(opengl glfw)