#include "catch_amalgamated.cpp"

/**
 * @brief Dummy method for using Catch2, as a default
 * 
 * @param number input number
 * @return int factorial of that input number
 */
uint32_t factorial( uint32_t number ) {
    return number <= 1 ? number : factorial(number-1) * number;
}

/**
 * @brief Dummy test cases for Catch2
 * 
 */
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( factorial( 1) == 1 );
    REQUIRE( factorial( 2) == 2 );
    REQUIRE( factorial( 3) == 6 );
    REQUIRE( factorial(10) == 3'628'800 );
}