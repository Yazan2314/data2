cmake_minimum_required(VERSION 3.30)
project(DS_wet2_winter_2024_2025)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(DS_wet2_winter_2024_2025
    main.cpp
    plains25a2.cpp
    plains25a2.h
    wet2util.h
        UnionFind.cpp
        UnionFind.h
        AvlTree.h
        hashTable.h
        jockey.cpp
        jockey.h
        team.cpp
        team.h)
