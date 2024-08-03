#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include "urn.hpp"
#include "urn_old.hpp"
#include <algorithm>


//new Urn Bib

void test_new_UrnO(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it);
}

//old Urn Bib

void test_old_UrnO(auto u)
{   
    do {} while (u.next());
}

//Algorithms Bib

void test_next_permutation(const auto& begin, const auto& end)
{   
    do {} while (std::next_permutation(begin, end));
}


//Benchmark 

TEST_CASE("Algorithm")
{
    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        meter.measure([&v] { return test_next_permutation(v.begin(), v.end()); });
    };
}


TEST_CASE("New Urn")
{
    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return test_new_UrnO(u.begin(), u.end()); });
    };
}

TEST_CASE("Old Urn")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {3,3};
        meter.measure([&u] { return test_old_UrnO(u); });
    };
}