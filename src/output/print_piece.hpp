#pragma once

#include <string>
#include <string_view>

#include "../game/pieces.hpp"

namespace chess {

char print_piece_letter(Piece piece);
std::string_view print_piece_symbol(Piece piece);
std::string_view print_piece_type(PieceType type);
std::string print_piece_descriptive(Piece piece);

}  // namespace chess
