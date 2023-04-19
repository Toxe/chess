#pragma once

#include <optional>
#include <string_view>

#include "../board/board.hpp"
#include "../game/castling_ability.hpp"
#include "../game/player.hpp"

namespace chess {

struct FEN {
    Board board;
    Player side_to_move;
    CastlingAbility castling_ability;
    std::optional<Square> en_passant_target_square;
    int halfmove_clock;
    int fullmove_counter;
};

FEN read_FEN(std::string_view fen);

}  // namespace chess
