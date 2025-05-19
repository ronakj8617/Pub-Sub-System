cmake_minimum_required(VERSION 3.14)
project(PubSubServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CROW_USE_BOOST ON)
set(CROW_BUILD_EXAMPLES OFF)
set(CROW_ENABLE_COMPRESSION OFF)
set(CROW_USE_SSL OFF)
set(CROW_AMALGAMATE OFF)

# Boost paths - adjust if you use Homebrew Boost
set(BOOST_ROOT /opt/homebrew/opt/boost)
set(Boost_INCLUDE_DIR /opt/homebrew/include)
set(Boost_LIBRARY_DIR /opt/homebrew/lib)

find_package(Boost REQUIRED COMPONENTS system thread)

add_subdirectory(external/crow)

add_executable(pubsub src/main.cpp src/TopicManager.cpp
        include/cors.h)

target_include_directories(pubsub PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/external/crow/include
        include
        ${Boost_INCLUDE_DIR}
)

target_link_libraries(pubsub PRIVATE ${Boost_LIBRARIES})
