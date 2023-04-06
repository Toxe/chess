#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"
#include "fmt/core.h"

#include "../src/output/print_square.hpp"

namespace chess {

TEST_CASE("output/print_square")
{
    SECTION("print_square()")
    {
        CHECK_THAT(print_square({0, 0}), Catch::Matchers::Equals("a8"));  // eighth rank
        CHECK_THAT(print_square({1, 0}), Catch::Matchers::Equals("b8"));
        CHECK_THAT(print_square({6, 0}), Catch::Matchers::Equals("g8"));
        CHECK_THAT(print_square({7, 0}), Catch::Matchers::Equals("h8"));

        CHECK_THAT(print_square({0, 1}), Catch::Matchers::Equals("a7"));  // seventh rank
        CHECK_THAT(print_square({1, 1}), Catch::Matchers::Equals("b7"));
        CHECK_THAT(print_square({6, 1}), Catch::Matchers::Equals("g7"));
        CHECK_THAT(print_square({7, 1}), Catch::Matchers::Equals("h7"));

        CHECK_THAT(print_square({0, 6}), Catch::Matchers::Equals("a2"));  // second rank
        CHECK_THAT(print_square({1, 6}), Catch::Matchers::Equals("b2"));
        CHECK_THAT(print_square({6, 6}), Catch::Matchers::Equals("g2"));
        CHECK_THAT(print_square({7, 6}), Catch::Matchers::Equals("h2"));

        CHECK_THAT(print_square({0, 7}), Catch::Matchers::Equals("a1"));  // first rank
        CHECK_THAT(print_square({1, 7}), Catch::Matchers::Equals("b1"));
        CHECK_THAT(print_square({6, 7}), Catch::Matchers::Equals("g1"));
        CHECK_THAT(print_square({7, 7}), Catch::Matchers::Equals("h1"));
    }
}

}  // namespace chess