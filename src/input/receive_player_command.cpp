#include "receive_player_command.hpp"

#include <iostream>
#include <limits>

#include "fmt/core.h"

#include "../game/print.hpp"
#include "../output/console_writer.hpp"
#include "eval_input.hpp"

namespace chess {

void clear_input()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string read_input(const Player player, ConsoleWriter& console_writer)
{
    std::string input;

    while (true) {
        console_writer.write(fmt::format("{}, your move? (type \"?\" for help)\n? ", print_player_side(player)));

        if ((std::cin >> input))
            break;

        console_writer.writeln("invalid input");
        clear_input();
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
