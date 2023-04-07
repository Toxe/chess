#include "print_board.hpp"

#include <cassert>
#include <sstream>

#include "print_piece.hpp"

namespace chess {

void print_empty_line(std::stringstream& out)
{
    out << '\n';
}

void print_top_border(std::stringstream& out)
{
    out << "┌────────────────────────────┐\n";
}

void print_bottom_border(std::stringstream& out)
{
    out << "└────────────────────────────┘\n";
}

void print_column_legend(std::stringstream& out)
{
    out << "│                            │\n"
        << "│    a  b  c  d  e  f  g  h  │\n";
}

void print_square(std::stringstream& out, const Square square, const Piece piece)
{
    const bool is_white_square = (square.x + square.y) % 2 == 0;

    if (piece == no_piece) {
        out << (is_white_square ? "███" : "   ");
    } else {
        if (is_white_square)
            out << "▌" << print_piece_symbol(piece) << "▐";
        else
            out << ' ' << print_piece_symbol(piece) << ' ';
    }
}

void print_row(std::stringstream& out, const Board& board, const int row)
{
    out << "│" << (8 - row) << "  ";

    for (Square square{0, row}; square.x < board.cols(); ++square.x)
        print_square(out, square, board.piece(square));

    out << " │\n";
}

std::string print_board(const Board& board)
{
    std::stringstream out;

    print_empty_line(out);
    print_top_border(out);

    for (int row = 0; row < board.rows(); ++row)
        print_row(out, board, row);

    print_column_legend(out);
    print_bottom_border(out);
    print_empty_line(out);

    return out.str();
}

}  // namespace chess
