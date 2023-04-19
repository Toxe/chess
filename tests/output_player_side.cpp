#include "catch2/catch_test_macros.hpp"

#include "../src/output/player_side.hpp"

namespace chess {

TEST_CASE("output/player_side")
{
    SECTION("White")
    {
        CHECK(player_side(Player::white) == "White");
    }

    SECTION("Black")
    {
        CHECK(player_side(Player::black) == "Black");
    }
}

}  // namespace chess
