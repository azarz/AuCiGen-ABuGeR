#include "catch.h"

int factorial(int n)
{
    return n > 1 ? factorial(n-1)*n : 1;
}

/*

TEST_CASE("factorial are computed", "[factorial]")
{
    REQUIRE(factorial(1)==1);
    REQUIRE(factorial(0)==1);
    REQUIRE(factorial(2)==2);
    REQUIRE(factorial(10)==3628800);
    REQUIRE(factorial(3)==6);
}

*/
