#include "board.hpp"

namespace chess {

bool Board::empty_square(const Square square) const
{
    return squares_.at(square) == 0;
}

}  // namespace chess
