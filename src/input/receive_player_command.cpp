#include "receive_player_command.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

#include "fmt/core.h"

#include "../command/command_factory.hpp"
#include "../game/print.hpp"
#include "../output/console_writer.hpp"
#include "eval_input.hpp"

namespace chess {

void to_lowercase(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](const unsigned char c) { return std::tolower(c); });
}

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

    to_lowercase(input);  // convert input to lowercase

    return input;
}

Command receive_player_command(const Player player, Board& board, const GameState game_state, ConsoleWriter& console_writer, const CommandFactory& command_factory)
{
    while (true) {
        const auto input = read_input(player, console_writer);

        // try keyword commands first
        if (const auto command = eval_keyword_command(command_factory, input); command)
            return *command;

        // try move commands after that
        if (const auto move = eval_move_input(player, board, game_state, input); move)
            return command_factory.create_player_move_command(*move);
        else
            console_writer.writeln(move.error());
    }
}

}  // namespace chess
