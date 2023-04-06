#pragma once

#include <stack>

#include "../command/command.hpp"

namespace chess {

class AppController {
public:
    void execute(Command command);
    void undo();
    void redo();

private:
    std::stack<Command> undo_stack_{};
    std::stack<Command> redo_stack_{};
};

}  // namespace chess
