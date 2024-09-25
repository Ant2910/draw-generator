//Benchmark.cpp by Anton Hempel, September 06, 2024

#include <catch2/catch_all.hpp> 
#include "urn.hpp"
#include "urn_old.hpp"
#include <algorithm>
#include <random>
#include <vector>
#include <discreture.hpp> //https://github.com/mraggi/discreture (Andere Permutation und Kombinatorik Bib)
#include "Benchmark_Config.hpp"
#include <fstream>


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


    bool decrement_draw(std::vector<uint>& draw, const uint& n, const uint& k)
    {   
        for(uint posCount {k}; posCount > 0; --posCount)
        {
            if(draw[posCount-1] > 0)
            {
                --draw[posCount-1];

                return true;
            }
            else
            {
                draw[posCount-1] = n-1;
            }
        }
        return false;
    }

}



void process_mem_usage(double& vm_usage, double& resident_set)
{
    vm_usage     = 0.0;
    resident_set = 0.0;

    // the two fields we want
    unsigned long vsize;
    long rss;
    
    std::string ignore;
    std::ifstream ifs("/proc/self/stat", std::ios_base::in);
    ifs >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore >> ignore
            >> ignore >> ignore >> vsize >> rss;
    ifs.close();
    

    long page_size_KB = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
    vm_usage = vsize / 1024.0;
    resident_set = rss * page_size_KB;
}
/*
RSS is the Resident Set Size and is used to show how much memory is allocated to that process and is in RAM. 
It does not include memory that is swapped out. It does include memory from shared libraries as long as the pages from those libraries are actually in memory. 
It does include all stack and heap memory.

VSZ is the Virtual Memory Size. It includes all memory that the process can access, 
including memory that is swapped out, memory that is allocated, but not used, and memory that is from shared libraries.

So if process A has a 500K binary and is linked to 2500K of shared libraries, has 200K of stack/heap allocations of which 100K is actually in memory (rest is swapped or unused), 
and it has only actually loaded 1000K of the shared libraries and 400K of its own binary then:
RSS: 400K + 1000K + 100K = 1500K
VSZ: 500K + 2500K + 200K = 3200K
*/




//ORDER IMPORTANT, REPETITION IMPORTANT BEGIN
#ifdef URN_OR_FULL_ITERATION_FORWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_forward_new_UrnOR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_forward_old_UrnOR(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_forward_naive_approach_UrnOR(std::vector<uint> draw, const auto& n, const auto& k)
{   
    do {} while (na::increment_draw(draw,n,k));
}

TEST_CASE("Full forward iteration small UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {3,3};
        meter.measure([&u] { return full_iteration_forward_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {3,3};
        meter.measure([&u] { return full_iteration_forward_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnOR(v,3,3); });
    };
}

TEST_CASE("Full forward iteration mid UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {5,5};
        meter.measure([&u] { return full_iteration_forward_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {5,5};
        meter.measure([&u] { return full_iteration_forward_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnOR(v,5,5); });
    };
}

TEST_CASE("Full forward iteration big UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {7,7};
        meter.measure([&u] { return full_iteration_forward_old_UrnOR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {7,7};
        meter.measure([&u] { return full_iteration_forward_new_UrnOR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnOR(v,7,7); });
    };
}
#endif //URN_OR_FULL_ITERATION_FORWARD_ENABLED







#ifdef URN_OR_FULL_ITERATION_BACKWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_backward_new_UrnOR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;}
}

void full_iteration_backward_naive_approach_UrnOR(std::vector<uint> draw, const auto& n, const auto& k)
{   
    do {} while (na::decrement_draw(draw,n,k));
}

TEST_CASE("Full backward iteration small UrnOR")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {3,3};
        meter.measure([&u] { return full_iteration_backward_new_UrnOR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,2);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnOR(v,3,3); });
    };
}

TEST_CASE("Full backward iteration mid UrnOR")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {5,5};
        meter.measure([&u] { return full_iteration_backward_new_UrnOR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,4);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnOR(v,5,5); });
    };
}

TEST_CASE("Full backward iteration big UrnOR")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {7,7};
        meter.measure([&u] { return full_iteration_backward_new_UrnOR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,6);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnOR(v,7,7); });
    };
}
#endif //URN_OR_FULL_ITERATION_BACKWARD_ENABLED







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
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,26);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {   
        urn::UrnOR u {3,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,26);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,26);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnOR(v,3,3,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw mid UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnOR(v,5,5,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw big UrnOR")
{
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnOR u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,823542);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnOR u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,823542);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnOR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,823542);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnOR(v,7,7,randomDraw); 
        });
    };
}
#endif //URN_OR_SPECIFIC_DRAW_ENABLED
//ORDER IMPORTANT, REPETITION IMPORTANT END







