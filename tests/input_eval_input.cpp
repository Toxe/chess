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
        Board board = Board::create_with_default_pieces();
        GamePlayers game_players{PlayerType::human, PlayerType::human};
        AppController controller;
        ConsoleWriter console_writer{false};
        const CommandFactory command_factory{board, game_players, controller, console_writer};

        SECTION("empty input returns an invalid command (nullopt)")
        {
            CHECK(eval_input(Player::white, board, command_factory, "").has_value() == false);
        }

        SECTION("simple keyword commands")
        {
            CHECK(eval_input(Player::white, board, command_factory, "?").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "h").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "q").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "r").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "u").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "exit").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "help").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "quit").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "redo").has_value());
            CHECK(eval_input(Player::white, board, command_factory, "undo").has_value());
        }

        SECTION("player move commands")
        {
            CHECK(eval_input(Player::white, board, command_factory, "a2a3").has_value());
            CHECK(eval_input(Player::black, board, command_factory, "a7a5").has_value());

            CHECK(eval_input(Player::white, board, command_factory, "").error() == "invalid input");
            CHECK(eval_input(Player::white, board, command_factory, "a1").error() == "invalid input");
            CHECK(eval_input(Player::white, board, command_factory, "a1a23").error() == "invalid input");
            CHECK(eval_input(Player::white, board, command_factory, "x9a1").error() == "invalid source square");
            CHECK(eval_input(Player::white, board, command_factory, "a1y9").error() == "invalid destination square");
            CHECK(eval_input(Player::white, board, command_factory, "d4d5").error() == "no piece found");
            CHECK(eval_input(Player::white, board, command_factory, "c7c6").error() == "wrong owner of piece");
        }

        SECTION("can receive commands for both players")
        {
            auto command1 = eval_input(Player::white, board, command_factory, "b2b4");
            controller.execute(std::move(*command1));
            CHECK(board.piece({"b4"}) == Piece{'P'});

            auto command2 = eval_input(Player::black, board, command_factory, "g8f6");
            controller.execute(std::move(*command2));
            CHECK(board.piece({"f6"}) == Piece{'n'});
        }
    }
}

}  // namespace chess
