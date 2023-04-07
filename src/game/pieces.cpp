#include "pieces.hpp"

#include <cassert>

namespace chess {

Piece::Piece(const char letter)
{
    assert(letter == '-' || letter == 'p' || letter == 'n' || letter == 'b' || letter == 'r' || letter == 'q' || letter == 'k' || letter == 'P' || letter == 'N' || letter == 'B' || letter == 'R' || letter == 'Q' || letter == 'K');

    switch (letter) {
        case 'p':
            player = Player::black;
            type = PieceType::pawn;
            break;
        case 'P':
            player = Player::white;
            type = PieceType::pawn;
            break;
        case 'n':
            player = Player::black;
            type = PieceType::knight;
            break;
        case 'N':
            player = Player::white;
            type = PieceType::knight;
            break;
        case 'b':
            player = Player::black;
            type = PieceType::bishop;
            break;
        case 'B':
            player = Player::white;
            type = PieceType::bishop;
            break;
        case 'r':
            player = Player::black;
            type = PieceType::rook;
            break;
        case 'R':
            player = Player::white;
            type = PieceType::rook;
            break;
        case 'q':
            player = Player::black;
            type = PieceType::queen;
            break;
        case 'Q':
            player = Player::white;
            type = PieceType::queen;
            break;
        case 'k':
            player = Player::black;
            type = PieceType::king;
            break;
        case 'K':
            player = Player::white;
            type = PieceType::king;
            break;
        default:
            player = Player::none;
            type = PieceType::none;
            break;
    }
}

}  // namespace chess
