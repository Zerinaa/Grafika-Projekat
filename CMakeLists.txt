cmake_minimum_required(VERSION 3.10)
project(zavrsni_projekat C)

set(CMAKE_C_STANDARD 99)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(zavrsni_projekat main.c)
target_link_libraries("zavrsni_projekat" ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})