cmake_minimum_required(VERSION 3.28)
project(adventOfCode2024 C)

set(CMAKE_C_STANDARD 11)

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
)
add_executable(tests tests/main.test.c src/arrayList.h
        src/arrayList.c src/helpers.h src/helpers.c
        src/linkedList.c
        src/linkedList.h
)
