#pragma once

#include "../game/player.hpp"
#include "square.hpp"

namespace chess {

int nth_rank(Player player, int nth);

bool on_home_rank(Player player, Square square);
bool on_second_rank(Player player, Square square);

}  // namespace chess
