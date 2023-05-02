#include "receive_player_command.hpp"

#include "fmt/core.h"
#include "scn/all.h"

#include "../game/print.hpp"
#include "../output/console_writer.hpp"
#include "eval_input.hpp"

namespace chess {

std::string read_input(const Player player, ConsoleWriter& console_writer)
{
    std::string input;

    while (true) {
        if (scn::prompt(fmt::format("{}, your move? (type \"?\" for help)\n? ", print_player_side(player)).c_str(), "{}", input))
            break;

        console_writer.writeln("invalid input");
    }

    return input;
}

Command receive_player_command(const Player player, Board& board, ConsoleWriter& console_writer, const CommandFactory& command_factory)
{
    while (true) {
        const auto input = read_input(player, console_writer);
        const auto command = eval_input(player, board, command_factory, input);

        if (!command)
            console_writer.writeln(command.error());
        else
            return *command;
    }
}

}  // namespace chess
