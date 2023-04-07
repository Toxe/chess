#include "board.hpp"

namespace chess {

Board Board::create_with_default_pieces()
{
    Board board;

    for (int col = 0; col < board.cols(); ++col) {
        board.change_piece({col, 1}, Piece{Player::black, PieceType::pawn});
        board.change_piece({col, 6}, Piece{Player::white, PieceType::pawn});
    }

    board.change_piece({"a8"}, Piece{Player::black, PieceType::rook});
    board.change_piece({"b8"}, Piece{Player::black, PieceType::knight});
    board.change_piece({"c8"}, Piece{Player::black, PieceType::bishop});
    board.change_piece({"d8"}, Piece{Player::black, PieceType::queen});
    board.change_piece({"e8"}, Piece{Player::black, PieceType::king});
    board.change_piece({"f8"}, Piece{Player::black, PieceType::bishop});
    board.change_piece({"g8"}, Piece{Player::black, PieceType::knight});
    board.change_piece({"h8"}, Piece{Player::black, PieceType::rook});

    board.change_piece({"a1"}, Piece{Player::white, PieceType::rook});
    board.change_piece({"b1"}, Piece{Player::white, PieceType::knight});
    board.change_piece({"c1"}, Piece{Player::white, PieceType::bishop});
    board.change_piece({"d1"}, Piece{Player::white, PieceType::queen});
    board.change_piece({"e1"}, Piece{Player::white, PieceType::king});
    board.change_piece({"f1"}, Piece{Player::white, PieceType::bishop});
    board.change_piece({"g1"}, Piece{Player::white, PieceType::knight});
    board.change_piece({"h1"}, Piece{Player::white, PieceType::rook});

    return board;
}

Board Board::create_from_letter_data(const std::initializer_list<std::string_view> data)
{
    Board board;
    int row = 0;

    assert(data.size() == static_cast<std::size_t>(board.rows()));

    for (const auto& line : data) {
        assert(line.size() == static_cast<std::size_t>(board.cols()));

        for (int col = 0; col < board.cols(); ++col)
            if (const auto c = line[static_cast<std::size_t>(col)]; c != '-')
                board.change_piece(Square{col, row}, Piece{c});

        ++row;
    }

    return board;
}

Piece Board::piece(const Square square) const
{
    return squares_.at(square);
}

void Board::change_piece(Square square, Piece piece)
{
    squares_.at(square) = piece;
}

bool Board::empty_square(const Square square) const
{
    return piece(square).type == PieceType::none;
}

}  // namespace chess
