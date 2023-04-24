#include "square.hpp"

#include <cassert>

namespace chess {

bool is_valid_col_char(const char c) { return c >= 'a' && c <= 'h'; }
bool is_valid_row_char(const char c) { return c >= '0' && c <= '8'; }
char col_from_char(const char c) { return c - 'a'; }
char row_from_char(const char c) { return '8' - c; }

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
