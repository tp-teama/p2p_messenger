cmake_minimum_required(VERSION 3.15)
project(central_server)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS -pthread)

find_package(Boost)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(include %{Boost_INCLUDE_DIRS})

add_executable(central_server
        include/CentralServer.h
        src/CentralServer.cpp
        main.cpp)

target_link_libraries(central_server ${Boost_LIBRARIES} Boost::system)