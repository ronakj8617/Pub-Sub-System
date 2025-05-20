cmake_minimum_required(VERSION 3.14)
project(PubSubServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow configuration
set(CROW_USE_BOOST ON)
set(CROW_BUILD_EXAMPLES OFF)
set(CROW_ENABLE_COMPRESSION OFF)
set(CROW_USE_SSL OFF)
set(CROW_AMALGAMATE OFF)

# Boost config (only set manually if CMake fails to auto-detect)
# You can comment these if not on macOS/Homebrew
# set(BOOST_ROOT /opt/homebrew/opt/boost)
# set(Boost_INCLUDE_DIR /opt/homebrew/include)
# set(Boost_LIBRARY_DIR /opt/homebrew/lib)

find_package(Boost REQUIRED COMPONENTS system thread)

# Include Crow
add_subdirectory(external/crow)

# Include directories
include_directories(
        external/crow/include
        external/asio
        ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Add your executable
add_executable(pubsub
        src/main.cpp
        src/TopicManager.cpp
        include/cors.h
)

# Link against Boost libraries
target_link_libraries(pubsub PRIVATE ${Boost_LIBRARIES})
