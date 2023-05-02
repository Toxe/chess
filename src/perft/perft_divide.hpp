#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../board/square.hpp"

namespace chess {

class PerftDivide {
public:
    PerftDivide() = default;
    PerftDivide(const std::string& example_data);

    void add(Square from, Square to, uint64_t num_moves);

    std::size_t size() const { return map_.size(); }
    uint64_t total_moves() const;

    std::vector<std::string> moves() const;
    bool has_move(const std::string& move) const;
    uint64_t move_count(const std::string& move) const;

private:
    std::map<std::string, uint64_t> map_{};
};

}  // namespace chess
