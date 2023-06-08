#pragma once

#include <string_view>

#include "tl/expected.hpp"

#include "../command/command.hpp"
#include "../game/player.hpp"
#include "../move_generator/game_state.hpp"

namespace chess {

class Board;
class CommandFactory;

tl::expected<Command, std::string_view> eval_keyword_command(const CommandFactory& command_factory, const std::string_view input);
tl::expected<Move, std::string_view> eval_move_input(Player player, Board& board, GameState game_state, std::string_view input);

}  // namespace chess
