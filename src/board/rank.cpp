#include "rank.hpp"

#include <cassert>

namespace chess {

int nth_rank(const Player player, const int nth)
{
    assert(player_is_valid(player));
    assert(nth >= 1 && nth <= 8);

    return (player == Player::white) ? 8 - nth : nth - 1;
}

bool on_home_rank(const Player player, const Square square)
{
    assert(player_is_valid(player));

    return square.y == nth_rank(player, 1);
}

bool on_second_rank(const Player player, const Square square)
{
    assert(player_is_valid(player));

    return square.y == nth_rank(player, 2);
}

}  // namespace chess
