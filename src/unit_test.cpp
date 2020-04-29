#include "catch.hpp"
#include "utility.h"
#include <string>

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

//void replace_all(std::string& s, const std::string& sub_str, const std::string& replace_str);

TEST_CASE("Test1")
{
    REQUIRE( 1==1 );
    REQUIRE( 2==2 );
}

TEST_CASE("Test2")
{
    REQUIRE( 1==1 );
    REQUIRE( 2==2 );
}

TEST_CASE("Test3")
{
    REQUIRE( 1==1 );
    REQUIRE( 2==2 );
}

TEST_CASE("Test4")
{
    REQUIRE( 1==1 );
    REQUIRE( 2==2 );
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

TEST_CASE("Replace All")
{
    std::string s = "Hello BEFORE this [BEFORE] <BEFORE> BEFORE";
    replace_all(s, "BEFORE", "AFTER");
    REQUIRE( s == "Hello AFTER this [AFTER] <AFTER> AFTER" );
    REQUIRE_FALSE( s != "Hello AFTER this [AFTER] <AFTER> AFTER" );
}

// TEST_CASE("Test1", "scanpf")
// {
    
// }

// g++ utility.cpp unit_test.cpp -o unit_test
// Compile implementation of Catch for use with files that do contain tests:
// - g++ -std=c++11 -Wall -I$(CATCH_SINGLE_INCLUDE) -c 000-CatchMain.cpp
// - cl -EHsc -I%CATCH_SINGLE_INCLUDE% -c 000-CatchMain.cpp
// Compile implementation of Catch for use with files that do contain tests:

// Specific Commands
// g++ -std=c++11 -Wall -c 000-CatchMain.cpp utility.cpp unit_test.cpp
// g++ -std=c++11 -Wall 000-CatchMain.o utility.o unit_test.o -o unit_test
// then, maybe if we are already up to date
// g++ -std=c++11 -Wall -c unit_test.cpp