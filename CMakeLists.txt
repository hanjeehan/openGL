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

configure_file(
        gouraud.vert
        gouraud.vert
        COPYONLY
)

configure_file(
        gouraud.frag
        gouraud.frag
        COPYONLY
)

configure_file(
        gouraudpot.vert
        gouraudpot.vert
        COPYONLY
)

configure_file(
        gouraudpot.frag
        gouraudpot.frag
        COPYONLY
)

add_library(opengl SHARED
        ./gllab1/MyGlWindow.cpp
        ./gllab1/ColorCube.cpp
        ./gllab1/Viewer.cpp
        ./gllab1/Board.cpp
        ./gllab1/Sphere.cpp
        ./gllab1/vboteapot.cpp
        )

add_executable(app
        ./gllab1/main.cpp
        )

target_link_libraries(opengl GLEW)
target_link_libraries(opengl GL)
target_link_libraries(opengl glfw)

target_link_libraries(app opengl)