#pragma once

#include <string_view>

#include "../game/pieces.hpp"

namespace chess {

char print_piece_letter(Piece piece);
std::string_view print_piece_symbol(Piece piece);

}  // namespace chess
