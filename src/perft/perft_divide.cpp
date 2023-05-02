#include "perft_divide.hpp"

#include <numeric>
#include <sstream>

#include "../board/print.hpp"

namespace chess {

PerftDivide::PerftDivide(const std::string& example_data)
{
    std::istringstream in{example_data};

    while (true) {
        std::string move;
        uint64_t count;

        in >> move >> count;

        if (!in.good())
            break;

        map_[move.substr(0, 4)] = count;
    }
}

void PerftDivide::add(Square from, Square to, uint64_t num_moves)
{
    map_[print_square(from) + print_square(to)] = num_moves;
}

uint64_t PerftDivide::total_moves() const
{
    return std::accumulate(map_.begin(), map_.end(), uint64_t{}, [](uint64_t acc, auto it) { return acc + it.second; });
}

std::vector<std::string> PerftDivide::moves() const
{
    std::vector<std::string> moves;

    for (const auto& [move, count] : map_)
        moves.emplace_back(move);

    return moves;
}

bool PerftDivide::has_move(const std::string& move) const
{
    return map_.contains(move);
}

uint64_t PerftDivide::move_count(const std::string& move) const
{
    return map_.at(move);
}

}  // namespace chess
