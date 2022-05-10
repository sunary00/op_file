cmake_minimum_required(VERSION 3.8)

project(op_file CXX)

add_executable(r_file rw_file.cc read_main.cc)
add_executable(w_file rw_file.cc write_main.cc)