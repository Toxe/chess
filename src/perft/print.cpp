#include "print.hpp"

#include <algorithm>

#include "fmt/core.h"

namespace chess {

std::string print_perft_divide(const PerftDivide& perft_divide)
{
    std::string s;

    if (perft_divide.size() > 0) {
        std::vector<std::string> lines;

        for (const auto& move : perft_divide.moves())
            lines.push_back(fmt::format("{}: {}\n", move, perft_divide.move_count(move)));

        std::sort(lines.begin(), lines.end());

        for (const auto& line : lines)
            s += line;
    }

    return s + fmt::format("total: {}", perft_divide.total_moves());
}

}  // namespace chess
