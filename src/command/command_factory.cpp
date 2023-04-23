#include "command_factory.hpp"

#include "../app/commands.hpp"
#include "../game/commands.hpp"

namespace chess {

Command CommandFactory::create_help_command() const
{
    return HelpCommand(console_writer_);
}

Command CommandFactory::create_quit_command() const
{
    return QuitCommand();
}

Command CommandFactory::create_undo_command() const
{
    return UndoCommand(controller_, game_players_);
}

Command CommandFactory::create_redo_command() const
{
    return RedoCommand(controller_, game_players_);
}

Command CommandFactory::create_player_move_command(const Move move) const
{
    return PlayerMoveCommand(game_players_, board_, console_writer_, move);
}

}  // namespace chess
