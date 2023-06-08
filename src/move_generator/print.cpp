#include "print.hpp"

#include "fmt/core.h"

#include "../board/print.hpp"
#include "../game/print.hpp"

namespace chess {

// ======== GameState ===============================================

std::string print_game_state(const GameState game_state)
{
    return fmt::format("{} {} {} {}", print_castling_ability(game_state.castling_ability), game_state.en_passant_target_square ? print_square(*game_state.en_passant_target_square) : "-", game_state.halfmove_clock, game_state.fullmove_counter);
}

// ======== MoveLegality ============================================

std::string_view print_move_legality(const MoveLegality move_legality)
{
    switch (move_legality) {
        case MoveLegality::ok: return "ok";
        case MoveLegality::en_passant_target_square_not_set: return "illegal move: no en passant target square";
        case MoveLegality::en_passant_target_square_wrong: return "illegal move: wrong en passant target square";
        case MoveLegality::check: return "illegal move: check";
        case MoveLegality::would_result_in_check: return "illegal move: would result in check";
        case MoveLegality::square_under_attack: return "illegal move: king would pass through or finish on a square that is under attack";
        case MoveLegality::no_castling_ability: return "illegal move: no castling ability";
    }
}

}  // namespace chess
