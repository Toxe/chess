#include <utility>

#include "app/app_controller.hpp"
#include "board/board.hpp"
#include "command/command_factory.hpp"
#include "game/game_players.hpp"
#include "game/win_conditions.hpp"
#include "input/receive_player_command.hpp"
#include "output/console_writer.hpp"
#include "output/print_board.hpp"
#include "output/print_game_over.hpp"

using namespace chess;

int main()
{
    Board board = Board::create_with_default_pieces();
    GamePlayers game_players{PlayerType::human, PlayerType::human};
    AppController controller;
    ConsoleWriter console_writer;
    const CommandFactory command_factory{board, game_players, controller, console_writer};

    while (!game_over(get_win_condition(board))) {
        const Player player = game_players.current_player();
        const bool is_human_player = player_is_human(game_players.player_info(player));

        console_writer.write(print_board(board));

        auto command = receive_player_command(player, board, console_writer, command_factory);
        controller.execute(std::move(command));
    }

    console_writer.write(print_board(board));
    console_writer.write(print_game_over(get_win_condition(board)));
}
