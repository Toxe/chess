#pragma once

#include <string>
#include <string_view>

#include "game_state.hpp"
#include "legal_moves.hpp"

namespace chess {

std::string print_game_state(GameState game_state);
std::string_view print_move_legality(MoveLegality move_legality);

}  // namespace chess
