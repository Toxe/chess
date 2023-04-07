#include "catch2/catch_test_macros.hpp"

#include "../src/board/board.hpp"

namespace chess {

void check_for_default_pieces(const Board& board)
{
    CHECK(board.piece({"a8"}) == Piece{Player::black, PieceType::rook});
    CHECK(board.piece({"b8"}) == Piece{Player::black, PieceType::knight});
    CHECK(board.piece({"c8"}) == Piece{Player::black, PieceType::bishop});
    CHECK(board.piece({"d8"}) == Piece{Player::black, PieceType::queen});
    CHECK(board.piece({"e8"}) == Piece{Player::black, PieceType::king});
    CHECK(board.piece({"f8"}) == Piece{Player::black, PieceType::bishop});
    CHECK(board.piece({"g8"}) == Piece{Player::black, PieceType::knight});
    CHECK(board.piece({"h8"}) == Piece{Player::black, PieceType::rook});
    CHECK(board.piece({"a7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"b7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"c7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"d7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"e7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"f7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"g7"}) == Piece{Player::black, PieceType::pawn});
    CHECK(board.piece({"h7"}) == Piece{Player::black, PieceType::pawn});

    CHECK(board.piece({"a2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"b2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"c2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"d2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"e2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"f2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"g2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"h2"}) == Piece{Player::white, PieceType::pawn});
    CHECK(board.piece({"a1"}) == Piece{Player::white, PieceType::rook});
    CHECK(board.piece({"b1"}) == Piece{Player::white, PieceType::knight});
    CHECK(board.piece({"c1"}) == Piece{Player::white, PieceType::bishop});
    CHECK(board.piece({"d1"}) == Piece{Player::white, PieceType::queen});
    CHECK(board.piece({"e1"}) == Piece{Player::white, PieceType::king});
    CHECK(board.piece({"f1"}) == Piece{Player::white, PieceType::bishop});
    CHECK(board.piece({"g1"}) == Piece{Player::white, PieceType::knight});
    CHECK(board.piece({"h1"}) == Piece{Player::white, PieceType::rook});

    for (int row = 2; row < board.rows() - 2; ++row)
        for (int col = 0; col < board.cols(); ++col)
            CHECK(board.empty_square({col, row}));
}

TEST_CASE("game/board")
{
    SECTION("a new Board is empty")
    {
        const Board board;

        for (int row = 0; row < board.rows(); ++row)
            for (int col = 0; col < board.cols(); ++col)
                CHECK(board.empty_square({col, row}));
    }

    SECTION("cols() returns the number of columns")
    {
        CHECK(Board{}.cols() == 8);
    }

    SECTION("rows() returns the number of rows")
    {
        CHECK(Board{}.rows() == 8);
    }

    SECTION("piece() returns the piece on a square")
    {
        const Board board;

        CHECK(board.piece({2, 3}) == no_piece);
    }

    SECTION("change_piece() changes the piece on a square")
    {
        Board board;

        board.change_piece({2, 3}, Piece{Player::black, PieceType::king});
        CHECK(board.piece({2, 3}) == Piece{Player::black, PieceType::king});

        board.change_piece({2, 3}, Piece{Player::white, PieceType::queen});
        CHECK(board.piece({2, 3}) == Piece{Player::white, PieceType::queen});
    }

    SECTION("empty_square() checks if a square is empty")
    {
        const Board board;

        CHECK(board.empty_square({0, 0}));
    }

    SECTION("can create Board with default pieces")
    {
        check_for_default_pieces(Board::create_with_default_pieces());
    }

    SECTION("can create Board with letter data")
    {
        const auto board = Board::create_from_letter_data({
            "rnbqkbnr",
            "pppppppp",
            "--------",
            "--------",
            "--------",
            "--------",
            "PPPPPPPP",
            "RNBQKBNR",
        });

        check_for_default_pieces(board);
    }
}

}  // namespace chess
