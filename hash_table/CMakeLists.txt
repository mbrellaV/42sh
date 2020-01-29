cmake_minimum_required(VERSION 3.15)
project(hash_table C)

set(CMAKE_C_STANDARD 99)

add_executable(hash_table main.c main.h hash_table.c hash_table_2.c ft.c)

set_target_properties(hash_table PROPERTIES LINK_FLAGS "-lreadline")