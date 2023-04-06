#include "catch2/catch_test_macros.hpp"

#include "../src/game/win_conditions.hpp"

namespace chess {

TEST_CASE("game/win_conditions")
{
    SECTION("a new board is not game over")
    {
        CHECK(game_over(get_win_condition(Board{})) == false);
    }
}

}  // namespace chess
