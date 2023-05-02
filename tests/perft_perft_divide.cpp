#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_contains.hpp"

#include "../src/perft/perft_divide.hpp"

namespace chess {

TEST_CASE("perft/perft_divide")
{
    SECTION("default construct")
    {
        PerftDivide perft_divide;

        CHECK(perft_divide.size() == 0);
        CHECK(perft_divide.total_moves() == 0);
        CHECK(perft_divide.moves().empty());
    }

    SECTION("construct with example data")
    {
        PerftDivide perft_divide{"a1a3: 50\n"
                                 "a1a2: 5\n"
                                 "f4f6: 20\n"
                                 "b2c2: 10\n"
                                 "f4f5: 100\n"};

        CHECK(perft_divide.size() == 5);
        CHECK(perft_divide.total_moves() == 185);

        const auto moves = perft_divide.moves();

        CHECK_THAT(moves, Catch::Matchers::Contains("a1a2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("a1a3"));
        CHECK_THAT(moves, Catch::Matchers::Contains("b2c2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f5"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f6"));
    }

    SECTION("add moves")
    {
        PerftDivide perft_divide;

        perft_divide.add(Square{"a1"}, Square{"a3"}, 50);
        perft_divide.add(Square{"a1"}, Square{"a2"}, 5);
        perft_divide.add(Square{"f4"}, Square{"f6"}, 20);
        perft_divide.add(Square{"b2"}, Square{"c2"}, 10);
        perft_divide.add(Square{"f4"}, Square{"f5"}, 100);

        CHECK(perft_divide.size() == 5);
        CHECK(perft_divide.total_moves() == 185);

        const auto moves = perft_divide.moves();

        CHECK_THAT(moves, Catch::Matchers::Contains("a1a2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("a1a3"));
        CHECK_THAT(moves, Catch::Matchers::Contains("b2c2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f5"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f6"));
    }
}

}  // namespace chess
