# CMake generated Testfile for 
# Source directory: /Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-src
# Build directory: /Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(crow_test "/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-build/tests/unittest")
set_tests_properties(crow_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-src/CMakeLists.txt;70;add_test;/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-src/CMakeLists.txt;0;")
add_test(template_test "/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-build/tests/template/test.py")
set_tests_properties(template_test PROPERTIES  WORKING_DIRECTORY "/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-build/tests/template" _BACKTRACE_TRIPLES "/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-src/CMakeLists.txt;71;add_test;/Users/ronak/Programming/CLion Projects/Pub-Sub-System/_deps/crow-src/CMakeLists.txt;0;")
subdirs("examples")
subdirs("tests")
