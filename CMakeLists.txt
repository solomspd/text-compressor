cmake_minimum_required(VERSION 3.15)
project(bonus)

set(CMAKE_CXX_STANDARD 17)

add_executable(bonus src/main.cpp src/compressed_stream.cpp src/compressed_stream.h src/huff_tree.cpp src/huff_tree.h src/compress.cpp src/compress.h src/decompress.cpp src/decompress.h)