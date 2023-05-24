#pragma once

#include <optional>

#include "../game/castling_ability.hpp"
#include "../game/move.hpp"

namespace chess {

struct GameState {
    int halfmove_clock = 0;
    int fullmove_counter = 1;

    CastlingAbility castling_ability;
    std::optional<Square> en_passant_target_square;

    bool operator==(const GameState& other) const = default;
    bool operator!=(const GameState& other) const = default;
};

[[nodiscard]] GameState update_game_state(GameState game_state, Move move);

}  // namespace chess
