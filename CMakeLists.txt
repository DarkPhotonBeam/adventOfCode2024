cmake_minimum_required(VERSION 3.18)
project(adventOfCode2024 C)

set(CMAKE_C_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/inputs/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/inputs/)

add_executable(adventOfCode2024 src/main.c
        src/days/day1.c
        src/days/day1.h
        src/helpers.c
        src/helpers.h
        src/arrayList.h
        src/arrayList.c
        src/linkedList.c
        src/linkedList.h
        src/days/day2.c
        src/days/day2.h
        src/days/day3.c
        src/days/day3.h
        src/text.c
        src/text.h
        src/graph.c
        src/graph.h
        src/days/day4.c src/days/day4.h
        src/days/day5.c
        src/days/day5.h
        src/days/day6.c src/days/day6.h)
