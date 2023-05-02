#include "catch2/catch_test_macros.hpp"

#include "../src/output/player_side.hpp"

namespace chess {

TEST_CASE("output/player_side")
{
    SECTION("player_side()")
    {
        CHECK(player_side(Player::white) == "White");
        CHECK(player_side(Player::black) == "Black");
    }

    SECTION("print_player()")
    {
        CHECK(print_player(Player::white) == "white");
        CHECK(print_player(Player::black) == "black");
    }
}

}  // namespace chess
