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

    SECTION("determine the opposing player")
    {
        CHECK(opposing_player(Player::white) == Player::black);
        CHECK(opposing_player(Player::black) == Player::white);
    }

    SECTION("return Player from char")
    {
        CHECK(player_from_char('p') == Player::black);
        CHECK(player_from_char('n') == Player::black);
        CHECK(player_from_char('b') == Player::black);
        CHECK(player_from_char('r') == Player::black);
        CHECK(player_from_char('q') == Player::black);
        CHECK(player_from_char('k') == Player::black);
        CHECK(player_from_char('P') == Player::white);
        CHECK(player_from_char('N') == Player::white);
        CHECK(player_from_char('B') == Player::white);
        CHECK(player_from_char('R') == Player::white);
        CHECK(player_from_char('Q') == Player::white);
        CHECK(player_from_char('K') == Player::white);
        CHECK(player_from_char('-') == Player::none);
        CHECK(player_from_char('?') == Player::none);
        CHECK(player_from_char('1') == Player::none);
    }
}

}  // namespace chess
