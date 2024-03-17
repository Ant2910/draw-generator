//unstable_tests.cpp by Anton Hempel, November 26, 2023

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

//Test ADT für GenericUrn
namespace per
{
    class Person
    {
        public:
            Person(string name, uint age): m_name {name}, m_age{age}{}

            string getName()
            {
                return m_name;
            }

            uint getAge()
            {
                return m_age;
            }

            //Muss für die GenericUrn spezifiziert werden bei ADTs
            bool operator==(const Person& other) const
            {
                return (m_name == other.m_name && m_age == other.m_age);
            }

        private:
            string m_name {};
            uint m_age {};  
    };

    //Output funktion für ADT. sollte für alle ADTs die mit der GenericUrn benutzt werden, definiert werden
    //ähnlich wie to_string
    string outputPerson(vector <Person> draw)
    {   
        string stdraw {};
        for(uint posCount{}; posCount < draw.size(); ++posCount)
        {
            stdraw += (draw.at(posCount).getName()) + "," + to_string((draw.at(posCount).getAge()));
            if(posCount != (draw.size()-1))
            {
                stdraw += " ";
            }
        }
        return stdraw;
    }
    
    //to_string mit outputPerson ausgetauscht
    string iterateRange(auto IteratorBegin, auto IteratorEnd)
    {   
        auto ite {IteratorEnd};
        string draws {};
        for(auto itb {IteratorBegin}; itb != ite; ++itb)
        {   
            draws += outputPerson(*itb);
        }
        return draws;
    }
    
}

//UrnOR

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
        REQUIRE(to_string(u.draw(0)) == "0 0 0");
        REQUIRE(to_string(u.draw(26)) == "2 2 2");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(27),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(27),"There is no valid draw for this ordinalnumber.");

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

        REQUIRE(to_string(itBegin[0]) == "0 0");
        REQUIRE(to_string(itBegin[3]) == "1 1");
        REQUIRE(to_string(itBegin[-1]) == "0 0");
        REQUIRE(to_string(itBegin[4]) == "0 0");
        
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
    }
}

//UrnO

TEST_CASE("UrnO")
{
    SECTION("1")
    {
        UrnO u {0,0};
        REQUIRE(u.n() == 0);
        REQUIRE(u.k() == 0);
        REQUIRE(u.z() == 0);
    }

    SECTION("2")
    {
        UrnO u {3,2};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 2);
        REQUIRE(u.z() == 6);
    }

    SECTION("3")
    {
        UrnO u {3,3};
        REQUIRE(to_string(u.firstDraw()) == "0 1 2");
        REQUIRE(to_string(u.lastDraw()) == "2 1 0");
        REQUIRE(to_string(u.nextDraw({0,1,2})) == "0 2 1");
        REQUIRE(to_string(u.nextDraw({2,0,1})) == "2 1 0");
        REQUIRE(to_string(u.backDraw({2,1,0})) == "2 0 1");
        REQUIRE(to_string(u.backDraw({1,0,2})) == "0 2 1");
        REQUIRE(to_string(u.draw(1)) == "0 2 1");
        REQUIRE(to_string(u.draw(0)) == "0 1 2");
        REQUIRE(to_string(u.draw(5)) == "2 1 0");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(6),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(6),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        UrnO u {3,3};
        //Test for constructor
        REQUIRE_THROWS_AS((UrnO { 2,3 }),std::domain_error);
        REQUIRE_THROWS_WITH((UrnO { 2,4 }),"UrnO with k > n is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({2,1,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({2,1,0})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({0,1,2})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({0,1,2})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for repetitions
        REQUIRE_THROWS_AS((u.nextDraw({0,0,1})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({0,0,1})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({0,1,1})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({0,1,1})),"Either the specified draw is incorrect or there is no next valid draw");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        UrnO u {3,2};
        REQUIRE(RandomAccessRange<UrnO>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "0 10 21 01 22 02 1");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "2 12 01 21 00 20 1");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "0 1");
        REQUIRE(to_string(itBegin[5]) == "2 1");
        REQUIRE(to_string(itBegin[-1]) == "0 0");
        REQUIRE(to_string(itBegin[6]) == "0 0");
        
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

        REQUIRE(u.end()-u.begin() == 6);
        REQUIRE(u.rend()-u.rbegin() == 6);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "0 2");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "1 0");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "0 2");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "0 1");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "1 0");
        it -= 1;
        REQUIRE(to_string(*it) == "0 2");
    }
}


