cmake_minimum_required(VERSION 3.28)
project(POO_team_project)

set(CMAKE_CXX_STANDARD 17)

find_package(SEAL CONFIG REQUIRED)

add_executable(POO_team_project
        VotingSystem.cpp
        main.cpp
        VotingSystem.h
)

target_link_libraries(POO_team_project PRIVATE SEAL::seal)