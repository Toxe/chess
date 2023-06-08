#include "receive_ai_command.hpp"

#include <cassert>
#include <stdexcept>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"
#include "../move_generator/move_generator.hpp"
// #include "../move_generator/stats.hpp"
#include "../output/console_writer.hpp"

namespace chess {

Command receive_ai_command(const Player player, const Board& board, const GameState, const CommandFactory& command_factory, ConsoleWriter&)
{
    // MoveGeneratorStats stats;
    Board test_board = board;
    const auto move = generate_move(test_board, player);

    if (!move)
        throw std::runtime_error("no move found");

    // console_writer.write(stats.print());

    return command_factory.create_player_move_command(*move);
}

}  // namespace chess
