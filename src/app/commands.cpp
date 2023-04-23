#include "commands.hpp"

#include <cstdlib>
#include <string_view>

#include "../app/app_controller.hpp"
#include "../game/game_players.hpp"
#include "../output/console_writer.hpp"

namespace chess {

Command HelpCommand(ConsoleWriter* console_writer)
{
    return Command{
        [=]() {
            const std::string_view output = R"(
Enter moves like "b2b4" or "g8f6".

(?), (h), (help): show help
(q), (quit), (exit): quit program
(u), (undo): undo last command
(r), (redo): redo last undo
)";

            console_writer->write(output);
        }};
}

Command QuitCommand()
{
    return Command{
        []() {
            std::exit(0);
        }};
}

Command UndoCommand(AppController* controller, const GamePlayers* game_players)
{
    return Command{
        [=]() {
            if (game_players->playing_against_ai())
                controller->undo();  // undo AI turn

            controller->undo();  // undo player turn
        }};
}

Command RedoCommand(AppController* controller, const GamePlayers* game_players)
{
    return Command{
        [=]() {
            controller->redo();  // redo player turn

            if (game_players->playing_against_ai())
                controller->redo();  // redo AI turn
        }};
}

}  // namespace chess
