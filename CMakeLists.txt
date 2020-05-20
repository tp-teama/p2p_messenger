cmake_minimum_required(VERSION 3.15)
project(p2p_messenger)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost)

include_directories(include ${Boost_INCLUDE_DIRS})

add_executable(p2p_messenger
        include/CentralServer.h
        include/Chat.h
        include/Client.h
        include/IRecievable.h
        include/ISendable.h
        include/Message.h
        include/Peer.h
        include/Server.h
        include/Storage.h
        include/StorageChat.h
        include/StorageMessage.h
        include/StorageUser.h
        include/User.h
        src/CentralServer.cpp
        src/Chat.cpp
        src/Client.cpp
        src/Message.cpp
        src/Peer.cpp
        src/Server.cpp
        src/Storage.cpp
        src/StorageChat.cpp
        src/StorageMessage.cpp
        src/StorageUser.cpp
        src/User.cpp
        main.cpp)

target_link_libraries(p2p_messenger ${Boost_LIBRARIES})