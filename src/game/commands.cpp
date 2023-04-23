#include "commands.hpp"

#include <cassert>
#include <stdexcept>

#include "fmt/core.h"

#include "../board/board.hpp"
#include "../game/game_players.hpp"
#include "../output/console_writer.hpp"
#include "../output/player_side.hpp"
#include "../output/print_move.hpp"

namespace chess {

Command PlayerMoveCommand(GamePlayers* game_players, Board* board, ConsoleWriter* console_writer, const Move move)
{
    assert(player_is_valid(move.piece.player));

    const Piece piece_at_destination = board->piece(move.to);

    return Command{
        .execute = [=]() {
            console_writer->write(fmt::format("> {} move: {}\n", player_side(move.piece.player), print_move(move)));

            board->change_piece(move.from, no_piece);
            board->change_piece(move.to, move.piece);

            game_players->switch_players(); },
        .undo = [=]() {
            console_writer->write(fmt::format("> undo {} move: {}\n", player_side(move.piece.player), print_move(move)));

            board->change_piece(move.from, move.piece);
            board->change_piece(move.to, piece_at_destination);

            game_players->switch_players(); }};
}

}  // namespace chess
