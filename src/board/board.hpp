#pragma once

#include "../grid/grid.hpp"
#include "square.hpp"

namespace chess {

class Board {
public:
    Board() : squares_{8, 8} { }

    [[nodiscard]] int cols() const { return squares_.width(); }
    [[nodiscard]] int rows() const { return squares_.height(); }

    [[nodiscard]] bool empty_square(Square square) const;

private:
    Grid<int, Square> squares_;
};

}  // namespace chess
