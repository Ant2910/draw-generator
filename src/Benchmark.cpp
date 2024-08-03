#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "urn.hpp"
#include <algorithm>


void test_UrnO(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it);
}

void test_next_permutation(const auto& begin, const auto& end)
{   
    do {} while (next_permutation(begin, end));
}


TEST_CASE("Algorithm")
{
    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        meter.measure([&v] { return test_next_permutation(v.begin(), v.end()); });
    };
}


TEST_CASE("Urn")
{
    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return test_UrnO(u.begin(), u.end()); });
    };
}