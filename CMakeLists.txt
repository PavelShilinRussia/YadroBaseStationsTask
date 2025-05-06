cmake_minimum_required(VERSION 3.10)
project(ComputerClubManagementSystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(ComputerClubManagementSystem
        src/main.cpp
        src/ClubTime.cpp
        src/Event.cpp
        src/ComputerClub.cpp
)


enable_testing()
add_subdirectory(tests)