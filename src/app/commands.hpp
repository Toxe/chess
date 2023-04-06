#pragma once

#include "../command/command.hpp"

namespace chess {

class AppController;
class ConsoleWriter;
class GamePlayers;

Command HelpCommand(ConsoleWriter* console_writer);
Command QuitCommand();
Command UndoCommand(AppController* controller, const GamePlayers* game_players);
Command RedoCommand(AppController* controller, const GamePlayers* game_players);

}  // namespace chess