#ifdef URN_OR_OLD_PREGENERATED_ENABLED
TEST_CASE("Pregenerated old UrnOR")
{   
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);
    BENCHMARK_ADVANCED("urn_old::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        
        meter.measure([&gen, &distr] 
        {   
            urn_old::UrnOR u {5,5};
            int randomDraw = distr(gen);
            std::vector<std::vector<uint>> draws {};
            
            do {
                std::vector<uint> draw {};
                for(int i {}; i < u.k(); ++i)
                {
                    draw.push_back(u[i]);
                }
                draws.push_back(draw);

            } while (u.next());

            draws.at(randomDraw);
        });
        
    };
    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;
    WARN("Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?");
}
#endif //URN_OR_OLD_PREGENERATED_ENABLED


#ifdef URN_OR_NEW_PREGENERATED_ENABLED
TEST_CASE("Pregenerated new UrnOR")
{   
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        
        meter.measure([&gen, &distr] 
        {   
            urn::UrnOR u {5,5};
            int randomDraw = distr(gen);
            std::vector<std::vector<uint>> draws {};
            
            for(auto it {u.begin()}; it != u.end(); ++it)
            {
                draws.push_back(*it);
            }

            draws.at(randomDraw);
        });
        
    };
    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;
    WARN("Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?");
}
#endif //URN_OR_NEW_PREGENERATED_ENABLED


#ifdef URN_OR_NAIVE_APPROACH_PREGENERATED_ENABLED
TEST_CASE("Pregenerated naive_approach UrnOR")
{   
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);
    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,3124);

        
        meter.measure([&gen, &distr] 
        {   
            std::vector<uint> v (5,0);
            int randomDraw = distr(gen);
            std::vector<std::vector<uint>> draws {};
            
            do {
                std::vector<uint> draw {};
                for(int i {}; i < v.size(); ++i)
                {
                    draw.push_back(v.at(i));
                }
                draws.push_back(draw);

            } while (na::increment_draw(v,5,5));

            draws.at(randomDraw);
        });
        
    };
    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;
    WARN("Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?");
}
#endif //URN_OR_NAIVE_APPROACH_PREGENERATED_ENABLED














//ORDER IMPORTANT, NO REPETITION BEGIN
#ifdef URN_O_FULL_ITERATION_FORWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_forward_new_UrnO(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_forward_old_UrnO(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_forward_next_permutation(std::vector<uint> draw)
{   
    auto begin {draw.begin()};
    auto end {draw.end()};

    do {} while (std::next_permutation(begin, end));
}

void full_iteration_forward_discreture_permutations(const int& n)
{
    for (const auto& perm : discreture::permutations(n));
}