//UrnR
TEST_CASE("UrnR")
{
    SECTION("1")
    {
        UrnR u {3,2};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 2);
        REQUIRE(u.z() == 6);
    }

    SECTION("2")
    {
        UrnR u {3,3};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 10);
    }

    SECTION("3")
    {
        UrnR u {3,3};
        REQUIRE(to_string(u.firstDraw()) == "0 0 0");
        REQUIRE(to_string(u.lastDraw()) == "2 2 2");
        REQUIRE(to_string(u.nextDraw({0,1,2})) == "0 2 2");
        REQUIRE(to_string(u.nextDraw({0,2,2})) == "1 1 1");
        REQUIRE(to_string(u.backDraw({1,1,1})) == "0 2 2");
        REQUIRE(to_string(u.backDraw({0,2,2})) == "0 1 2");
        REQUIRE(to_string(u.draw(1)) == "0 0 1");
        REQUIRE(to_string(u.draw(0)) == "0 0 0");
        REQUIRE(to_string(u.draw(9)) == "2 2 2");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(10),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(10),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        UrnR u {3,3};
        //Test for constructor
        REQUIRE_THROWS_AS((UrnR { 0,3 }),std::domain_error);
        REQUIRE_THROWS_WITH((UrnR { 0,3 }),"UrnR with n = 0 is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({2,2,2})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({2,2,2})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({0,0,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({0,0,0})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for unsorted
        REQUIRE_THROWS_AS((u.nextDraw({2,1,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({2,1,0})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({1,0,1})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({1,0,1})),"Either the specified draw is incorrect or there is no next valid draw");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        UrnR u {3,2};
        REQUIRE(RandomAccessRange<UrnR>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "0 00 10 21 11 22 2");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "2 21 21 10 20 10 0");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "0 0");
        REQUIRE(to_string(itBegin[5]) == "2 2");
        REQUIRE(to_string(itBegin[-1]) == "0 0");
        REQUIRE(to_string(itBegin[6]) == "0 0");
        
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

        REQUIRE(u.end()-u.begin() == 6);
        REQUIRE(u.rend()-u.rbegin() == 6);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "0 1");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "0 2");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "0 1");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "0 0");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "0 2");
        it -= 1;
        REQUIRE(to_string(*it) == "0 1");
    }
}


//Urn
TEST_CASE("Urn")
{
    SECTION("1")
    {
        Urn u {5,3};
        REQUIRE(u.n() == 5);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 10);
    }

    SECTION("2")
    {
        Urn u {3,3};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 1);
    }

    SECTION("3")
    {
        Urn u {4,2};
        REQUIRE(to_string(u.firstDraw()) == "0 1");
        REQUIRE(to_string(u.lastDraw()) == "2 3");
        REQUIRE(to_string(u.nextDraw({0,2})) == "0 3");
        REQUIRE(to_string(u.nextDraw({0,3})) == "1 2");
        REQUIRE(to_string(u.backDraw({1,2})) == "0 3");
        REQUIRE(to_string(u.backDraw({0,3})) == "0 2");
        REQUIRE(to_string(u.draw(1)) == "0 2");
        REQUIRE(to_string(u.draw(0)) == "0 1");
        REQUIRE(to_string(u.draw(5)) == "2 3");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(6),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(6),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        Urn u {3,2};
        //Test for constructor
        REQUIRE_THROWS_AS((Urn { 0,3 }),std::domain_error);
        REQUIRE_THROWS_WITH((Urn { 0,3 }),"UrnOR with n == 0 and k > 0 is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({1,2})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({1,2})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({0,1})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({0,1})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for unsorted
        REQUIRE_THROWS_AS((u.nextDraw({1,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({1,0})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({2,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({2,0})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for repetitions
        REQUIRE_THROWS_AS((u.nextDraw({0,0})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({0,0})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({1,1})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({1,1})),"Either the specified draw is incorrect or there is no next valid draw");
    
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        Urn u {3,2};
        REQUIRE(RandomAccessRange<Urn>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "0 10 21 2");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "1 20 20 1");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "0 1");
        REQUIRE(to_string(itBegin[2]) == "1 2");
        REQUIRE(to_string(itBegin[-1]) == "0 0");
        REQUIRE(to_string(itBegin[3]) == "0 0");
        
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

        REQUIRE(u.end()-u.begin() == 3);
        REQUIRE(u.rend()-u.rbegin() == 3);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "0 2");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "1 2");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "0 2");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "0 1");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "1 2");
        it -= 1;
        REQUIRE(to_string(*it) == "0 2");
    }
}


