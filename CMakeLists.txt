cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "San")

set(CMAKE_C_STANDARD 99)
set(BUILD_SHARED_LIBS OFF)

project(gel C)

find_package(SDL2 REQUIRED)
link_directories(${SDL2_LIBRARY_DIRS})

set(gel_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/include)
set(gel_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

file(GLOB_RECURSE gel_SRCS ${gel_SRCS} ${gel_INC_DIR}/gel/*.h)
file(GLOB_RECURSE gel_HDRS ${gel_HDRS} ${gel_SRC_DIR}/*.c)
set(gel_HDR ${gel_INC_DIR}/gel.h)

add_library(gel ${gel_SRCS} ${gel_HDRS} ${gel_HDR})
target_include_directories(gel PUBLIC ${gel_INC_DIR})
target_link_libraries(gel PUBLIC ${SDL2_LIBRARY})
target_compile_options(gel PUBLIC -Wall -Werror -Wextra -ansi)

set_target_properties(gel PROPERTIES OUTPUT_NAME "gel")
set_target_properties(gel PROPERTIES OUTPUT_NAME_DEBUG "gel.dev")
set_target_properties(gel PROPERTIES OUTPUT_NAME_SAN "gel.san")
set_target_properties(gel PROPERTIES RUNTIME_OUTPUT_DIRECTORY
	${CMAKE_CURRENT_LIST_DIR})

if (APPLE)
	include_directories("/System/Library/Frameworks")
	find_library(COCOA_LIBRARIES Cocoa)
	find_library(IOKIT_LIBRARIES IOkit)
	find_library(COREVIDEO_LIBRARIES CoreVideo)
	target_link_libraries(gel PUBLIC
		"-framework AppKit" "-framework OpenGL"
		"-framework IOKit" "-framework CoreVideo")
endif ()

set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g3")
if (CMAKE_C_FLAGS_RELEASE MATCHES "-O3")
	string(REPLACE "-O3" "-O2" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
endif ()
if (CMAKE_BUILD_TYPE MATCHES San)
	set_target_properties(gel PROPERTIES COMPILE_FLAGS "-fsanitize=address")
	set_target_properties(gel PROPERTIES LINK_FLAGS "-fsanitize=address")
endif ()

install(FILES ${gel_HDRS} DESTINATION include/gel)
install(FILES ${gel_HDR} DESTINATION include)
