#include "print_move.hpp"

#include "print_square.hpp"

namespace chess {

std::string print_move(const Move move)
{
    return print_square(move.from) + print_square(move.to);
}

}  // namespace chess
