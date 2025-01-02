cmake_minimum_required(VERSION 3.31)

project(sanic)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/*.h")
add_executable(sanic ${SOURCES} ${INCLUDES})

include_directories(${CMAKE_SOURCE_DIR}/include)
if (APPLE)
    target_link_libraries(sanic ${CMAKE_SOURCE_DIR}/lib/libraylib.a)
endif()
if (WIN32)
    target_link_libraries(sanic raylib)
endif()

if (APPLE)
    target_link_libraries(sanic "-framework IOKit")
    target_link_libraries(sanic "-framework Cocoa")
    target_link_libraries(sanic "-framework OpenGL")
endif()
