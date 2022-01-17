cmake_minimum_required(VERSION 2.8.12)

set(SOURCE_FILES src/main.cpp src/LTexture.cpp src/Renderer.cpp)
set(HEADER_FILES headers/Renderer.hpp)
set(PROJ_NAME fcFrog)

project(${PROJ_NAME})

add_definitions("-std=c++11")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


add_executable(${PROJ_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${PROJ_NAME} ${CONAN_LIBS})
target_include_directories(${PROJ_NAME} PRIVATE headers)

if(MSVC)
	# target_compile_options(${PROJ_NAME} PRIVATE /W4 /WX)
else()
	target_compile_options(${PROJ_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/higo.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/higo.png
)

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/path.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/path.png
)

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/path2.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/path2.png
)

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/profile.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/profile.png
)

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/splash_logo.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/splash_logo.png
)

add_custom_command(
		TARGET ${PROJ_NAME}
	POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
				${CMAKE_CURRENT_SOURCE_DIR}/assets/splash_logo_small.png
				${CMAKE_CURRENT_BINARY_DIR}/bin/assets/splash_logo_small.png
)
