#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/perft/perft_divide.hpp"

namespace chess {

TEST_CASE("perft/perft_divide")
{
    SECTION("add moves and calculate total")
    {
        PerftDivide perft_divide;

        CHECK(perft_divide.total_moves() == 0);

        perft_divide.add(Square{"a1"}, Square{"a2"}, 5);
        perft_divide.add(Square{"b2"}, Square{"c2"}, 10);
        perft_divide.add(Square{"f4"}, Square{"f5"}, 100);

        CHECK(perft_divide.total_moves() == 115);
    }

    SECTION("construct with example data")
    {
        FAIL();
    }
}

}  // namespace chess
