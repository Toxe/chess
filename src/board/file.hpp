#pragma once

#include <cassert>

#include "square.hpp"

namespace chess {

[[nodiscard]] constexpr bool is_valid_file_char(const char c) { return c >= 'a' && c <= 'h'; }

[[nodiscard]] constexpr Square::coordinates_type from_file(const char file)
{
    assert(is_valid_file_char(file));
    return file - 'a';
}

[[nodiscard]] constexpr char to_file(const char col)
{
    assert(col >= 0 && col <= 7);
    return 'a' + col;
}

}  // namespace chess