TEST_CASE("Full forward iteration small UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {3,3};
        meter.measure([&u] { return full_iteration_forward_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return full_iteration_forward_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        meter.measure([&v] { return full_iteration_forward_next_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_forward_discreture_permutations(3); });
    };
}

TEST_CASE("Full forward iteration mid UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {5,5};
        meter.measure([&u] { return full_iteration_forward_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {5,5};
        meter.measure([&u] { return full_iteration_forward_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4};
        meter.measure([&v] { return full_iteration_forward_next_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_forward_discreture_permutations(5); });
    };
}

TEST_CASE("Full forward iteration big UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {7,7};
        meter.measure([&u] { return full_iteration_forward_old_UrnO(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {7,7};
        meter.measure([&u] { return full_iteration_forward_new_UrnO(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("std::next_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4,5,6};
        meter.measure([&v] { return full_iteration_forward_next_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_forward_discreture_permutations(7); });
    };
}
#endif //URN_O_FULL_ITERATION_FORWARD_ENABLED







#ifdef URN_O_FULL_ITERATION_BACKWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_backward_new_UrnO(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;}
}

void full_iteration_backward_prev_permutation(std::vector<uint> draw)
{   
    auto begin {draw.begin()};
    auto end {draw.end()};

    do {} while (std::prev_permutation(begin, end));
}

void full_iteration_backward_discreture_permutations(const int& n)
{   
    for (const auto& perm : reversed(discreture::permutations(n)));
}

TEST_CASE("Full backward iteration small UrnO")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        meter.measure([&u] { return full_iteration_backward_new_UrnO(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("std::prev_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {2,1,0};
        meter.measure([&v] { return full_iteration_backward_prev_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_permutations(3); });
    };
}

TEST_CASE("Full backward iteration mid UrnO")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {5,5};
        meter.measure([&u] { return full_iteration_backward_new_UrnO(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("std::prev_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {4,3,2,1,0};
        meter.measure([&v] { return full_iteration_backward_prev_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_permutations(5); });
    };
}

TEST_CASE("Full backward iteration big UrnO")
{
    BENCHMARK_ADVANCED("urn::UrnOR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {7,7};
        meter.measure([&u] { return full_iteration_backward_new_UrnO(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("std::prev_permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {6,5,4,3,2,1,0};
        meter.measure([&v] { return full_iteration_backward_prev_permutation(v); });
    };

    //Kann nur Permutationen mit gleichen n und k
    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_permutations(7); });
    };
}
#endif //URN_O_FULL_ITERATION_BACKWARD_ENABLED







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

void specific_draw_next_permutation(std::vector<uint> draw, const uint& specificDraw)
{   
    auto begin {draw.begin()};
    auto end {draw.end()};

    for(int upCount {}; upCount < specificDraw; ++upCount)
    {
        std::next_permutation(begin, end);
    }
}

void specific_draw_discreture_permutations(const int& n, const uint& specificDraw)
{   
    uint upCount {};

    for (const auto& perm : discreture::permutations(n))
    {
        if(upCount == specificDraw)
        {
            break;
        }
        ++upCount;
    }
}

TEST_CASE("Specific draw small UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {3,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {3,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("std::next:permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_next_permutation(v,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_permutations(3,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw mid UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,119);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,119);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("std::next:permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,119);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_next_permutation(v,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,119);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_permutations(5,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw big UrnO")
{
    BENCHMARK_ADVANCED("urn_old::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnO u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5039);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnO")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnO u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5039);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnO(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("std::next:permutation")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4,5,6};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5039);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_next_permutation(v,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::permutations")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5039);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_permutations(7,randomDraw); 
        });
    };
}
#endif //URN_O_SPECIFIC_DRAW_ENABLED
//ORDER IMPORTANT, NO REPETITION END







//ORDER NOT IMPORTANT, REPETITION IMPORTANT BEGIN
#ifdef URN_R_FULL_ITERATION_FORWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_forward_new_UrnR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;};
}

void full_iteration_forward_old_UrnR(auto urn)
{   
    do {} while (urn.next());
}

void full_iteration_forward_naive_approach_UrnR(auto draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k)); //Wird das weg optimiert durch den Compiler?

    } while (na::increment_draw(draw,n,k));
}

TEST_CASE("Full forward iteration small UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {3,3};
        meter.measure([&u] { return full_iteration_forward_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {3,3};
        meter.measure([&u] { return full_iteration_forward_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnR(v,3,3); });
    };
}

TEST_CASE("Full forward iteration mid UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {5,5};
        meter.measure([&u] { return full_iteration_forward_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {5,5};
        meter.measure([&u] { return full_iteration_forward_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnR(v,5,5); });
    };
}

TEST_CASE("Full forward iteration big UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {6,6};
        meter.measure([&u] { return full_iteration_forward_old_UrnR(u); });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {6,6};
        meter.measure([&u] { return full_iteration_forward_new_UrnR(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (6,0);
        meter.measure([&v] { return full_iteration_forward_naive_approach_UrnR(v,6,6); });
    };
}
#endif //URN_R_FULL_ITERATION_FORWARD_ENABLED







#ifdef URN_R_FULL_ITERATION_BACKWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_backward_new_UrnR(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;}
}

void full_iteration_backward_naive_approach_UrnR(std::vector<uint> draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k));

    } while (na::decrement_draw(draw,n,k));
}

TEST_CASE("Full backward iteration small UrnR")
{
    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {3,3};
        meter.measure([&u] { return full_iteration_backward_new_UrnR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,2);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnR(v,3,3); });
    };
}

TEST_CASE("Full backward iteration mid UrnR")
{
    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {5,5};
        meter.measure([&u] { return full_iteration_backward_new_UrnR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,4);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnR(v,5,5); });
    };
}

TEST_CASE("Full backward iteration big UrnR")
{
    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {6,6};
        meter.measure([&u] { return full_iteration_backward_new_UrnR(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (6,6);
        meter.measure([&v] { return full_iteration_backward_naive_approach_UrnR(v,7,7); });
    };
}
#endif //URN_R_FULL_ITERATION_BACKWARD_ENABLED







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
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,9);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {   
        urn::UrnR u {3,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,9);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (3,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,9);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnR(v,3,3,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw mid UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {5,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (5,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnR(v,5,5,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw big UrnR")
{
    BENCHMARK_ADVANCED("urn_old::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::UrnR u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,1715);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::UrnR")(Catch::Benchmark::Chronometer meter) 
    {
        urn::UrnR u {7,7};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,1715);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_UrnR(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (7,0);
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,1715);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_UrnR(v,7,7,randomDraw); 
        });
    };
}
#endif //URN_R_SPECIFIC_DRAW_ENABLED
//ORDER NOT IMPORTANT, REPETITION IMPORTANT END







//ORDER NOT IMPORTANT, NO REPETITION BEGIN
#ifdef URN_FULL_ITERATION_FORWARD_ENABLED
//TEST_FUNCTIONS
void full_forward_iteration_new_Urn(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;}
}

void full_forward_iteration_old_Urn(auto urn)
{   
    do {} while (urn.next());
}

void full_forward_iteration_naive_approach_Urn(auto draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k) && !na::repetitions(draw,k));
       
    } while (na::increment_draw(draw,n,k));
}

void full_forward_iteration_discreture_combinations(const auto& n, const auto& k)
{   
    for(const auto& comb : discreture::combinations(4,2));
}

TEST_CASE("Full forward iteration small Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {4,2};
        meter.measure([&u] { return full_forward_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {4,2};
        meter.measure([&u] { return full_forward_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (4,0);
        meter.measure([&v] { return full_forward_iteration_naive_approach_Urn(v,4,2); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_forward_iteration_discreture_combinations(4,2); });
    };
}

TEST_CASE("Full forward iteration mid Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {8,3};
        meter.measure([&u] { return full_forward_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {8,3};
        meter.measure([&u] { return full_forward_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (8,0);
        meter.measure([&v] { return full_forward_iteration_naive_approach_Urn(v,8,3); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_forward_iteration_discreture_combinations(8,3); });
    };
}

TEST_CASE("Full forward iteration big Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {9,5};
        meter.measure([&u] { return full_forward_iteration_old_Urn(u); });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {9,5};
        meter.measure([&u] { return full_forward_iteration_new_Urn(u.begin(), u.end()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v (9,0);
        meter.measure([&v] { return full_forward_iteration_naive_approach_Urn(v,9,5); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_forward_iteration_discreture_combinations(9,5); });
    };
}
#endif //URN_FULL_ITERATION_FORWARD_ENABLED







#ifdef URN_FULL_ITERATION_BACKWARD_ENABLED
//TEST_FUNCTIONS
void full_iteration_backward_new_Urn(const auto& begin, const auto& end)
{
    for(auto it {begin}; it != end; ++it){*it;}
}

void full_iteration_backward_naive_approach_Urn(std::vector<uint> draw, const auto& n, const auto& k)
{   
    do {

        if(!na::unsorted(draw,k) && !na::repetitions(draw,k));

    } while (na::decrement_draw(draw,n,k));
}

void full_iteration_backward_discreture_combinations(const auto& n, const auto& k)
{   
    for(const auto& comb : reversed(discreture::combinations(n,k)));
}

TEST_CASE("Full backward iteration small Urn")
{
    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {4,2};
        meter.measure([&u] { return full_iteration_backward_new_Urn(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {2,3};
        meter.measure([&v] { return full_iteration_backward_naive_approach_Urn(v,4,2); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_combinations(4,2); });
    };
}

TEST_CASE("Full backward iteration mid Urn")
{
    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {8,3};
        meter.measure([&u] { return full_iteration_backward_new_Urn(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {5,6,7};
        meter.measure([&v] { return full_iteration_backward_naive_approach_Urn(v,8,3); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_combinations(8,3); });
    };
}

TEST_CASE("Full backward iteration big Urn")
{
    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {9,5};
        meter.measure([&u] { return full_iteration_backward_new_Urn(u.rbegin(), u.rend()); });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {4,5,6,7,8};
        meter.measure([&v] { return full_iteration_backward_naive_approach_Urn(v,9,5); });
    };

    BENCHMARK_ADVANCED("discreture::combinations")(Catch::Benchmark::Chronometer meter) 
    {
        meter.measure([] { return full_iteration_backward_discreture_combinations(9,5); });
    };
}
#endif //URN_FULL_ITERATION_BACKWARD_ENABLED







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
    uint upCount {};

    while(upCount != specificDraw)
    {   
        na::increment_draw(draw,n,k);

        if(!na::unsorted(draw,k) && !na::repetitions(draw,k))
        {
            ++upCount;
        }
    }
}

void specific_draw_discreture_combinations(const uint& n, const uint& k, const uint& specificDraw)
{   
    //Die Reihnfolge der Draws ist anders 
    uint upCount {};

    for (const auto& comb : discreture::combinations(4,2))
    {
        if(upCount == specificDraw)
        {   
            break;
        }
        ++upCount;
    }
}

TEST_CASE("Specific draw small Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {4,2};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {   
        urn::Urn u {4,2};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_Urn(v,4,2,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::combinations !ANDERE DRAW REIHENFOLGE!")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,5);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_combinations(4,2,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw mid Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {8,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,55);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {8,3};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,55);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,55);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_Urn(v,8,3,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::combinations !ANDERE DRAW REIHENFOLGE!")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,55);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_combinations(8,3,randomDraw); 
        });
    };
}

TEST_CASE("Specific draw big Urn")
{
    BENCHMARK_ADVANCED("urn_old::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn_old::Urn u {9,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_old_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("urn::Urn")(Catch::Benchmark::Chronometer meter) 
    {
        urn::Urn u {9,5};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&u, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_new_Urn(u,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("na::naive_approach")(Catch::Benchmark::Chronometer meter) 
    {
        std::vector<uint> v {0,1,2,3,4};
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&v, &gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_naive_approach_Urn(v,9,5,randomDraw); 
        });
    };

    BENCHMARK_ADVANCED("discreture::combinations !ANDERE DRAW REIHENFOLGE!")(Catch::Benchmark::Chronometer meter) 
    {
        // Zufallszahlengenerator und Verteilung initialisieren
        std::random_device rd;  
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<> distr(0,125);

        meter.measure([&gen, &distr] 
        {   
            // Zufällige Zahl erzeugen
            int randomDraw = distr(gen);

            return specific_draw_discreture_combinations(9,5,randomDraw); 
        });
    };
}
#endif //URN_SPECIFIC_DRAW_ENABLED
//ORDER NOT IMPORTANT, NO REPETITION END









int main()
{   
    /*
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);

    // Zufallszahlengenerator und Verteilung initialisieren
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0,3124);

    
    std::vector<uint> v (5,0);
    int randomDraw = distr(gen);
    std::vector<std::vector<uint>> draws {};
    
    do {
        std::vector<uint> draw {};
        for(int i {}; i < v.size(); ++i)
        {
            draw.push_back(v.at(i));
        }
        draws.push_back(draw);

    } while (na::increment_draw(v,5,5));

    for(auto i: draws.at(randomDraw))
    {
        std::cout << i;
    }
    std::cout << std::endl;

    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;

    std::cout << "Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?" << std::endl;
    
    //BENCHMARK
    //1004 VM
    //3700 - 3800 RSS
    
    //MAIN
    //176 VM
    //1500-1700 RSS
    


    //Gibt auf meinem PC 176 ?KB?
    //In der Benchmark 1004  ?KB?


    
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);

    // Zufallszahlengenerator und Verteilung initialisieren
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0,3124);

    

    urn_old::UrnOR u {5,5};
    int randomDraw = distr(gen);
    std::vector<std::vector<uint>> draws {};
    
    do {
        std::vector<uint> draw {};
        for(int i {}; i < u.k(); ++i)
        {
            draw.push_back(u[i]);
        }
        draws.push_back(draw);

    } while (u.next());

    for(auto i: draws.at(randomDraw))
    {
        std::cout << i;
    }
    std::cout << std::endl;

    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;

    std::cout << "Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?" << std::endl;
    
    //MAIN
    //176 VM
    //1500-1700 RSS

    //BENCHMARK
    //1004 VM
    //3700 RSS
    */
    
    double vmBefore {}, rssBefore {};
    process_mem_usage(vmBefore, rssBefore);

    // Zufallszahlengenerator und Verteilung initialisieren
    std::random_device rd;  
    std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(0,3124);

        

    urn::UrnOR u {5,5};
    int randomDraw = distr(gen);
    std::vector<std::vector<uint>> draws {};
    
    for(auto it {u.begin()}; it != u.end(); ++it)
    {
        draws.push_back(*it);
    }

    for(auto i: draws.at(randomDraw))
    {
        std::cout << i;
    }
    std::cout << std::endl;

    double vmAfter {}, rssAfter {};
    process_mem_usage(vmAfter, rssAfter);
    double vmDiff = vmAfter - vmBefore;
    double rssDiff = rssAfter - rssBefore;

    std::cout << "Speicherverbrauch VM: " << vmDiff << " ?KB?" << "\n" << "Speicherverbrauch RSS: " << rssDiff << " ?KB?" << std::endl;
    
    //MAIN
    //176 VM
    //1700-1800 RSS

    //BENCHMARK
    //912 VM
    //3300 - 3500 RSS

}
