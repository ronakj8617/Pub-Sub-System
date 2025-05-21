cmake_minimum_required(VERSION 3.14)
project(PubSubServer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Crow configuration (if you use any Crow-specific defines)
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

# ======================================
# Fetch Catch2
# ======================================
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2  # Use latest stable tag
)
FetchContent_MakeAvailable(Catch2)

add_subdirectory(tests)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system thread)


add_executable(pubsub
        src/main.cpp
        src/TopicManager.cpp
        include/cors.h
)

# Now specify include directories for the target
target_include_directories(pubsub PRIVATE
        external/crow/include
        external/asio
        ${Boost_INCLUDE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against Boost libraries
target_link_libraries(pubsub PRIVATE ${Boost_LIBRARIES})

# Doxygen Documentation setup
find_package(Doxygen QUIET)

if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

    add_custom_target(doc_doxygen
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM
    )
else()
    message(STATUS "Doxygen not found, 'doc_doxygen' target will not be available")
endif()
