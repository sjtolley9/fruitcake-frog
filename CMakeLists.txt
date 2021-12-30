cmake_minimum_required(VERSION 3.7)

set(SOURCE_FILES src/main.cpp)
set(HEADER_FILES )
set(PROJ_NAME fcFrog)

project(${PROJ_NAME})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJ_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(${PROJ_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
