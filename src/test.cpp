// Define this in only one file to add 'main'
#define CATCH_CONFIG_MAIN
// include the Catch framework
#include "catch.hpp"

// Test cases start with the 'TESTCASE' macro
TESTCASE("Simple Addition", "[test label]")
{
  std::vector<double> v;
  v.push_back(2.1);
  v.push_back(3.1);

  // Test values with the 'REQUIRE' macro
  REQUIRE(v.size() == 2);

  double sum = std::accumulate(v.begin(), v.end(), 0.0);

  // Floating point comparisons with tolerance using 'Approx'
  REQUIRE(sum == Approx(5.1));
}