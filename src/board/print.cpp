#include "print.hpp"

#include <memory>
#include <sstream>
#include <utility>

#include "../game/print.hpp"

namespace chess {

// ======== Square ==================================================

std::string print_square(const Square square)
{
    return std::string{static_cast<char>('a' + square.x), static_cast<char>('8' - square.y)};
}

// ======== Board ===================================================

class BoardPrinter {
public:
    virtual ~BoardPrinter() = default;

    [[nodiscard]] std::string str() { return out_.str(); }

    void print_empty_line() { out_ << '\n'; }
    virtual void print_top_border() = 0;
    virtual void print_bottom_border() = 0;
    virtual void print_delimiter_row() = 0;
    virtual void print_column_legend() = 0;
    virtual void print_row_begin(int row) = 0;
    virtual void print_row_end() = 0;
    virtual void print_square(Square square, Piece piece) = 0;

protected:
    [[nodiscard]] std::stringstream& out() { return out_; }

private:
    std::stringstream out_;
};

class BoardSimplePrinter : public BoardPrinter {
public:
    void print_top_border() override { }
    void print_bottom_border() override { }
    void print_delimiter_row() override { out() << "   +---+---+---+---+---+---+---+---+\n"; }
    void print_column_legend() override { out() << "                                    \n     a   b   c   d   e   f   g   h  \n"; }
    void print_row_begin(const int row) override { out() << (8 - row) << "  "; }
    void print_row_end() override { out() << "|\n"; }
    void print_square(const Square, const Piece piece) override { out() << "| " << (piece == no_piece ? ' ' : print_piece_letter(piece)) << " "; }
};

class BoardUnicodePrinter : public BoardPrinter {
public:
    void print_top_border() override { out() << "┌────────────────────────────┐\n"; }
    void print_bottom_border() override { out() << "└────────────────────────────┘\n"; }
    void print_delimiter_row() override { }
    void print_column_legend() override { out() << "│                            │\n│    a  b  c  d  e  f  g  h  │\n"; }
    void print_row_begin(const int row) override { out() << "│" << (8 - row) << "  "; }
    void print_row_end() override { out() << " │\n"; }

    void print_square(const Square square, const Piece piece) override
    {
        const bool is_white_square = (square.x + square.y) % 2 == 0;

        if (piece == no_piece) {
            out() << (is_white_square ? "███" : "   ");
        } else {
            if (is_white_square)
                out() << "▌" << print_piece_symbol(piece) << "▐";
            else
                out() << ' ' << print_piece_symbol(piece) << ' ';
        }
    }
};

std::unique_ptr<BoardPrinter> create_board_printer(const BoardPrintFormat format)
{
    switch (format) {
        case BoardPrintFormat::simple: return std::make_unique<BoardSimplePrinter>();
        case BoardPrintFormat::unicode: return std::make_unique<BoardUnicodePrinter>();
    }

    std::unreachable();
}

std::string print_board(const Board& board, const BoardPrintFormat format)
{
    std::unique_ptr<BoardPrinter> printer = create_board_printer(format);

    printer->print_empty_line();
    printer->print_top_border();

    for (int row = 0; row < board.rows(); ++row) {
        printer->print_delimiter_row();
        printer->print_row_begin(row);

        for (Square square{0, row}; square.x < board.cols(); ++square.x)
            printer->print_square(square, board.piece(square));

        printer->print_row_end();

        if (row == 7)
            printer->print_delimiter_row();
    }

    printer->print_column_legend();
    printer->print_bottom_border();
    printer->print_empty_line();

    return printer->str();
}

}  // namespace chess
