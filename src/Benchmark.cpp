//Benchmark.cpp by Anton Hempel, August 08, 2024

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <catch2/catch.hpp>
#include "urn.hpp"
#include "urn_old.hpp"
#include <algorithm>
#include "Benchmark_Config.hpp"


//namespace naive approach
namespace na
{   
    //Filtert die Draws für UrnR/Urn aus UrnOR heraus
    bool unsorted(const std::vector<uint>& draw, const uint& k)
    {
        for (uint posCount {}; posCount < k - 1; ++posCount)
        {
            if (draw[posCount] > draw[posCount + 1])
            {
                return true;
            }
        }
        return false;
    }

    bool repetitions(const std::vector<uint>& draw, const uint& k)
    {
        for (uint i {}; i < k - 1; ++i)
        {
            for (uint j { i + 1 }; j < k; ++j)
            {
                if (draw[i] == draw[j])
                {
                    return true;
                }
            }
        }
        return false;
    }

    //Gibt alle Draws wie UrnOR aus 
    bool increment_draw(std::vector<uint>& draw, const uint& n, const uint& k)
    {   
        for(uint posCount {k}; posCount > 0; --posCount)
        {
            if(draw[posCount-1] < n-1)
            {
                ++draw[posCount-1];

                return true;
            }
            else
            {
                draw[posCount-1] = 0;
            }
    }
    return false;
    }
}



