#include "player_side.hpp"

#include <cassert>

namespace chess {

std::string_view player_side(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? "White" : "Black";
}

}  // namespace chess
