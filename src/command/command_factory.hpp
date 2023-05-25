#pragma once

#include "../board/square.hpp"
#include "../game/move.hpp"
#include "command.hpp"

namespace chess {

class Board;
class GamePlayers;
class AppController;
class ConsoleWriter;
struct GameState;

class CommandFactory {
public:
    CommandFactory(Board& board, GameState& game_state, GamePlayers& game_players, AppController& controller, ConsoleWriter& console_writer)
        : board_{&board}, game_state_{&game_state}, game_players_{&game_players}, controller_{&controller}, console_writer_{&console_writer} { }

    Command create_help_command() const;
    Command create_quit_command() const;
    Command create_undo_command() const;
    Command create_redo_command() const;
    Command create_player_move_command(Move move) const;

private:
    Board* board_;
    GameState* game_state_;
    GamePlayers* game_players_;
    AppController* controller_;
    ConsoleWriter* console_writer_;
};

}  // namespace chess
