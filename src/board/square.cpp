#include "square.hpp"

#include <cassert>

namespace chess {

Square::Square(const short col_on_board, const short row_on_board)
{
    assert(col_on_board >= 0 && col_on_board < 8);
    assert(row_on_board >= 0 && row_on_board < 8);

    x = col_on_board;
    y = row_on_board;
}

}  // namespace chess
