cmake_minimum_required(VERSION 2.8.12)

set(SOURCE_FILES src/main.cpp)
set(HEADER_FILES )
set(PROJ_NAME fcFrog)

project(${PROJ_NAME})

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(${PROJ_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJ_NAME} ${CONAN_LIBS})
