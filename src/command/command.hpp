#pragma once

#include <functional>

namespace chess {

struct Command {
    std::function<void()> execute;
    std::function<void()> undo = nullptr;

    bool has_undo() const { return undo != nullptr; }
};

}  // namespace chess
