#pragma once

#include <cassert>

#include "../game/player.hpp"
#include "square.hpp"

namespace chess {

Square::coordinates_type nth_rank(Player player, char nth);

bool on_home_rank(Player player, Square square);
bool on_second_rank(Player player, Square square);

[[nodiscard]] constexpr bool is_valid_rank_char(const char c) { return c >= '1' && c <= '8'; }

[[nodiscard]] constexpr Square::coordinates_type from_rank(const char rank)
{
    assert(is_valid_rank_char(rank));
    return '8' - rank;
}

[[nodiscard]] constexpr char to_rank(const char row)
{
    assert(row >= 0 && row <= 7);
    return '8' - row;
}

}  // namespace chess
