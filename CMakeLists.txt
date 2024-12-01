cmake_minimum_required(VERSION 3.28)
project(adventOfCode2024 C)

set(CMAKE_C_STANDARD 11)

add_executable(adventOfCode2024 main.c
        day1.c
        day1.h
        helpers.c
        helpers.h)
