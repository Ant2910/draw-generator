cmake_minimum_required(VERSION 3.16)
project(draw-generator)

# Setze den C++-Standard auf C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

# Finde und lade Catch2
find_package(Catch2 3 REQUIRED)

# Definiere die Quelldateien für Unit-Tests
set(UNIT_TEST_SOURCES
    src/UrnUnitTests.cpp
    src/urn.cpp
    src/urn.hpp
    src/definitions.tpp
)



# Erstelle ein ausführbares Ziel für die Unit-Tests
add_executable(unit_tests ${UNIT_TEST_SOURCES})
target_link_libraries(unit_tests PRIVATE Catch2::Catch2WithMain)
target_include_directories(unit_tests PRIVATE src)

# Definiere die Quelldateien für Benchmarks
set(BENCHMARK_SOURCES
    src/Benchmark.cpp
    src/Benchmark_Config.hpp
    src/urn.cpp
    src/urn.hpp
    src/definitions.tpp
    src/urn_old.cpp
    src/urn_old.hpp
    src/definitions_old.tpp
)

# Erstelle ein ausführbares Ziel für die Benchmarks
add_executable(benchmarks ${BENCHMARK_SOURCES})
target_link_libraries(benchmarks PRIVATE Catch2::Catch2WithMain)
target_include_directories(benchmarks PRIVATE src)

# Optional: Füge CTest-Integration hinzu, wenn du CTest verwenden möchtest
include(CTest)
if (BUILD_TESTING)
    add_test(NAME UnitTests COMMAND unit_tests)
    add_test(NAME Benchmarks COMMAND benchmarks)
endif()
