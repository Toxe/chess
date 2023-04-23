#pragma once

#include <cstddef>
#include <optional>
#include <string_view>

#include "../grid/coords.hpp"

namespace chess {

struct Square : public Coords<short> {
    Square() : Coords{} { }
    Square(short board_col, short board_row);
    Square(int board_col, int board_row) : Square(static_cast<short>(board_col), static_cast<short>(board_row)) { }
    Square(std::size_t board_col, std::size_t board_row) : Square(static_cast<short>(board_col), static_cast<short>(board_row)) { }
    Square(std::string_view sv);  // "c5"
};

std::optional<Square> read_square(std::string_view sv);

}  // namespace chess
