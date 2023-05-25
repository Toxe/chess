#include "print.hpp"

#include "fmt/core.h"

#include "../board/print.hpp"
#include "../game/print.hpp"

namespace chess {

// ======== GameState ===============================================

std::string print_game_state(GameState game_state)
{
    return fmt::format("{} {} {} {}", print_castling_ability(game_state.castling_ability), game_state.en_passant_target_square ? print_square(*game_state.en_passant_target_square) : "-", game_state.halfmove_clock, game_state.fullmove_counter);
}

}  // namespace chess
