#pragma once

namespace chess {

enum class Player : char {
    none = 0,
    white = 1,
    black = 2
};

enum class PlayerType {
    human,
    ai
};

struct PlayerInfo {
    Player player;
    PlayerType type;
};

bool player_is_human(const PlayerInfo& player_info);
bool player_is_ai(const PlayerInfo& player_info);
bool player_is_valid(Player player);

}  // namespace chess
