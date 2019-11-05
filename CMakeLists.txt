cmake_minimum_required(VERSION 3.15)
project(bonus)

set(CMAKE_CXX_STANDARD 17)

add_executable(bonus main.cpp compressed_stream.cpp compressed_stream.h huff_tree.cpp huff_tree.h compress.cpp compress.h decompress.cpp decompress.h)