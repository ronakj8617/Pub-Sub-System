# Add test executable
add_executable(
        gtests
        gtest_main.cpp
        gtest_topic_manager.cpp
        ${CMAKE_SOURCE_DIR}/src/TopicManager.cpp

)

# Link GoogleTest (fetched via FetchContent)
target_link_libraries(gtests PRIVATE GTest::gtest GTest::gtest_main)

# Add include dirs for test target
target_include_directories(gtests PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(gtests)

add_test(NAME gtests COMMAND gtests --gtest_output=xml:${CMAKE_BINARY_DIR}/gtest_report.xml)
