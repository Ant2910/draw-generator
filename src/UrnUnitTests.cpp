// UrnUnitTests.cpp by Ulrich Eisenecker, May 17, 2023

   #define CATCH_CONFIG_MAIN
   #include <catch2/catch.hpp>

   #include "urn.hpp"
   #include <iostream>
   #include <string>
   #include <type_traits>

namespace convert
{  
   template<typename T>
   std::string to_string(const T& s)
   {
      return std::to_string(s);
   }

   template<>
   std::string to_string(const std::string& s)
   {  
      return s;
   }
}

template <class T>
std::string to_string(const T& urn)
{
   std::string result;
   for (urn::uint i { 0 }; i < urn.k(); ++i)
   {
      if (i > 0)
      {
         result += " ";
      }
      result += convert::to_string(urn[i]);
   }
   return result;
}

TEST_CASE("UrnOR")
{
   using namespace urn;
   SECTION("1")
   {
      UrnOR u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("2")
   {
      REQUIRE_THROWS_AS((UrnOR { 0,1 }),std::domain_error);
      REQUIRE_THROWS_WITH((UrnOR { 0,1 }),
         "UrnOR with n == 0 and k > 0 is not valid.");
   }
   SECTION("3")
   {
      UrnOR u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("4")
   {
      UrnOR u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("5")
   {
      UrnOR u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("6")
   {
      UrnOR u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("UrnO")
{
   using namespace urn;
   SECTION("7")
   {
      UrnO u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("8")
   {
      REQUIRE_THROWS_AS((UrnO { 0,1 }),std::domain_error);
      REQUIRE_THROWS_WITH((UrnO { 0,1 }),
         "UrnO with k > n is not valid.");
   }
   SECTION("9")
   {
      UrnO u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("10")
   {
      UrnO u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("11")
   {
      UrnO u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("12")
   {
      UrnO u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0");
      REQUIRE(u.next() == false);
   }
   SECTION("13")
   {
      UrnO u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 1 0");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("UrnR")
{
   using namespace urn;
   SECTION("14")
   {
      REQUIRE_THROWS_AS((UrnR { 0,1 }),std::domain_error);
      REQUIRE_THROWS_WITH((UrnR { 0,1 }),
         "UrnR with n = 0 is not valid.");
   }
   SECTION("15")
   {
      UrnR u { 1,0 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("16")
   {
      UrnR u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("17")
   {
      UrnR u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("18")
   {
      UrnR u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1");
      REQUIRE(u.next() == false);
   }
   SECTION("19")
   {
      UrnR u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 2 2");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("Urn")
{
   using namespace urn;
   SECTION("20")
   {
      Urn u { 0,0 };
      REQUIRE(u.n() == 0);
      REQUIRE(u.k() == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("21")
   {
      REQUIRE_THROWS_AS((Urn { 0,1 }),std::domain_error);
      REQUIRE_THROWS_WITH((Urn { 0,1 }),
         "UrnOR with n == 0 and k > 0 is not valid.");
   }
   SECTION("22")
   {
      Urn u { 1,1 };
      REQUIRE(u.n() == 1);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == false);
   }
   SECTION("23")
   {
      Urn u { 2,1 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 1);
      REQUIRE(u.at(0) == 0);
      REQUIRE(u[0] == 0);
      REQUIRE(u.next() == true);
      REQUIRE(u.at(0) == 1);
      REQUIRE(u[0] == 1);
      REQUIRE(u.next() == false);
   }
   SECTION("24")
   {
      Urn u { 2,2 };
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == false);
   }
   SECTION("25")
   {
      Urn u { 3,3 };
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == false);
   }
   SECTION("26")
   {
      Urn u { 4,3 };
      REQUIRE(u.n() == 4);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 3");
      REQUIRE(u.next() == false);
   }
}

TEST_CASE("GenericUrn")
{
   using namespace urn;
   SECTION("27")
   {
      REQUIRE_THROWS_AS((GenericUrn<std::string,true,true> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((GenericUrn<std::string,true,true> { 1,{} }), "UrnOR with n == 0 and k > 0 is not valid.");
      REQUIRE_THROWS_AS((Permutation<std::string> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((Permutation<std::string> { 1,{} }), "UrnOR with n == 0 and k > 0 is not valid.");
   }
   SECTION("28")
   {
      GenericUrn<std::string,true,true> u { 2,{ "0","1" } };
      Permutation<std::string> u2 { 2,{ "0","1" } };
      REQUIRE(std::is_same_v<decltype(u),decltype(u2)> == true);
      REQUIRE(u.n() == 2);
      REQUIRE(u.k() == 2);
      REQUIRE(to_string(u) == "0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1");
      REQUIRE(u.next() == false);
   }
   SECTION("29")
   {
      REQUIRE_THROWS_AS((GenericUrn<std::string,true,false> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((GenericUrn<std::string,true,false> { 1,{} }), "UrnO with k > n is not valid.");
      REQUIRE_THROWS_AS((PartialPermutation<std::string> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((PartialPermutation<std::string> { 1,{} }), "UrnO with k > n is not valid.");
   }
   SECTION("30")
   {
      GenericUrn<std::string,true,false> u { 3,{ "0","1","2" } };
      PartialPermutation<std::string> u2 { 3,{ "0","1","2" } };
      REQUIRE(std::is_same_v<decltype(u),decltype(u2)> == true);
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 1 0");
      REQUIRE(u.next() == false);
   }
   SECTION("31")
   {
      REQUIRE_THROWS_AS((GenericUrn<std::string,false,true> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((GenericUrn<std::string,false,true> { 1,{} }), "UrnR with n = 0 is not valid.");
      REQUIRE_THROWS_AS((MultiCombination<std::string> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((MultiCombination<std::string> { 1,{} }), "UrnR with n = 0 is not valid.");
   }
   SECTION("32")
   {
      GenericUrn<std::string,false,true> u { 3,{ "0","1","2" } };
      MultiCombination<std::string> u2 { 3,{ "0","1","2" } };
      REQUIRE(std::is_same_v<decltype(u),decltype(u2)> == true);
      REQUIRE(u.n() == 3);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 0 0");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 0 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 1");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "2 2 2");
      REQUIRE(u.next() == false);
   }
   SECTION("33")
   {
      REQUIRE_THROWS_AS((GenericUrn<std::string,false,false> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((GenericUrn<std::string,false,false> { 1,{} }), "UrnOR with n == 0 and k > 0 is not valid.");
      REQUIRE_THROWS_AS((Combination<std::string> { 1,{} }),std::domain_error);
      REQUIRE_THROWS_WITH((Combination<std::string> { 1,{} }), "UrnOR with n == 0 and k > 0 is not valid.");
   }
   SECTION("34")
   {
      GenericUrn<std::string,false,false> u { 3,{ "0","1","2","3" } };
      Combination<std::string> u2 { 3,{ "0","1","2","3" } };
      REQUIRE(std::is_same_v<decltype(u),decltype(u2)> == true);
      REQUIRE(u.n() == 4);
      REQUIRE(u.k() == 3);
      REQUIRE(to_string(u) == "0 1 2");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 1 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "0 2 3");
      REQUIRE(u.next() == true);
      REQUIRE(to_string(u) == "1 2 3");
      REQUIRE(u.next() == false);
   }
}
