#include "commands.hpp"

#include <cassert>
#include <stdexcept>

#include "fmt/core.h"

#include "../board/board.hpp"
#include "../game/game_players.hpp"
#include "../output/console_writer.hpp"
#include "print.hpp"

namespace chess {

Command PlayerMoveCommand(GamePlayers* game_players, Board* board, ConsoleWriter* console_writer, const Move move)
{
    assert(player_is_valid(move.player()));

    const Piece piece_at_destination = board->piece(move.to);

    return Command{
        .execute = [=]() {
            console_writer->writeln(fmt::format("> {} move: {}", print_player_side(move.player()), print_move(move)));

            board->change_piece(move.from, no_piece);
            board->change_piece(move.to, move.piece);

            game_players->switch_players(); },
        .undo = [=]() {
            console_writer->writeln(fmt::format("> undo {} move: {}", print_player_side(move.player()), print_move(move)));

            board->change_piece(move.from, move.piece);
            board->change_piece(move.to, piece_at_destination);

            game_players->switch_players(); }};
}

}  // namespace chess
