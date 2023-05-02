#include "print.hpp"

#include <cassert>
#include <sstream>

#include "../game/print.hpp"

namespace chess {

// ======== Square ==================================================

std::string print_square(const Square square)
{
    return std::string{static_cast<char>('a' + square.x), static_cast<char>('8' - square.y)};
}

// ======== Board ===================================================

void output_empty_line(std::stringstream& out)
{
    out << '\n';
}

void output_top_border(std::stringstream& out)
{
    out << "┌────────────────────────────┐\n";
}

void output_bottom_border(std::stringstream& out)
{
    out << "└────────────────────────────┘\n";
}

void output_column_legend(std::stringstream& out)
{
    out << "│                            │\n"
        << "│    a  b  c  d  e  f  g  h  │\n";
}

void output_square(std::stringstream& out, const Square square, const Piece piece)
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

void output_row(std::stringstream& out, const Board& board, const int row)
{
    out << "│" << (8 - row) << "  ";

    for (Square square{0, row}; square.x < board.cols(); ++square.x)
        output_square(out, square, board.piece(square));

    out << " │\n";
}

std::string print_board(const Board& board)
{
    std::stringstream out;

    output_empty_line(out);
    output_top_border(out);

    for (int row = 0; row < board.rows(); ++row)
        output_row(out, board, row);

    output_column_legend(out);
    output_bottom_border(out);
    output_empty_line(out);

    return out.str();
}

}  // namespace chess
