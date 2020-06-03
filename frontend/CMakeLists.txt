cmake_minimum_required(VERSION 3.10)
project(MessengerUI)


include(${CMAKE_CURRENT_SOURCE_DIR}/../backend/CMakeLists.txt)

# add_subdirectory(MessengerBackend ../backend/)
# add_library(MessengerBackend ../backend/CMakeLists.txt)


SET(CURSES_USE_NCURSES TRUE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -static -Wextra -Werror=pedantic -lncurses")
find_package(Curses REQUIRED)

# include_directories(frontend)
# include_directories(test/frontend)

include_directories(${CURSES_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 14)
add_executable(MessengerUI
	# frontend.h
	# App.h
	# test/constants.cpp
	# utilities.cpp
	# App.cpp
	# ncurscript.cpp
	# frontend.cpp
	main.cpp
	)

target_link_libraries(MessengerUI ${CURSES_LIBRARIES})
