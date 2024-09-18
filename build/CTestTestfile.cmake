# CMake generated Testfile for 
# Source directory: /home/anton/draw-generator
# Build directory: /home/anton/draw-generator/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTests "/home/anton/draw-generator/build/unit_tests")
set_tests_properties(UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/anton/draw-generator/CMakeLists.txt;49;add_test;/home/anton/draw-generator/CMakeLists.txt;0;")
add_test(Benchmarks "/home/anton/draw-generator/build/benchmarks")
set_tests_properties(Benchmarks PROPERTIES  _BACKTRACE_TRIPLES "/home/anton/draw-generator/CMakeLists.txt;50;add_test;/home/anton/draw-generator/CMakeLists.txt;0;")
