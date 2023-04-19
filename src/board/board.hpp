#pragma once

#include <initializer_list>
#include <string_view>

#include "../game/pieces.hpp"
#include "../grid/grid.hpp"
#include "square.hpp"

namespace chess {

class Board {
public:
    Board() : squares_{8, 8, no_piece} { }

    [[nodiscard]] static Board create_with_default_pieces();
    [[nodiscard]] static Board create_from_letter_data(std::initializer_list<std::string_view> data);

    [[nodiscard]] int cols() const { return squares_.width(); }
    [[nodiscard]] int rows() const { return squares_.height(); }

    [[nodiscard]] Piece piece(Square square) const;
    void change_piece(Square square, Piece piece);

    [[nodiscard]] bool empty_square(Square square) const;

    bool operator==(const Board& other) const = default;
    bool operator!=(const Board& other) const = default;

private:
    Grid<Piece, Square> squares_;
};

}  // namespace chess
