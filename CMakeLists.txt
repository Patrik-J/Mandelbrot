cmake_minimum_required(VERSION 4.3)
project(mandelbrot_generator)
set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

set(RAYLIB_VERSION 6.0)
set(OPENCV_VERSION 4.13.0)

FetchContent_Declare(
    raylib 
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
)

find_package(OpenCV REQUIRED)

FetchContent_MakeAvailable(raylib)

set(SOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/window.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/windowelement.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mandelbrotgenerator.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/mandelbrot.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/portable-file-dialogs.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/filedialog.cpp"
    )

add_executable(${PROJECT_NAME} 
${SOURCE_FILES}
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        raylib
        ${OpenCV_LIBS}
        # opencv_core
        # opencv_imgproc
        # opencv_imgcodecs
)