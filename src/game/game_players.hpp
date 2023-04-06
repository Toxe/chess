#pragma once

#include <array>

#include "player.hpp"

namespace chess {

class GamePlayers {
public:
    GamePlayers(PlayerType white_player_type, PlayerType black_player_type) : players_{PlayerInfo{Player::white, white_player_type}, PlayerInfo{Player::black, black_player_type}} { }

    [[nodiscard]] Player current_player() const { return current_player_; }
    [[nodiscard]] const PlayerInfo& player_info(Player player) const;

    [[nodiscard]] bool playing_against_ai() const;

    void switch_players();

private:
    std::array<PlayerInfo, 2> players_;
    Player current_player_ = Player::white;
};

}  // namespace chess
