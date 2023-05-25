#include <utility>

#include "ai/receive_ai_command.hpp"
#include "app/app_controller.hpp"
#include "board/board.hpp"
#include "board/print.hpp"
#include "command/command_factory.hpp"
#include "game/game_players.hpp"
#include "game/print.hpp"
#include "game/win_conditions.hpp"
#include "input/receive_player_command.hpp"
#include "move_generator/game_state.hpp"
#include "move_generator/print.hpp"
#include "output/console_writer.hpp"

using namespace chess;

int main()
{
    Board board = Board::create_with_default_pieces();
    GameState game_state{0, 1, CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt};

    GamePlayers game_players{PlayerType::human, PlayerType::ai};
    AppController controller;
    ConsoleWriter console_writer;
    const CommandFactory command_factory{board, game_state, game_players, controller, console_writer};

    while (!game_over(get_win_condition(board, game_state))) {
        const Player player = game_players.current_player();
        const bool is_human_player = player_is_human(game_players.player_info(player));

        console_writer.write(print_board(board));
        console_writer.writeln(print_game_state(game_state));

        auto command = is_human_player ? receive_player_command(player, board, console_writer, command_factory) : receive_ai_command(player, board, command_factory, console_writer);
        controller.execute(std::move(command));
    }

    console_writer.write(print_board(board));
    console_writer.write(print_game_over(get_win_condition(board, game_state)));
}
