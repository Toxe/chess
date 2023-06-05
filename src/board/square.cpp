#include "square.hpp"

#include <cassert>

#include "file.hpp"
#include "rank.hpp"

namespace chess {

Square::Square(const std::string_view sv)
{
    assert(sv.size() == 2);
    assert(is_valid_file_char(sv[0]));
    assert(is_valid_rank_char(sv[1]));

    x = from_file(sv[0]);
    y = from_rank(sv[1]);
}

std::optional<Square> read_square(const std::string_view sv)
{
    if (sv.size() != 2 || !is_valid_file_char(sv[0]) || !is_valid_rank_char(sv[1]))
        return {};

    return Square{sv};
}

}  // namespace chess
