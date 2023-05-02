#pragma once

#include <string>
#include <string_view>

#include "move.hpp"
#include "pieces.hpp"
#include "player.hpp"
#include "win_conditions.hpp"

namespace chess {

std::string_view print_player(Player player);
std::string_view print_player_side(Player player);

std::string_view print_piece_type(PieceType type);

char print_piece_letter(Piece piece);
std::string_view print_piece_symbol(Piece piece);
std::string print_piece_descriptive(Piece piece);

std::string print_move(Move move);

std::string print_game_over(WinCondition win_condition);

}  // namespace chess
