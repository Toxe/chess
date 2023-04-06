#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/print_game_over.hpp"

namespace chess {

TEST_CASE("output/print_game_over")
{
    SECTION("game is not over")
    {
        CHECK_THAT(print_game_over(WinCondition::none), Catch::Matchers::Equals("The game is not over yet."));
    }

    SECTION("draw")
    {
        CHECK_THAT(print_game_over(WinCondition::draw), Catch::Matchers::Equals("Draw!"));
    }

    SECTION("White won")
    {
        CHECK_THAT(print_game_over(WinCondition::player1_won), Catch::Matchers::Equals("White won!"));
    }

    SECTION("Black won")
    {
        CHECK_THAT(print_game_over(WinCondition::player2_won), Catch::Matchers::Equals("Black won!"));
    }
}

}  // namespace chess
