#include "square.hpp"

#include <cassert>

namespace chess {

Square::Square(const short board_col, const short board_row)
{
    assert(board_col >= 0 && board_col < 8);
    assert(board_row >= 0 && board_row < 8);

    x = board_col;
    y = board_row;
}

Square::Square(std::string_view text)
{
    assert(text.size() == 2);
    assert(text[0] >= 'a' && text[0] <= 'h');
    assert(text[1] >= '0' && text[1] <= '8');

    x = static_cast<short>(text[0] - 'a');
    y = static_cast<short>('8' - text[1]);
}

}  // namespace chess
