cmake_minimum_required(VERSION 4.3)
set(CMAKE_POLICY_DEFAULT_CMP0000 NEW)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(mandelbrot_generator)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

set(RAYLIB_VERSION 6.0)

FetchContent_Declare(
    raylib 
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)

FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/windowelement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mandelbrotgenerator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mandelbrot.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/filedialog.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/lodepng.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/lodepng.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/include/portable-file-dialogs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/res/icon.h"
    )

add_executable(${PROJECT_NAME} 
WIN32
${SOURCE_FILES}
mb.rc
)

target_include_directories(${PROJECT_NAME} PRIVATE 
"${CMAKE_CURRENT_SOURCE_DIR}/src"
"${CMAKE_CURRENT_SOURCE_DIR}/include"
"${CMAKE_CURRENT_SOURCE_DIR}/res")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
)