//GenericUrn

//GenericUrn<TYPE,TRUE,TRUE> = UrnOR
TEST_CASE("GenericUrn<TYPE,TRUE,TRUE>")
{
    SECTION("1")
    {
        GenericUrn<std::string,true,true> u {0,{}};
        REQUIRE(u.n() == 0);
        REQUIRE(u.k() == 0);
        REQUIRE(u.z() == 0);
    }

    SECTION("2")
    {
        GenericUrn<std::string,true,true> u {3,{"Red","Green"}};
        REQUIRE(u.n() == 2);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 8);
    }

    SECTION("3")
    {
        GenericUrn<std::string,true,true> u {3,{"Red","Green","Blue"}};
        REQUIRE(to_string(u.firstDraw()) == "Red Red Red");
        REQUIRE(to_string(u.lastDraw()) == "Blue Blue Blue");
        REQUIRE(to_string(u.nextDraw({"Red","Red","Red"})) == "Red Red Green");
        REQUIRE(to_string(u.nextDraw({"Green","Green","Blue"})) == "Green Blue Red");
        REQUIRE(to_string(u.backDraw({"Red","Red","Green"})) == "Red Red Red");
        REQUIRE(to_string(u.backDraw({"Green","Green","Blue"})) == "Green Green Green");
        REQUIRE(to_string(u.draw(1)) == "Red Red Green");
        REQUIRE(to_string(u.draw(0)) == "Red Red Red");
        REQUIRE(to_string(u.draw(26)) == "Blue Blue Blue");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(27),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(27),"There is no valid draw for this ordinalnumber.");

    }   

    SECTION("4")
    {   
        GenericUrn<std::string,true,true> u {3,{"Red","Green","Blue"}};
        REQUIRE_THROWS_AS((GenericUrn<std::string,true,true> { 1,{} }),std::domain_error);
        REQUIRE_THROWS_WITH((GenericUrn<std::string,true,true> { 1,{} }),"UrnOR with n == 0 and k > 0 is not valid.");

        REQUIRE_THROWS_AS((u.nextDraw({"Blue","Blue","Blue"})),std::overflow_error);
        REQUIRE_THROWS_WITH((u.nextDraw({"Blue","Blue","Blue"})),"There is no valid next draw.");

        REQUIRE_THROWS_AS((u.backDraw({"Red","Red","Red"})),std::underflow_error);
        REQUIRE_THROWS_WITH((u.backDraw({"Red","Red","Red"})),"There is no valid back draw.");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        GenericUrn<std::string,true,true> u {2,{"Red","Green"}};
        REQUIRE(RandomAccessRange<GenericUrn<std::string,true,true>>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "Red RedRed GreenGreen RedGreen Green");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "Green GreenGreen RedRed GreenRed Red");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "Red Red");
        REQUIRE(to_string(itBegin[3]) == "Green Green");
        REQUIRE_THROWS_AS((itBegin[-1]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[-1]),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS((itBegin[4]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[4]),"There is no valid draw for this ordinalnumber.");
        
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
        REQUIRE(to_string(*itBegin) == "Red Green");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "Green Red");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "Red Green");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "Red Red");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "Green Red");
        it -= 1;
        REQUIRE(to_string(*it) == "Red Green");
    }
}

//GenericUrn<TYPE,TRUE,FALSE> = UrnO

