cmake_minimum_required(VERSION 3.10.2)
project(p2p_messenger)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lncurses")
set(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

set(CURSES_USE_NCURSES TRUE)


find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Boost)
find_package(Boost REQUIRED COMPONENTS system)

find_package(Curses REQUIRED)

include_directories(backend/include %{Boost_INCLUDE_DIRS} ${CURSES_INCLUDE_DIR})

add_executable(p2p_messenger
    backend/include/Chat.h
    backend/include/Client.h
    backend/include/IReceivable.h
    backend/include/ISendable.h
    backend/include/Message.h
    backend/include/Peer.h
    backend/include/Server.h
    backend/include/Storage.h
    backend/include/User.h
    backend/src/Chat.cpp
    backend/src/Client.cpp
    backend/src/Message.cpp
    backend/src/Peer.cpp
    backend/src/Server.cpp
    backend/src/Storage.cpp
    backend/src/User.cpp

    frontend/lang/en.h
    frontend/App.cpp
    frontend/App.h
    frontend/constants.h
    frontend/frontend.cpp
    frontend/frontend.h
    frontend/ncurscript.cpp
    frontend/ncurscript.h
    frontend/utilities.cpp
    frontend/utilities.h

    main.cpp
)

target_link_libraries(p2p_messenger ${CURSES_LIBRARIES} ${Boost_LIBRARIES} Boost::system ${PQXX_LIB} ${PQ_LIB})
