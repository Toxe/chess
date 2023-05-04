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
                                 "d7c8q: 1\n"
                                 "f4f5: 100\n"};

        CHECK(perft_divide.size() == 6);
        CHECK(perft_divide.total_moves() == 186);

        const auto moves = perft_divide.moves();

        CHECK_THAT(moves, Catch::Matchers::Contains("a1a2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("a1a3"));
        CHECK_THAT(moves, Catch::Matchers::Contains("b2c2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f5"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f6"));
        CHECK_THAT(moves, Catch::Matchers::Contains("d7c8q"));
    }

    SECTION("add moves")
    {
        PerftDivide perft_divide;

        perft_divide.add(Move::create_normal({"a1"}, {"a3"}, Piece{'R'}), 50);
        perft_divide.add(Move::create_normal({"a1"}, {"a2"}, Piece{'Q'}), 5);
        perft_divide.add(Move::create_normal({"f4"}, {"f6"}, Piece{'r'}), 20);
        perft_divide.add(Move::create_normal({"b2"}, {"c2"}, Piece{'k'}), 10);
        perft_divide.add(Move::create_normal({"f4"}, {"f5"}, Piece{'q'}), 100);
        perft_divide.add(Move::create_capture_and_promotion({"d7"}, {"c8"}, Piece{'Q'}, Piece{'r'}), 1);
        perft_divide.add(Move::create_promotion({"f2"}, {"f1"}, Piece{'n'}), 1);

        CHECK(perft_divide.size() == 7);
        CHECK(perft_divide.total_moves() == 187);

        const auto moves = perft_divide.moves();

        CHECK_THAT(moves, Catch::Matchers::Contains("a1a2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("a1a3"));
        CHECK_THAT(moves, Catch::Matchers::Contains("b2c2"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f5"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f4f6"));
        CHECK_THAT(moves, Catch::Matchers::Contains("d7c8q"));
        CHECK_THAT(moves, Catch::Matchers::Contains("f2f1n"));
    }
}

}  // namespace chess
