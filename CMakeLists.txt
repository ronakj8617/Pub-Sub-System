cmake_minimum_required(VERSION 3.10)
project(PubSubSystem)

set(CMAKE_CXX_STANDARD 17)

#find_package(Curses REQUIRED)
#include_directories(${CURSES_INCLUDE_DIR})

add_executable(SystemMonitor
        src/main.cpp
        src/TopicManager.cpp
        include/TopicManager.h
)

#target_link_libraries(SystemMonitor ${CURSES_LIBRARIES})

# Link with ncurses
#target_link_libraries(SystemMonitor ${CURSES_LIBRARIES})