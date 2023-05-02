#include "player_side.hpp"

#include <cassert>

namespace chess {

std::string_view player_side(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? "White" : "Black";
}

std::string_view print_player(const Player player)
{
    assert(player_is_valid(player));

    return player == Player::white ? "white" : "black";
}

}  // namespace chess
