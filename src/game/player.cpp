#include "player.hpp"

#include <cassert>

namespace chess {

bool player_is_human(const PlayerInfo& player_info)
{
    assert(player_is_valid(player_info.player));

    return player_info.type == PlayerType::human;
}

bool player_is_ai(const PlayerInfo& player_info)
{
    assert(player_is_valid(player_info.player));

    return player_info.type == PlayerType::ai;
}

bool player_is_valid(const Player player)
{
    return player == Player::white || player == Player::black;
}

Player opposing_player(const Player player)
{
    assert(player != Player::none);

    return player == Player::white ? Player::black : Player::white;
}

}  // namespace chess
