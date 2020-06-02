cmake_minimum_required(VERSION 3.10)
project(MessengerUI)

find_package(Threads REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++17 -Wall -Wextra -Werror=pedantic")
add_executable(main frontend/main.cpp)

include_directories(frontend)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

target_link_libraries(main ${CURSES_LIBRARIES})

SET(CURSES_USE_NCURSES TRUE)
