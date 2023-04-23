#include "square.hpp"

#include <cassert>

namespace chess {

bool is_valid_col_char(const char c) { return c >= 'a' && c <= 'h'; }
bool is_valid_row_char(const char c) { return c >= '0' && c <= '8'; }
short col_from_char(const char c) { return c - 'a'; }
short row_from_char(const char c) { return '8' - c; }

Square::Square(const short board_col, const short board_row)
{
    assert(board_col >= 0 && board_col < 8);
    assert(board_row >= 0 && board_row < 8);

    x = board_col;
    y = board_row;
}

Square::Square(const std::string_view sv)
{
    assert(sv.size() == 2);
    assert(is_valid_col_char(sv[0]));
    assert(is_valid_row_char(sv[1]));

    x = col_from_char(sv[0]);
    y = row_from_char(sv[1]);
}

std::optional<Square> read_square(const std::string_view sv)
{
    if (sv.size() != 2 || !is_valid_col_char(sv[0]) || !is_valid_row_char(sv[1]))
        return {};

    return Square{sv};
}

}  // namespace chess
