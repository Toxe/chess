#include "pieces.hpp"

namespace chess {

PieceType piece_type_from_char(char c)
{
    switch (c) {
        case 'p':
        case 'P':
            return PieceType::pawn;
        case 'n':
        case 'N':
            return PieceType::knight;
        case 'b':
        case 'B':
            return PieceType::bishop;
        case 'r':
        case 'R':
            return PieceType::rook;
        case 'q':
        case 'Q':
            return PieceType::queen;
        case 'k':
        case 'K':
            return PieceType::king;
        default:
            return PieceType::none;
    }
}

}  // namespace chess
