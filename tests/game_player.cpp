#include "catch2/catch_test_macros.hpp"

#include "../src/game/player.hpp"

namespace chess {

TEST_CASE("game/player")
{
    SECTION("check if player is human")
    {
        const PlayerInfo player_info{Player::white, PlayerType::human};

        CHECK(player_is_human(player_info) == true);
        CHECK(player_is_ai(player_info) == false);
    }

    SECTION("check if player is AI")
    {
        const PlayerInfo player_info{Player::black, PlayerType::ai};

        CHECK(player_is_human(player_info) == false);
        CHECK(player_is_ai(player_info) == true);
    }

    SECTION("check if player side is valid")
    {
        CHECK(player_is_valid(Player::white) == true);
        CHECK(player_is_valid(Player::black) == true);
        CHECK(player_is_valid(Player::none) == false);
    }
}

}  // namespace chess
