cmake_minimum_required (VERSION 3.0)
project(DZ1)

add_subdirectory(io)

message("IO_LIB_INCLUDE_DIRS = ${IO_LIB_INCLUDE_DIRS}")
message("IO_LIB_LIBRARIES = ${IO_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} src/source.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov -g -Wall -Werror -fsanitize=address")
set(CMAKE_CXX_COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

target_include_directories(${PROJECT_NAME} PUBLIC ${IO_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${IO_LIB_LIBRARIES})

add_subdirectory(Google_tests)

# # Test target
# add_executable(
#     test
#     test/test.cpp
# )

# # Add test to the include directories from the test lib
# target_include_directories(
#     test PRIVATE
#     "${CMAKE_CURRENT_SOURCE_DIR}/src"
# )


# target_include_libraries(
#     test PRIVATE
#     gtest gtest_main
# )

# # Setup log levels
# if (MSVS) {
#     set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

#     target_compile_options(
#         DZ1 PRIVATE
#         /W4
#     )

#     target_compile_options(
#         test PRIVATE
#         /W4
#     )
# }
# else () {
#     target_compile_options(
#         DZ1 PRIVATE
#         -Wall -Wextra -pedantic -Werror
#     )

#     target_compile_options(
#         test PRIVATE
#         -Wall -Wextra -pedantic -Werror
#     )
# }
# endif()