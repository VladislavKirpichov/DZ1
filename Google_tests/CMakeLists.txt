cmake_minimum_required(VERSION 3.0)
project(Google_tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" )

file(GLOB SOURCES *.cpp)

find_package(GTest REQUIRED)

file(GLOB TEST_FILES "^test$.txt")
file(GLOB ANSWER_FILES "^answer$.txt")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TEST_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/tests)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/answers/${ANSWER_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/answers)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${IO_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${IO_LIB_LIBRARIES} ${LCOV_LINK_FLAGS} GTest::gtest_main)
# Стресс тесты под санитайзерами