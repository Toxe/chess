#include "fen.hpp"

#include <stdexcept>

#include "fen_detail.hpp"

namespace chess {

FEN read_FEN(const std::string_view fen)
{
    const auto parts = detail::fen::split_string(fen, ' ');

    if (parts.size() != 6)
        throw std::runtime_error{"badly formed FEN line"};

    return FEN{
        detail::fen::process_piece_placement(parts[0]),
        detail::fen::process_side_to_move(parts[1]),
        detail::fen::process_castling_ability(parts[2]),
        detail::fen::process_en_passant_target_square(parts[3]),
        detail::fen::process_halfmove_clock(parts[4]),
        detail::fen::process_fullmove_counter(parts[5]),
    };
}

}  // namespace chess
