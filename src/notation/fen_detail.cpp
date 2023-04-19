#include "fen_detail.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

namespace chess::detail::fen {

// Simple split function for strings like "one two three" (with delim=' '). Restrictions:
// - Must not begin (" bad") or end ("bad ") with 'delim'.
// - Only one consecutive 'delim' ("bad   string").
// - String must not be empty ("").
std::vector<std::string_view> split_string(const std::string_view sv, const char delim)
{
    if (sv.empty() || sv.back() == delim)
        throw std::runtime_error{"badly formed string"};

    std::vector<std::string_view> buf;
    auto first = sv.cbegin();

    while (first != sv.cend()) {
        if (*first == delim)
            throw std::runtime_error{"badly formed string"};

        const auto end = std::find(first, sv.cend(), delim);
        buf.emplace_back(first, end);

        if (end == sv.cend())
            break;

        first = end + 1;
    }

    return buf;
}

Board process_piece_placement(const std::string_view sv)
{
    const auto rows = split_string(sv, '/');

    if (rows.size() != 8)
        throw std::runtime_error{"badly formed FEN line"};

    Board board;
    Square square{0, 0};

    for (const auto& row : rows) {
        square.x = 0;

        for (const char c : row) {
            if (c >= '1' && c <= '8') {
                square.move_right((c - '1') + 1);
            } else {
                board.change_piece(square, Piece{c});
                square.move_right();
            }
        }

        square.move_down();
    }

    return board;
}

Player process_side_to_move(const std::string_view sv)
{
    if (sv == "w")
        return Player::white;
    else if (sv == "b")
        return Player::black;

    throw std::runtime_error{"invalid side to move"};
}

CastlingAbility process_castling_ability(const std::string_view sv)
{
    CastlingAbility castling_ability;

    if (sv.empty() || sv.size() > 4)
        throw std::runtime_error{"invalid castling ability"};

    if (sv == "-")
        return castling_ability;

    for (const char c : sv) {
        CastlingRight castling_right = CastlingRight::none;

        switch (c) {
            case 'K': castling_right = CastlingRight::white_king; break;
            case 'Q': castling_right = CastlingRight::white_queen; break;
            case 'k': castling_right = CastlingRight::black_king; break;
            case 'q': castling_right = CastlingRight::black_queen; break;
            default:
                throw std::runtime_error{"invalid castling ability"};
        }

        assert(castling_right != CastlingRight::none);

        if (castling_ability.has(castling_right))
            throw std::runtime_error{"invalid castling ability"};

        castling_ability.set(castling_right);
    }

    return castling_ability;
}

std::optional<Square> process_en_passant_target_square(const std::string_view sv)
{
    if (sv == "-")
        return {};

    if (sv.size() != 2)
        throw std::runtime_error{"invalid en passant target square"};

    return Square{sv};
}

int process_halfmove_clock(const std::string_view sv)
{
    const int halfmove_clock = std::stoi(std::string{sv});

    if (halfmove_clock < 0)
        throw std::runtime_error{"invalid halfmove clock"};

    return halfmove_clock;
}

int process_fullmove_counter(const std::string_view sv)
{
    const int fullmove_counter = std::stoi(std::string{sv});

    if (fullmove_counter < 1)
        throw std::runtime_error{"invalid fullmove counter"};

    return fullmove_counter;
}

}  // namespace chess::detail::fen
