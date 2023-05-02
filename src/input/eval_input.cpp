#include "eval_input.hpp"

#include <cassert>

#include "../board/board.hpp"
#include "../command/command_factory.hpp"

namespace chess {

std::optional<Command> check_keyword_commands(const CommandFactory& command_factory, const std::string_view input)
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

tl::expected<Command, std::string_view> check_move_command(const Player player, Board& board, const CommandFactory& command_factory, const std::string_view input)
{
    if (input.size() != 4)
        return tl::unexpected("invalid input");

    const auto from = read_square(input.substr(0, 2));
    const auto to = read_square(input.substr(2));

    if (!from)
        return tl::unexpected("invalid source square");

    if (!to)
        return tl::unexpected("invalid destination square");

    const auto piece = board.piece(*from);

    if (piece == no_piece)
        return tl::unexpected("no piece found");

    if (piece.player != player)
        return tl::unexpected("wrong owner of piece");

    // TODO: check if move is legal
    // TODO: move type

    return command_factory.create_player_move_command(Move::create_normal(*from, *to, piece));
}

tl::expected<Command, std::string_view> eval_input(const Player player, Board& board, const CommandFactory& command_factory, const std::string_view input)
{
    if (auto command = check_keyword_commands(command_factory, input))
        return *command;

    return check_move_command(player, board, command_factory, input);
}

}  // namespace chess
