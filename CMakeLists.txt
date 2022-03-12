cmake_minimum_required (VERSION 3.0)
project(DZ1)
set(CMAKE_C_COMPILER "gcc")

# # Build googletest
# add_subdirectory(
#     "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
#     "googletest"
# )

# Main target
add_executable(DZ1 src/source.c src/skyscraperio.c)

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