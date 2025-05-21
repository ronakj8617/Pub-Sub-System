# tests/CMakeLists.txt
find_package(Catch2 REQUIRED)

add_executable(tests
        test_main.cpp
        test_topic_manager.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

include(Catch)
catch_discover_tests(tests)
