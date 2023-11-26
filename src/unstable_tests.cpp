// unstable_tests.cpp by Anton Hempel, November 26, 2023

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "restructured.cpp"
#include <string>
#include <concepts>

template<class T>
concept RandomAccessRange = std::ranges::random_access_range<T>;

//Funktion Iterator Test
//Funktioniert aber vielleicht zu vector Rückgabe umbauen?
string iterateRange(auto IteratorBegin, auto IteratorEnd)
{   
    auto ite {IteratorEnd};
    string draws {};
    for(auto itb {IteratorBegin}; itb != ite; ++itb)
    {   
        draws += to_string(*itb);
    }
    return draws;
}




TEST_CASE("UrnOR")
{
    SECTION("1")
    {
        UrnOR u {0,0};
        REQUIRE(u.n() == 0);
        REQUIRE(u.k() == 0);
        REQUIRE(u.z() == 0);
    }

    SECTION("2")
    {
        UrnOR u {2,3};
        REQUIRE(u.n() == 2);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 8);
    }

    SECTION("3")
    {
        UrnOR u {3,3};
        REQUIRE(to_string(u.firstDraw()) == "0 0 0");
        REQUIRE(to_string(u.lastDraw()) == "2 2 2");
        REQUIRE(to_string(u.nextDraw({0,0,0})) == "0 0 1");
        REQUIRE(to_string(u.nextDraw({1,1,2})) == "1 2 0");
        REQUIRE(to_string(u.backDraw({0,0,1})) == "0 0 0");
        REQUIRE(to_string(u.backDraw({1,1,2})) == "1 1 1");
        REQUIRE(to_string(u.draw(1)) == "0 0 1");
    }   

    SECTION("4")
    {   
        UrnOR u {3,3};
        REQUIRE_THROWS_AS((UrnOR { 0,1 }),std::domain_error);
        REQUIRE_THROWS_WITH((UrnOR { 0,1 }),"UrnOR with n == 0 and k > 0 is not valid.");

        REQUIRE_THROWS_AS((u.nextDraw({2,2,2})),std::overflow_error);
        REQUIRE_THROWS_WITH((u.nextDraw({2,2,2})),"There is no valid next draw.");

        REQUIRE_THROWS_AS((u.backDraw({0,0,0})),std::underflow_error);
        REQUIRE_THROWS_WITH((u.backDraw({0,0,0})),"There is no valid back draw.");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        UrnOR u {2,2};
        REQUIRE(RandomAccessRange<UrnOR>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "0 00 11 01 1");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "1 11 00 10 0");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};
        
        REQUIRE((itBegin == itEnd) == false);
        REQUIRE((itBegin != itEnd) == true);
        REQUIRE((itBegin < itEnd) == true);
        REQUIRE((itBegin > itEnd) == false);
        REQUIRE((itBegin >= itEnd) == false);
        REQUIRE((itBegin <= itEnd) == true);

        auto itRbegin {u.rbegin()};
        auto itRend {u.rend()};

        REQUIRE((itRbegin == itRend) == false);
        REQUIRE((itRbegin != itRend) == true);
        REQUIRE((itRbegin < itRend) == true);
        REQUIRE((itRbegin > itRend) == false);
        REQUIRE((itRbegin >= itRend) == false);
        REQUIRE((itRbegin <= itRend) == true);

        REQUIRE(u.end()-u.begin() == 4);
        REQUIRE(u.rend()-u.rbegin() == 4);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "0 1");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "1 0");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "0 1");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "0 0");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "1 0");
        it -= 1;
        REQUIRE(to_string(*it) == "0 1");

        //Weitere Randfälle?
    }
    
    
    
}