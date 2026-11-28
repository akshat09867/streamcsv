cmake_minimum_required(VERSION 3.20)
project(streamcsv VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)

add_library(streamcsv_core
    src/mapped_file.cpp
    src/csv_parser.cpp
)

target_include_directories(streamcsv_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(streamcsv_core PRIVATE
    -Wall -Wextra -Wpedantic
)

if(ENABLE_SANITIZERS)
    target_compile_options(streamcsv_core PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(streamcsv_core PUBLIC -fsanitize=address,undefined)
endif()

add_executable(streamcsv
    src/main.cpp
)

target_link_libraries(streamcsv PRIVATE streamcsv_core)
target_compile_options(streamcsv PRIVATE -Wall -Wextra -Wpedantic)
