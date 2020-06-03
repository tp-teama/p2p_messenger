cmake_minimum_required(VERSION 3.10.2)
project(MessengerBackend)

set(CMAKE_CXX_STANDARD 14)

SET(CMAKE_CXX_FLAGS -pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")

set(PQXX /usr/local/include/pqxx)

find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

find_package(Boost)
find_package(Boost REQUIRED COMPONENTS system)

include_directories(include %{Boost_INCLUDE_DIRS})

add_executable(MessengerBackend
  ../backend/include/Chat.h
  ../backend/include/Client.h
  ../backend/include/IReceivable.h
  ../backend/include/ISendable.h
  ../backend/include/Message.h
  ../backend/include/Peer.h
  ../backend/include/Server.h
  ../backend/include/Storage.h
  ../backend/include/User.h
  ../backend/src/Chat.cpp
  ../backend/src/Client.cpp
  ../backend/src/Message.cpp
  ../backend/src/Peer.cpp
  ../backend/src/Server.cpp
  ../backend/src/Storage.cpp
  ../backend/src/User.cpp
  )

target_link_libraries(MessengerBackend ${Boost_LIBRARIES} Boost::system ${PQXX_LIB} ${PQ_LIB})
