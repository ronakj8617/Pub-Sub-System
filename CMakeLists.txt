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

# Enable testing
include(CTest)
enable_testing()

# ======================================
# Fetch GoogleTest (GTest + GMock)
# ======================================
include(FetchContent)
FetchContent_Declare(
        GTest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0  # Use latest stable tag
)
FetchContent_MakeAvailable(GTest)

# Add GTest test directory
add_subdirectory(tests/gtests)
################################
# Catch2                       #
################################
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.5.2 # or latest stable tag
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)

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
