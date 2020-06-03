cmake_minimum_required(VERSION 3.10)
project(p2p_messenger)

set(CMAKE_CXX_STANDARD 14)

add_executable(
	p2p_messenger
	main.cpp
	)

add_library(MessengerBackend ../backend/CMakeLists.txt)

target_link_libraries(p2p_messenger MessengerBackend)
