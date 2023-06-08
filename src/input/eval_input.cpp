#include "eval_input.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>

#include "../board/board.hpp"
#include "../board/file.hpp"
#include "../board/rank.hpp"
#include "../command/command_factory.hpp"
#include "../move_generator/legal_moves.hpp"
#include "../move_generator/list_moves.hpp"
#include "../move_generator/print.hpp"

namespace chess {

bool is_lowercase(const std::string_view sv)
{
    return std::all_of(sv.begin(), sv.end(), [](const unsigned char c) { return std::isalpha(c) ? std::islower(c) : true; });
}

tl::expected<Command, std::string_view> eval_keyword_command(const CommandFactory& command_factory, const std::string_view input)
{
    assert(is_lowercase(input));

    if (input == "?" || input == "h" || input == "help")
        return command_factory.create_help_command();
    else if (input == "q" || input == "quit" || input == "exit")
        return command_factory.create_quit_command();
    else if (input == "u" || input == "undo")
        return command_factory.create_undo_command();
    else if (input == "r" || input == "redo")
        return command_factory.create_redo_command();

    return tl::unexpected("invalid input");
}

tl::expected<Move, std::string_view> create_normal_or_capture_move(const Board& board, const Square from, const Square to, const Piece piece)
{
    auto move = Move::create_normal(from, to, piece);

    if (const auto captured_piece = board.piece(to); captured_piece != no_piece) {
        if (captured_piece.player == piece.player)
            return tl::unexpected("cannot capture own pieces");

        move.captured_piece = captured_piece;
        move.type = MoveType::capture;
    }

    return move;
}

tl::expected<Move, std::string_view> check_pawn_move_input(const Board& board, const Piece pawn, const Square from, const Square to, const std::string_view input)
{
    assert(input.size() == 4 || input.size() == 5);

    if (pawn.type != PieceType::pawn)
        return tl::unexpected("invalid input");

    // promotion
    if (input.size() == 5) {
        const auto captured_piece = board.piece(to);
        const auto promoted_piece = Piece{pawn.player, piece_type_from_char(input.back())};

        if (captured_piece.player == pawn.player)
            return tl::unexpected("cannot capture own pieces");

        if (promoted_piece.type == PieceType::none)
            return tl::unexpected("invalid input");

        if (promoted_piece.type != PieceType::knight && promoted_piece.type != PieceType::bishop && promoted_piece.type != PieceType::rook && promoted_piece.type != PieceType::queen)
            return tl::unexpected("invalid promotion piece");

        return captured_piece == no_piece ? Move::create_promotion(from, to, promoted_piece) : Move::create_capture_and_promotion(from, to, promoted_piece, captured_piece);
    }

    // en passant
    if (from.y == nth_rank(pawn.player, 5) && to.y == nth_rank(pawn.player, 6) && std::abs(to.x - from.x) == 1)
        return Move::create_en_passant(from, to, pawn);

    return create_normal_or_capture_move(board, from, to, pawn);
}

tl::expected<Move, std::string_view> check_normal_move_input(const Player player, const Board& board, const std::string_view input)
{
    if (input.size() < 4 || input.size() > 5)
        return tl::unexpected("invalid input");

    const auto from = read_square(input.substr(0, 2));
    const auto to = read_square(input.substr(2, 2));

    if (!from)
        return tl::unexpected("invalid source square");

    if (!to)
        return tl::unexpected("invalid destination square");

    const auto piece = board.piece(*from);

    if (piece == no_piece)
        return tl::unexpected("no piece found");

    if (piece.player != player)
        return tl::unexpected("can only move own pieces");

    if (piece.type == PieceType::pawn || input.size() == 5)
        return check_pawn_move_input(board, piece, *from, *to, input);

    return create_normal_or_capture_move(board, *from, *to, piece);
}

tl::expected<Move, std::string_view> check_castling_move_input(const Player player, const std::string_view input)
{
    if (input != "0-0" && input != "0-0-0" && input != "o-o" && input != "o-o-o")
        return tl::unexpected("invalid input");

    const auto home_rank = nth_rank(player, 1);
    const Square from{from_file('e'), home_rank};
    const Square to{(input == "0-0" || input == "o-o") ? from_file('g') : from_file('c'), home_rank};

    return Move::create_castling(from, to, Piece{player, PieceType::king});
}

tl::expected<Move, std::string_view> eval_move_input(const Player player, Board& board, const GameState game_state, const std::string_view input)
{
    assert(is_lowercase(input));

    if (input.size() < 3 || input.size() > 5)
        return tl::unexpected("invalid input");

    // check for castling input or normal moves
    const auto move = (input.starts_with("0-0") || input.starts_with("o-o")) ? check_castling_move_input(player, input) : check_normal_move_input(player, board, input);

    if (!move)
        return move;

    const auto pseudo_legal_moves = list_moves(board, player);

    if (std::find(pseudo_legal_moves.begin(), pseudo_legal_moves.end(), *move) == pseudo_legal_moves.end())
        return tl::unexpected("illegal move");

    if (const auto legal = check_legal_move(board, game_state, *move); legal != MoveLegality::ok)
        return tl::unexpected(print_move_legality(legal));

    return move;
}

}  // namespace chess
