#include <optional>
#include <utility>

#include "catch2/catch_test_macros.hpp"

#include "../src/ai/receive_ai_command.hpp"
#include "../src/app/app_controller.hpp"
#include "../src/board/board.hpp"
#include "../src/command/command_factory.hpp"
#include "../src/game/game_players.hpp"
#include "../src/move_generator/game_state.hpp"
#include "../src/output/console_writer.hpp"

namespace chess {

TEST_CASE("ai/receive_ai_command")
{
    GamePlayers game_players{PlayerType::ai, PlayerType::ai};
    GameState game_state;
    AppController controller;
    ConsoleWriter console_writer{false};

    SECTION("can receive commands for both players")
    {
        for (const auto player : {Player::white, Player::black}) {
            Board board = Board::create_from_letter_data({
                "----k---",
                "--pp----",
                "--------",
                "--------",
                "--------",
                "--------",
                "--PP----",
                "----K---",
            });

            const Board orig_board = board;
            const CommandFactory command_factory{board, game_state, game_players, controller, console_writer};

            auto command = receive_ai_command(player, board, game_state, command_factory, console_writer);
            controller.execute(std::move(command));

            CHECK(board != orig_board);
        }
    }
}

}  // namespace chess
