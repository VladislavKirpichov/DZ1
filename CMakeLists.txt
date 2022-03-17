cmake_minimum_required (VERSION 3.0)
project(DZ1)

set(LCOV_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
set(LCOV_LINK_FLAGS "-lgcov")

add_subdirectory(io)

message("IO_LIB_INCLUDE_DIRS = ${IO_LIB_INCLUDE_DIRS}")
message("IO_LIB_LIBRARIES = ${IO_LIB_LIBRARIES}")

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")

add_executable(${PROJECT_NAME} src/source.c)

if (sanitaizer_test)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${DCMAKE_CXX_COMPILER} -fsanitize=address -coverage -lgcov -g -Wall -Werror")
    set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${DCMAKE_CC_COMPILER} -fsanitize=address")

elseif (test)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LCOV_COMPILE_FLAGS} -coverage -lgcov -g -Wall -Werror")
    set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${LCOV_LINK_FLAGS}")

else () 
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} ${DCMAKE_CC_COMPILER}")

endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ${IO_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IO_LIB_LIBRARIES})

if (sanitaizer_test OR test)
    add_subdirectory(Google_tests)
endif ()