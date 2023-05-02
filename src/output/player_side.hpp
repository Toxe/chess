#pragma once

#include <string_view>

#include "../game/player.hpp"

namespace chess {

std::string_view player_side(Player player);
std::string_view print_player(Player player);

}  // namespace chess
