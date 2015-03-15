cmake_minimum_required(VERSION 2.6)
project(2D)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
find_package(GLUT REQUIRED)
find_package(OpenGL REQUIRED)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}")
find_package(slg REQUIRED)
set(CMAKE_CXX_FLAGS "-g -Wall")
include_directories(${PROJECT_SOURCE_DIR}/../slg)
include_directories("${slg_INCLUDE_DIRS}")
#add_subdirectory(${PROJECT_SOURCE_DIR}/../slg)
add_executable(2D main.cpp)
set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m ${slg_LIBRARIES})
target_link_libraries(2D ${CORELIBS})

#the one C file
#add_executable(cdemo cdemo.c)
#target_link_libraries(cdemo m lo) #link the math library

#these are all compiled the same way
#set(PROGRAMS oglfirst pointers)
#set(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)

#foreach(program ${PROGRAMS})
#  add_executable(${program} ${program}.cpp)
#  target_link_libraries(${program} ${CORELIBS})
#endforeach(program)

#building just a library. 
#add_library(geometry geometry.cpp)

#add_executable(test_geometry test_geometry.cpp)
#linking against a custom library
#target_link_libraries(test_geometry ${CORELIBS} geometry)

