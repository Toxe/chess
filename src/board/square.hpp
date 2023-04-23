#pragma once

#include <cstddef>
#include <optional>
#include <string_view>

#include "../grid/coords.hpp"

namespace chess {

struct Square : public Coords<char> {
    Square() : Coords{} { }
    Square(char board_col, char board_row);
    Square(int board_col, int board_row) : Square(static_cast<char>(board_col), static_cast<char>(board_row)) { }
    Square(std::size_t board_col, std::size_t board_row) : Square(static_cast<char>(board_col), static_cast<char>(board_row)) { }
    Square(std::string_view sv);  // "c5"
};

std::optional<Square> read_square(std::string_view sv);

}  // namespace chess
