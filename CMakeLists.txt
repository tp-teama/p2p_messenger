cmake_minimum_required(VERSION 3.10.2)
project(p2p_messenger)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Boost)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(include %{Boost_INCLUDE_DIRS})

add_executable(p2p_messenger
        include/Chat.h
        include/Client.h
        include/IReceivable.h
        include/ISendable.h
        include/Message.h
        include/Peer.h
        include/Server.h
        include/Storage.h
        include/User.h
        src/Chat.cpp
        src/Client.cpp
        src/Message.cpp
        src/Peer.cpp
        src/Server.cpp
        src/Storage.cpp
        src/User.cpp
        CMakeLists.txt
        main.cpp)

target_link_libraries(p2p_messenger ${Boost_LIBRARIES} Boost::system ${PQXX_LIB} ${PQ_LIB})