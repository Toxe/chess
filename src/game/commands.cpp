#include "commands.hpp"

#include <cassert>
#include <stdexcept>

#include "fmt/core.h"

#include "../board/board.hpp"
#include "../game/game_players.hpp"
#include "../move_generator/game_state.hpp"
#include "../output/console_writer.hpp"
#include "print.hpp"

namespace chess {

Command PlayerMoveCommand(Board* board, GameState* game_state, GamePlayers* game_players, ConsoleWriter* console_writer, const Move move)
{
    assert(player_is_valid(move.player()));

    const Piece old_piece = board->piece(move.to);
    const GameState old_game_state = *game_state;

    return Command{
        .execute = [=]() {
            console_writer->writeln(fmt::format("> {} move: {}", print_player_side(move.player()), print_move(move)));

            board->change_piece(move.from, no_piece);
            board->change_piece(move.to, move.piece);

            *game_state = update_game_state(*game_state, move);

            game_players->switch_players(); },
        .undo = [=]() {
            console_writer->writeln(fmt::format("> undo {} move: {}", print_player_side(move.player()), print_move(move)));

            board->change_piece(move.from, move.piece);
            board->change_piece(move.to, old_piece);

            *game_state = old_game_state;

            game_players->switch_players(); }};
}

}  // namespace chess
