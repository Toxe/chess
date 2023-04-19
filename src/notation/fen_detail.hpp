#pragma once

#include <optional>
#include <string_view>
#include <vector>

#include "../board/board.hpp"
#include "../game/castling_ability.hpp"
#include "../game/player.hpp"

namespace chess::detail::fen {

std::vector<std::string_view> split_string(std::string_view sv, char delim);

Board process_piece_placement(std::string_view sv);
Player process_side_to_move(std::string_view sv);
CastlingAbility process_castling_ability(std::string_view sv);
std::optional<Square> process_en_passant_target_square(std::string_view sv);
int process_halfmove_clock(std::string_view sv);
int process_fullmove_counter(std::string_view sv);

}  // namespace chess::detail::fen
