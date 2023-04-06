#include "print_square.hpp"

namespace chess {

std::string print_square(const Square square)
{
    return std::string{static_cast<char>('a' + square.x), static_cast<char>('8' - square.y)};
}

}  // namespace chess