TEST_CASE("GenericUrn<TYPE,TRUE,FALSE>")
{
    SECTION("1")
    {
        GenericUrn<char,true,false> u {0,{}};
        REQUIRE(u.n() == 0);
        REQUIRE(u.k() == 0);
        REQUIRE(u.z() == 0);
    }

    SECTION("2")
    {
        GenericUrn<char,true,false> u {2,{'A','B','C'}};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 2);
        REQUIRE(u.z() == 6);
    }

    SECTION("3")
    {
        GenericUrn<char,true,false> u {3,{'A','B','C'}};
        REQUIRE(to_string(u.firstDraw()) == "A B C");
        REQUIRE(to_string(u.lastDraw()) == "C B A");
        REQUIRE(to_string(u.nextDraw({'A','B','C'})) == "A C B");
        REQUIRE(to_string(u.nextDraw({'C','A','B'})) == "C B A");
        REQUIRE(to_string(u.backDraw({'C','B','A'})) == "C A B");
        REQUIRE(to_string(u.backDraw({'B','A','C'})) == "A C B");
        REQUIRE(to_string(u.draw(1)) == "A C B");
        REQUIRE(to_string(u.draw(0)) == "A B C");
        REQUIRE(to_string(u.draw(5)) == "C B A");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(6),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(6),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        GenericUrn<char,true,false> u {3,{'A','B','C'}};
        //Test for constructor
        REQUIRE_THROWS_AS((GenericUrn<char,true,false> { 4,{'A','B','C'} }),std::domain_error);
        REQUIRE_THROWS_WITH((GenericUrn<char,true,false> { 4,{'A','B','C'} }),"UrnO with k > n is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({'C','B','A'})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({'C','B','A'})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({'A','B','C'})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({'A','B','C'})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for repetitions
        REQUIRE_THROWS_AS((u.nextDraw({'A','A','B'})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({'A','A','B'})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({'A','B','B'})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({'A','B','B'})),"Either the specified draw is incorrect or there is no next valid draw");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        GenericUrn<char,true,false> u {2, {'A','B','C'}};
        REQUIRE(RandomAccessRange<GenericUrn<char,true,false>>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "A BA CB AB CC AC B");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "C BC AB CB AA CA B");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "A B");
        REQUIRE(to_string(itBegin[5]) == "C B");
        REQUIRE_THROWS_AS((itBegin[-1]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[-1]),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS((itBegin[6]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[6]),"There is no valid draw for this ordinalnumber.");
        
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

        REQUIRE(u.end()-u.begin() == 6);
        REQUIRE(u.rend()-u.rbegin() == 6);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "A C");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "B A");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "A C");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "A B");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "B A");
        it -= 1;
        REQUIRE(to_string(*it) == "A C");
    }
}

