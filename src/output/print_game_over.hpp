#pragma once

#include <string>

#include "../game/win_conditions.hpp"

namespace chess {

std::string print_game_over(WinCondition win_condition);

}  // namespace chess
