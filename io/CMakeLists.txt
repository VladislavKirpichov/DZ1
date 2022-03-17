cmake_minimum_required(VERSION 3.0)
project(io)

if (sanitaizer_test OR test)
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fprofile-arcs -ftest-coverage -fPIC -O0")

else () 
    set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-fPIC -O0")  

endif ()

file(GLOB SOURCES *.c)
file(GLOB INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

add_library(${PROJECT_NAME} ${SOURCES})

set(IO_LIB_LIBRARIES ${PROJECT_NAME} PARENT_SCOPE)
set(IO_LIB_INCLUDE_DIRS ${INCLUDE_DIRS} PARENT_SCOPE)