//GenericUrn<TYPE,FALSE,TRUE> = UrnR
TEST_CASE("GenericUrn<TYPE,FALSE,TRUE>")
{
    SECTION("1")
    {
        GenericUrn<double,false,true> u {2,{3.14,2.71,9.81}};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 2);
        REQUIRE(u.z() == 6);
    }

    SECTION("2")
    {
        GenericUrn<double,false,true> u {3,{3.14,2.71,9.81}};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 10);
    }

    SECTION("3")
    {
        GenericUrn<double,false,true> u {3,{3.14,2.71,9.81}};
        REQUIRE(to_string(u.firstDraw()) == "3.140000 3.140000 3.140000");
        REQUIRE(to_string(u.lastDraw()) == "9.810000 9.810000 9.810000");
        REQUIRE(to_string(u.nextDraw({3.14,2.71,9.81})) == "3.140000 9.810000 9.810000");
        REQUIRE(to_string(u.nextDraw({3.14,9.81,9.81})) == "2.710000 2.710000 2.710000");
        REQUIRE(to_string(u.backDraw({2.71,2.71,2.71})) == "3.140000 9.810000 9.810000");
        REQUIRE(to_string(u.backDraw({3.14,9.81,9.81})) == "3.140000 2.710000 9.810000");
        REQUIRE(to_string(u.draw(1)) == "3.140000 3.140000 2.710000");
        REQUIRE(to_string(u.draw(0)) == "3.140000 3.140000 3.140000");
        REQUIRE(to_string(u.draw(9)) == "9.810000 9.810000 9.810000");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(10),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(10),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        GenericUrn<double,false,true> u {3,{3.14,2.71,9.81}};
        //Test for constructor
        REQUIRE_THROWS_AS((GenericUrn<double,false,true> { 3,{} }),std::domain_error);
        REQUIRE_THROWS_WITH((GenericUrn<double,false,true> { 3,{} }),"UrnR with n = 0 is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({9.81,9.81,9.81})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({9.81,9.81,9.81})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({3.14,3.14,3.14})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({3.14,3.14,3.14})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for unsorted
        REQUIRE_THROWS_AS((u.nextDraw({9.81,2.71,3.14})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({9.81,2.71,3.14})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({2.71,3.14,2.71})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({2.71,3.14,2.71})),"Either the specified draw is incorrect or there is no next valid draw");
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        GenericUrn<double,false,true> u {2,{3.14,2.71,9.81}};
        REQUIRE(RandomAccessRange<GenericUrn<double,false,true>>);
        REQUIRE((iterateRange(u.begin(), u.end())) == "3.140000 3.1400003.140000 2.7100003.140000 9.8100002.710000 2.7100002.710000 9.8100009.810000 9.810000");
        REQUIRE((iterateRange(u.rbegin(), u.rend())) == "9.810000 9.8100002.710000 9.8100002.710000 2.7100003.140000 9.8100003.140000 2.7100003.140000 3.140000");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(to_string(itBegin[0]) == "3.140000 3.140000");
        REQUIRE(to_string(itBegin[5]) == "9.810000 9.810000");
        REQUIRE_THROWS_AS((itBegin[-1]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[-1]),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS((itBegin[6]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[6]),"There is no valid draw for this ordinalnumber.");
        
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

        REQUIRE(u.end()-u.begin() == 6);
        REQUIRE(u.rend()-u.rbegin() == 6);

        ++itBegin;
        REQUIRE(to_string(*itBegin) == "3.140000 2.710000");
        itBegin++;
        REQUIRE(to_string(*itBegin) == "3.140000 9.810000");
        --itBegin;
        REQUIRE(to_string(*itBegin) == "3.140000 2.710000");
        itBegin--;
        REQUIRE(to_string(*itBegin) == "3.140000 3.140000");

        auto it {u.begin()};
        it += 2;
        REQUIRE(to_string(*it) == "3.140000 9.810000");
        it -= 1;
        REQUIRE(to_string(*it) == "3.140000 2.710000");
    }
}


//GenericUrn<TYPE,FALSE,FALSE> = Urn
TEST_CASE("GenericUrn<TYPE,FALSE,FALSE>")
{   
    SECTION("1")
    {
        GenericUrn<per::Person,false,false> u {2,{{"Anakin",22},{"Obi-Wan",38},{"Ahsoka",17}}};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 2);
        REQUIRE(u.z() == 3);
    }

    SECTION("2")
    {
        GenericUrn<per::Person,false,false> u {3,{{"Anakin",22},{"Obi-Wan",38},{"Ahsoka",17}}};
        REQUIRE(u.n() == 3);
        REQUIRE(u.k() == 3);
        REQUIRE(u.z() == 1);
    }

    SECTION("3")
    {
        GenericUrn<per::Person,false,false> u {2,{{"Anakin",22},{"Obi-Wan",38},{"Ahsoka",17},{"Rex",26}}};
        REQUIRE(per::outputPerson(u.firstDraw()) == "Anakin,22 Obi-Wan,38");
        REQUIRE(per::outputPerson(u.lastDraw()) == "Ahsoka,17 Rex,26");
        REQUIRE(per::outputPerson(u.nextDraw({{"Anakin",22},{"Ahsoka",17}})) == "Anakin,22 Rex,26");
        REQUIRE(per::outputPerson(u.nextDraw({{"Anakin",22},{"Rex",26}})) == "Obi-Wan,38 Ahsoka,17");
        REQUIRE(per::outputPerson(u.backDraw({{"Obi-Wan",38},{"Ahsoka",17}})) == "Anakin,22 Rex,26");
        REQUIRE(per::outputPerson(u.backDraw({{"Anakin",22},{"Rex",26}})) == "Anakin,22 Ahsoka,17");
        REQUIRE(per::outputPerson(u.draw(1)) == "Anakin,22 Ahsoka,17");
        REQUIRE(per::outputPerson(u.draw(0)) == "Anakin,22 Obi-Wan,38");
        REQUIRE(per::outputPerson(u.draw(5)) == "Ahsoka,17 Rex,26");

        REQUIRE_THROWS_AS(u.draw(-1),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(-1),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS(u.draw(6),std::domain_error);
        REQUIRE_THROWS_WITH(u.draw(6),"There is no valid draw for this ordinalnumber.");
    }   

    SECTION("4")
    {   
        GenericUrn<per::Person,false,false> u {2,{{"Anakin",22},{"Obi-Wan",38},{"Ahsoka",17}}};
        //Test for constructor
        REQUIRE_THROWS_AS((GenericUrn<per::Person,false,false> { 3,{} }),std::domain_error);
        REQUIRE_THROWS_WITH((GenericUrn<per::Person,false,false> { 3,{} }),"UrnOR with n == 0 and k > 0 is not valid.");

        //Test for range
        REQUIRE_THROWS_AS((u.nextDraw({{"Obi-Wan",38},{"Ahsoka",17}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({{"Obi-Wan",38},{"Ahsoka",17}})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({{"Anakin",22},{"Obi-Wan",38}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({{"Anakin",22},{"Obi-Wan",38}})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for unsorted
        REQUIRE_THROWS_AS((u.nextDraw({{"Obi-Wan",38},{"Anakin",22}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({{"Obi-Wan",38},{"Anakin",22}})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({{"Ahsoka",17},{"Anakin",22}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({{"Ahsoka",17},{"Anakin",22}})),"Either the specified draw is incorrect or there is no next valid draw");

        //Test for repetitions
        REQUIRE_THROWS_AS((u.nextDraw({{"Anakin",22},{"Anakin",22}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.nextDraw({{"Anakin",22},{"Anakin",22}})),"Either the specified draw is incorrect or there is no next valid draw");

        REQUIRE_THROWS_AS((u.backDraw({{"Obi-Wan",38},{"Obi-Wan",38}})),std::domain_error);
        REQUIRE_THROWS_WITH((u.backDraw({{"Obi-Wan",38},{"Obi-Wan",38}})),"Either the specified draw is incorrect or there is no next valid draw");
    
    }

    //Urn Iterator Test
    SECTION("5")
    {   
        GenericUrn<per::Person,false,false> u {2,{{"Anakin",22},{"Obi-Wan",38},{"Ahsoka",17}}};
        REQUIRE(RandomAccessRange<GenericUrn<per::Person,false,false>>);
        REQUIRE((per::iterateRange(u.begin(), u.end())) == "Anakin,22 Obi-Wan,38Anakin,22 Ahsoka,17Obi-Wan,38 Ahsoka,17");
        REQUIRE((per::iterateRange(u.rbegin(), u.rend())) == "Obi-Wan,38 Ahsoka,17Anakin,22 Ahsoka,17Anakin,22 Obi-Wan,38");

        auto itBegin {u.begin()};
        auto itEnd {u.end()};

        REQUIRE(per::outputPerson(itBegin[0]) == "Anakin,22 Obi-Wan,38");
        REQUIRE(per::outputPerson(itBegin[2]) == "Obi-Wan,38 Ahsoka,17");
        REQUIRE_THROWS_AS((itBegin[-1]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[-1]),"There is no valid draw for this ordinalnumber.");
        REQUIRE_THROWS_AS((itBegin[3]),std::domain_error);
        REQUIRE_THROWS_WITH((itBegin[3]),"There is no valid draw for this ordinalnumber.");
        
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

        REQUIRE(u.end()-u.begin() == 3);
        REQUIRE(u.rend()-u.rbegin() == 3);

        ++itBegin;
        REQUIRE(per::outputPerson(*itBegin) == "Anakin,22 Ahsoka,17");
        itBegin++;
        REQUIRE(per::outputPerson(*itBegin) == "Obi-Wan,38 Ahsoka,17");
        --itBegin;
        REQUIRE(per::outputPerson(*itBegin) == "Anakin,22 Ahsoka,17");
        itBegin--;
        REQUIRE(per::outputPerson(*itBegin) == "Anakin,22 Obi-Wan,38");

        auto it {u.begin()};
        it += 2;
        REQUIRE(per::outputPerson(*it) == "Obi-Wan,38 Ahsoka,17");
        it -= 1;
        REQUIRE(per::outputPerson(*it) == "Anakin,22 Ahsoka,17");
    }
}