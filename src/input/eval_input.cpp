#include "eval_input.hpp"

#include <cassert>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"

namespace chess {

std::optional<Command> check_keyword_commands(const CommandFactory& command_factory, const std::string& input)
{
    if (input == "?" || input == "h" || input == "help")
        return command_factory.create_help_command();
    else if (input == "q" || input == "quit" || input == "exit")
        return command_factory.create_quit_command();
    else if (input == "u" || input == "undo")
        return command_factory.create_undo_command();
    else if (input == "r" || input == "redo")
        return command_factory.create_redo_command();

    return {};
}

std::optional<Command> eval_input(const Player player, Board& board, const CommandFactory& command_factory, const std::string& input)
{
    return check_keyword_commands(command_factory, input);
}

}  // namespace chess
