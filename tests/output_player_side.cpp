#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/player_side.hpp"

namespace chess {

TEST_CASE("output/player_side")
{
    SECTION("White")
    {
        CHECK_THAT(player_side(Player::white), Catch::Matchers::Equals("White"));
    }

    SECTION("Black")
    {
        CHECK_THAT(player_side(Player::black), Catch::Matchers::Equals("Black"));
    }
}

}  // namespace chess