//ORDER IMPORTANT, NO REPETITION BEGIN
#ifdef URN_O_FULL_ITERATION_ENABLED
//TEST_FUNCTIONS
void full_iteration_new_UrnO(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_old_UrnO(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_next_permutation(const auto& begin, const auto& end)
{   
    do {} while (std::next_permutation(begin, end));
}

TEST_CASE("Full iteration small UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {3,3};
        meter.measure([&u] { return full_iteration_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return full_iteration_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        meter.measure([&v] { return full_iteration_next_permutation(v.begin(), v.end()); });
    };
}

TEST_CASE("Full iteration mid UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {5,5};
        meter.measure([&u] { return full_iteration_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {5,5};
        meter.measure([&u] { return full_iteration_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4};
        meter.measure([&v] { return full_iteration_next_permutation(v.begin(), v.end()); });
    };
}

TEST_CASE("Full iteration big UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {7,7};
        meter.measure([&u] { return full_iteration_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {7,7};
        meter.measure([&u] { return full_iteration_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4,5,6};
        meter.measure([&v] { return full_iteration_next_permutation(v.begin(), v.end()); });
    };
}
#endif //URN_O_FULL_ITERATION







#ifdef URN_O_SPECIFIC_DRAW_ENABLED
//TEST_FUNCTIONS
void specific_draw_new_UrnO(auto urn, const uint& specificDraw)
{
    urn.draw(specificDraw);
}

void specific_draw_old_UrnO(auto urn, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::ignore = urn.next();
        //https://en.cppreference.com/w/cpp/utility/tuple/ignore könnte es verlangsamen?
    }
}

void specific_draw_next_permutation(const auto& begin, const auto& end, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::next_permutation(begin, end);
    }
}

TEST_CASE("Specific draw small UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {3,3};
        meter.measure([&u] { return specific_draw_old_UrnO(u,5); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return specific_draw_new_UrnO(u,5); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        meter.measure([&v] { return specific_draw_next_permutation(v.begin(), v.end(),5); });
    };
}

TEST_CASE("Specific draw mid UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {5,5};
        meter.measure([&u] { return specific_draw_old_UrnO(u,119); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {5,5};
        meter.measure([&u] { return specific_draw_new_UrnO(u,119); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4};
        meter.measure([&v] { return specific_draw_next_permutation(v.begin(), v.end(), 119); });
    };
}

TEST_CASE("Specific draw big UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {7,7};
        meter.measure([&u] { return specific_draw_old_UrnO(u,5039); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {7,7};
        meter.measure([&u] { return specific_draw_new_UrnO(u,5039); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4,5,6};
        meter.measure([&v] { return specific_draw_next_permutation(v.begin(), v.end(), 5039); });
    };
}
#endif //URN_O_SPECIFIC_DRAW
//ORDER IMPORTANT, NO REPETITION END







//ORDER IMPORTANT, REPETITION IMPORTANT BEGIN
#ifdef URN_OR_FULL_ITERATION_ENABLED
//TEST_FUNCTIONS
void full_iteration_new_UrnOR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_old_UrnOR(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_naive_approach_UrnOR(std::vector<uint> draw, const auto& n, const auto& k)
{   
    do {} while (na::increment_draw(draw,n,k));
}

TEST_CASE("Full iteration small UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {3,3};
        meter.measure([&u] { return full_iteration_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {3,3};
        meter.measure([&u] { return full_iteration_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return full_iteration_naive_approach_UrnOR(v,3,3); });
    };
}

TEST_CASE("Full iteration mid UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {5,5};
        meter.measure([&u] { return full_iteration_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {5,5};
        meter.measure([&u] { return full_iteration_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return full_iteration_naive_approach_UrnOR(v,5,5); });
    };
}

TEST_CASE("Full iteration big UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {7,7};
        meter.measure([&u] { return full_iteration_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {7,7};
        meter.measure([&u] { return full_iteration_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        meter.measure([&v] { return full_iteration_naive_approach_UrnOR(v,7,7); });
    };
}
#endif //URN_OR_FULL_ITERATION







#ifdef URN_OR_SPECIFIC_DRAW_ENABLED
//TEST_FUNCTIONS
void specific_draw_new_UrnOR(auto urn, const uint& specificDraw)
{
    urn.draw(specificDraw);
}

void specific_draw_old_UrnOR(auto urn, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::ignore = urn.next();
        //https://en.cppreference.com/w/cpp/utility/tuple/ignore könnte es verlangsamen?
    }
}

void specific_draw_naive_approach_UrnOR(auto draw, const uint& n, const uint& k, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {   
        na::increment_draw(draw,n,k);
    }
}

TEST_CASE("Specific draw small UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {3,3};
        meter.measure([&u] { return specific_draw_old_UrnOR(u,26); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {3,3};
        meter.measure([&u] { return specific_draw_new_UrnOR(u,26); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnOR(v,3,3,26); });
    };
}

TEST_CASE("Specific draw mid UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {5,5};
        meter.measure([&u] { return specific_draw_old_UrnOR(u,3124); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {5,5};
        meter.measure([&u] { return specific_draw_new_UrnOR(u,3124); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnOR(v,5,5,3124); });
    };
}

TEST_CASE("Specific draw big UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {7,7};
        meter.measure([&u] { return specific_draw_old_UrnOR(u,823542); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {7,7};
        meter.measure([&u] { return specific_draw_new_UrnOR(u,823542); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnOR(v,7,7,823542); });
    };
}
#endif //URN_OR_SPECIFIC_DRAW_ENABLED
//ORDER IMPORTANT, REPETITION IMPORTANT END







//ORDER NOT IMPORTANT, REPETITION IMPORTANT BEGIN
#ifdef URN_R_FULL_ITERATION_ENABLED
//TEST_FUNCTIONS
void full_iteration_new_UrnR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_old_UrnR(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_naive_approach_UrnR(auto draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k)); //Wird das weg optimiert durch den Compiler?

    } while (na::increment_draw(draw,n,k));
}

TEST_CASE("Full iteration small UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {3,3};
        meter.measure([&u] { return full_iteration_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {3,3};
        meter.measure([&u] { return full_iteration_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return full_iteration_naive_approach_UrnR(v,3,3); });
    };
}

TEST_CASE("Full iteration mid UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {5,5};
        meter.measure([&u] { return full_iteration_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {5,5};
        meter.measure([&u] { return full_iteration_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return full_iteration_naive_approach_UrnR(v,5,5); });
    };
}

TEST_CASE("Full iteration big UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {6,6};
        meter.measure([&u] { return full_iteration_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {6,6};
        meter.measure([&u] { return full_iteration_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (6,6);
        meter.measure([&v] { return full_iteration_naive_approach_UrnR(v,7,7); });
    };
}
#endif //URN_R_FULL_ITERATION







#ifdef URN_R_SPECIFIC_DRAW_ENABLED
//TEST_FUNCTIONS
void specific_draw_new_UrnR(auto urn, const uint& specificDraw)
{   
    urn.draw(specificDraw);
}

void specific_draw_old_UrnR(auto urn, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::ignore = urn.next();
        //https://en.cppreference.com/w/cpp/utility/tuple/ignore könnte es verlangsamen?
    }
}

void specific_draw_naive_approach_UrnR(auto draw, const uint& n, const uint& k, const uint& specificDraw)
{   
    uint upCount {};

    while(upCount != specificDraw)
    {   
        na::increment_draw(draw,n,k);

        if(!na::unsorted(draw,k))
        {
            ++upCount;
        }
    }
}

TEST_CASE("Specific draw small UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {3,3};
        meter.measure([&u] { return specific_draw_old_UrnR(u,9); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {3,3};
        meter.measure([&u] { return specific_draw_new_UrnR(u,9); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnR(v,3,3,9); });
    };
}

TEST_CASE("Specific draw mid UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {5,5};
        meter.measure([&u] { return specific_draw_old_UrnR(u,125); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {5,5};
        meter.measure([&u] { return specific_draw_new_UrnR(u,125); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnR(v,5,5,125); });
    };
}

TEST_CASE("Specific draw big UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {7,7};
        meter.measure([&u] { return specific_draw_old_UrnR(u,1715); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {7,7};
        meter.measure([&u] { return specific_draw_new_UrnR(u,1715); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        meter.measure([&v] { return specific_draw_naive_approach_UrnR(v,7,7,1715); });
    };
}
#endif //URN_R_SPECIFIC_DRAW_ENABLED
//ORDER NOT IMPORTANT, REPETITION IMPORTANT END








//ORDER NOT IMPORTANT, NO REPETITION BEGIN
#ifdef URN_FULL_ITERATION_ENABLED
//TEST_FUNCTIONS
void full_iteration_new_Urn(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_old_Urn(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_naive_approach_Urn(auto draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k) && !na::repetitions(draw,k)); //Wird das weg optimiert durch den Compiler?
       
    } while (na::increment_draw(draw,n,k));
}

TEST_CASE("Full iteration small Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {4,2};
        meter.measure([&u] { return full_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {4,2};
        meter.measure([&u] { return full_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (4,0);
        meter.measure([&v] { return full_iteration_naive_approach_Urn(v,4,2); });
    };
}

TEST_CASE("Full iteration mid Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {8,3};
        meter.measure([&u] { return full_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {8,3};
        meter.measure([&u] { return full_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (8,0);
        meter.measure([&v] { return full_iteration_naive_approach_Urn(v,8,3); });
    };
}

TEST_CASE("Full iteration big Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {9,5};
        meter.measure([&u] { return full_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {9,5};
        meter.measure([&u] { return full_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (9,0);
        meter.measure([&v] { return full_iteration_naive_approach_Urn(v,9,5); });
    };
}
#endif //URN_FULL_ITERATION







#ifdef URN_SPECIFIC_DRAW_ENABLED
//TEST_FUNCTIONS
void specific_draw_new_Urn(auto urn, const uint& specificDraw)
{   
    urn.draw(specificDraw);
}

void specific_draw_old_Urn(auto urn, const uint& specificDraw)
{   
    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::ignore = urn.next();
        //https://en.cppreference.com/w/cpp/utility/tuple/ignore könnte es verlangsamen?
    }
}

void specific_draw_naive_approach_Urn(auto draw, const uint& n, const uint& k, const uint& specificDraw)
{   
    int upCount {-1}; //weil bei 0 wäre es 000
                      //muss bei UrnR nicht beachtet werden, weil da reps erlaubt
    while(upCount != specificDraw)
    {   
        na::increment_draw(draw,n,k);

        if(!na::unsorted(draw,k) && !na::repetitions(draw,k))
        {
            ++upCount;
        }
    }
}

TEST_CASE("Specific draw small Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {4,2};
        meter.measure([&u] { return specific_draw_old_Urn(u,5); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {4,2};
        meter.measure([&u] { return specific_draw_new_Urn(u,5); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (4,0);
        meter.measure([&v] { return specific_draw_naive_approach_Urn(v,4,2,5); });
    };
}

TEST_CASE("Specific draw mid Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {8,3};
        meter.measure([&u] { return specific_draw_old_Urn(u,55); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {8,3};
        meter.measure([&u] { return specific_draw_new_Urn(u,55); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (8,0);
        meter.measure([&v] { return specific_draw_naive_approach_Urn(v,8,3,55); });
    };
}

TEST_CASE("Specific draw big Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {9,5};
        meter.measure([&u] { return specific_draw_old_Urn(u,125); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {9,5};
        meter.measure([&u] { return specific_draw_new_Urn(u,125); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (9,0);
        meter.measure([&v] { return specific_draw_naive_approach_Urn(v,9,5,125); });
    };
}
#endif //URN_SPECIFIC_DRAW_ENABLED




/*
void full_iteration_new_UrnR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it)
    {   
        for(auto i: *it)
            std::cout << i;
        std::cout << std::endl;
    };
}

void full_iteration_old_UrnR(auto urn)
{   
    do {
        for(int i{}; i < urn.k(); ++i)
            std::cout << urn[i];
        std::cout << std::endl;
    } while (urn.next());
}


int main()
{   
    
    urn::Urn u {9,5};
    
    full_iteration_old_UrnR(u);
    full_iteration_new_UrnR(u.begin(),u.end());

    return 0;
}
*/