cmake_minimum_required(VERSION 3.31)

project(sanic)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
  endif()
endif()

set(CMAKE_C_STANDARD 17)

file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB INCLUDES "${CMAKE_SOURCE_DIR}/include/*.h")
add_executable(sanic ${SOURCES} ${INCLUDES})

include_directories(${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} raylib)

if (APPLE)
    target_link_libraries(sanic "-framework IOKit")
    target_link_libraries(sanic "-framework Cocoa")
    target_link_libraries(sanic "-framework OpenGL")
endif()
