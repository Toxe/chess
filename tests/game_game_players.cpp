#include "catch2/catch_test_macros.hpp"

#include "../src/game/game_players.hpp"

namespace chess {

TEST_CASE("game/game_players")
{
    SECTION("first player is White")
    {
        const GamePlayers game_players{PlayerType::human, PlayerType::ai};

        CHECK(game_players.current_player() == Player::white);
    }

    SECTION("get player info")
    {
        const GamePlayers game_players{PlayerType::human, PlayerType::ai};

        const PlayerInfo player1_info = game_players.player_info(Player::white);
        CHECK(player1_info.player == Player::white);
        CHECK(player1_info.type == PlayerType::human);

        const PlayerInfo player2_info = game_players.player_info(Player::black);
        CHECK(player2_info.player == Player::black);
        CHECK(player2_info.type == PlayerType::ai);
    }

    SECTION("can switch between the players")
    {
        GamePlayers game_players{PlayerType::human, PlayerType::ai};

        game_players.switch_players();
        CHECK(game_players.current_player() == Player::black);

        game_players.switch_players();
        CHECK(game_players.current_player() == Player::white);

        game_players.switch_players();
        CHECK(game_players.current_player() == Player::black);
    }

    SECTION("check if a human player is playing against AI")
    {
        CHECK(GamePlayers{PlayerType::human, PlayerType::ai}.playing_against_ai() == true);
        CHECK(GamePlayers{PlayerType::ai, PlayerType::human}.playing_against_ai() == true);
        CHECK(GamePlayers{PlayerType::human, PlayerType::human}.playing_against_ai() == false);
        CHECK(GamePlayers{PlayerType::ai, PlayerType::ai}.playing_against_ai() == false);
    }
}

}  // namespace chess
