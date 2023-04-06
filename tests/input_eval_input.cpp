#include <utility>
#include <vector>

#include "catch2/catch_test_macros.hpp"

#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_players.hpp"
#include "../src/input/eval_input.hpp"
#include "../src/output/console_writer.hpp"

namespace chess {

TEST_CASE("input/eval_input")
{
    SECTION("eval_input()")
    {
        Board board;
        GamePlayers game_players{PlayerType::human, PlayerType::ai};
        AppController controller;
        ConsoleWriter console_writer{false};
        const CommandFactory command_factory{board, game_players, controller, console_writer};

        SECTION("empty input returns an invalid command (nullopt)")
        {
            CHECK(eval_input(Player::white, board, command_factory, "") == std::nullopt);
        }

        SECTION("simple keyword commands")
        {
            CHECK(eval_input(Player::white, board, command_factory, "?") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "h") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "q") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "r") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "u") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "exit") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "help") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "quit") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "redo") != std::nullopt);
            CHECK(eval_input(Player::white, board, command_factory, "undo") != std::nullopt);
        }
    }
}

}  // namespace chess
