#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_vector.hpp"

#include "../src/notation/fen.hpp"
#include "../src/notation/fen_detail.hpp"

namespace chess {

bool compare_boards(const Board& board1, const Board& board2)
{
    bool ok = true;

    for (int row = 0; row < board1.rows(); ++row) {
        for (int col = 0; col < board1.cols(); ++col) {
            const bool equal = board1.piece({col, row}) == board2.piece({col, row});

            if (ok && !equal)
                ok = false;

            CHECK(equal);
        }
    }

    return ok;
}

TEST_CASE("notation/fen")
{
    SECTION("read_FEN()")
    {
        SECTION("can read FEN lines")
        {
            const auto fen1 = read_FEN("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2");

            CHECK(compare_boards(
                fen1.board,
                Board::create_from_letter_data({
                    "rnbqkbnr",
                    "pp-ppppp",
                    "--------",
                    "--p-----",
                    "----P---",
                    "--------",
                    "PPPP-PPP",
                    "RNBQKBNR",
                })));

            CHECK(fen1.side_to_move == Player::white);
            CHECK(fen1.castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});
            CHECK(fen1.en_passant_target_square == Square{"c6"});
            CHECK(fen1.halfmove_clock == 0);
            CHECK(fen1.fullmove_counter == 2);

            const auto fen2 = read_FEN("1k1r3r/pp4pp/8/2pp1pq1/8/P7/PRP2P1P/1Q3R1K b - - 0 18");

            CHECK(compare_boards(
                fen2.board,
                Board::create_from_letter_data({
                    "-k-r---r",
                    "pp----pp",
                    "--------",
                    "--pp-pq-",
                    "--------",
                    "P-------",
                    "PRP--P-P",
                    "-Q---R-K",
                })));

            CHECK(fen2.side_to_move == Player::black);
            CHECK(fen2.castling_ability == CastlingAbility{});
            CHECK(fen2.en_passant_target_square == std::nullopt);
            CHECK(fen2.halfmove_clock == 0);
            CHECK(fen2.fullmove_counter == 18);
        }

        SECTION("throws exception for FEN lines that contain the wrong number of parts")
        {
            CHECK_THROWS(read_FEN("1 2 3 4 5"));
            CHECK_THROWS(read_FEN("1 2 3 4 5 6 7"));
        }
    }

    SECTION("detail")
    {
        SECTION("split_string()")
        {
            CHECK_THAT(detail::fen::split_string("aaa bbb ccc", ' '), Catch::Matchers::Equals(std::vector<std::string_view>{"aaa", "bbb", "ccc"}));
            CHECK_THAT(detail::fen::split_string("a b c", ' '), Catch::Matchers::Equals(std::vector<std::string_view>{"a", "b", "c"}));
            CHECK_THAT(detail::fen::split_string("aaa", ' '), Catch::Matchers::Equals(std::vector<std::string_view>{"aaa"}));
            CHECK_THAT(detail::fen::split_string("one:two:three", ':'), Catch::Matchers::Equals(std::vector<std::string_view>{"one", "two", "three"}));
            CHECK_THAT(detail::fen::split_string("1/2/3", '/'), Catch::Matchers::Equals(std::vector<std::string_view>{"1", "2", "3"}));

            CHECK_THROWS(detail::fen::split_string("aaa ", ' '));
            CHECK_THROWS(detail::fen::split_string("aaa   ", ' '));
            CHECK_THROWS(detail::fen::split_string(" aaa", ' '));
            CHECK_THROWS(detail::fen::split_string(" aaa ", ' '));
            CHECK_THROWS(detail::fen::split_string(" aaa bbb ", ' '));
            CHECK_THROWS(detail::fen::split_string("", ' '));
            CHECK_THROWS(detail::fen::split_string(" ", ' '));
            CHECK_THROWS(detail::fen::split_string("aaa   bbb   ccc", ' '));
        }

        SECTION("process_piece_placement()")
        {
            CHECK(compare_boards(
                detail::fen::process_piece_placement("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR"),
                Board::create_from_letter_data({
                    "rnbqkbnr",
                    "pppppppp",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "PPPPPPPP",
                    "RNBQKBNR",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR"),
                Board::create_from_letter_data({
                    "rnbqkbnr",
                    "pppppppp",
                    "--------",
                    "--------",
                    "----P---",
                    "--------",
                    "PPPP-PPP",
                    "RNBQKBNR",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR"),
                Board::create_from_letter_data({
                    "rnbqkbnr",
                    "pp-ppppp",
                    "--------",
                    "--p-----",
                    "----P---",
                    "--------",
                    "PPPP-PPP",
                    "RNBQKBNR",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R"),
                Board::create_from_letter_data({
                    "rnbqkbnr",
                    "pp-ppppp",
                    "--------",
                    "--p-----",
                    "----P---",
                    "-----N--",
                    "PPPP-PPP",
                    "RNBQKB-R",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("4k3/8/8/8/8/8/4P3/4K3"),
                Board::create_from_letter_data({
                    "----k---",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "--------",
                    "----P---",
                    "----K---",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("8/5k2/3p4/1p1Pp2p/pP2Pp1P/P4P1K/8/8"),
                Board::create_from_letter_data({
                    "--------",
                    "-----k--",
                    "---p----",
                    "-p-Pp--p",
                    "pP--Pp-P",
                    "P----P-K",
                    "--------",
                    "--------",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("r3k2r/p1pppppp/n7/8/8/8/P2PPPpP/R3K2R"),
                Board::create_from_letter_data({
                    "r---k--r",
                    "p-pppppp",
                    "n-------",
                    "--------",
                    "--------",
                    "--------",
                    "P--PPPpP",
                    "R---K--R",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("r1b1k2r/pp3ppp/5b2/K2p1n2/2N5/4nN2/Pp4qP/8"),
                Board::create_from_letter_data({
                    "r-b-k--r",
                    "pp---ppp",
                    "-----b--",
                    "K--p-n--",
                    "--N-----",
                    "----nN--",
                    "Pp----qP",
                    "--------",
                })));

            CHECK(compare_boards(
                detail::fen::process_piece_placement("1k1r3r/pp4pp/8/2pp1pq1/8/P7/PRP2P1P/1Q3R1K"),
                Board::create_from_letter_data({
                    "-k-r---r",
                    "pp----pp",
                    "--------",
                    "--pp-pq-",
                    "--------",
                    "P-------",
                    "PRP--P-P",
                    "-Q---R-K",
                })));

            CHECK_THROWS(detail::fen::process_piece_placement("8/8/8/8/8/8/8"));
            CHECK_THROWS(detail::fen::process_piece_placement("8/8/8/8/8/8/8/8/8"));
        }

        SECTION("process_side_to_move()")
        {
            CHECK(detail::fen::process_side_to_move("w") == Player::white);
            CHECK(detail::fen::process_side_to_move("b") == Player::black);

            CHECK_THROWS(detail::fen::process_side_to_move(""));
            CHECK_THROWS(detail::fen::process_side_to_move("-"));
            CHECK_THROWS(detail::fen::process_side_to_move("?"));
            CHECK_THROWS(detail::fen::process_side_to_move("W"));
            CHECK_THROWS(detail::fen::process_side_to_move("B"));
        }

        SECTION("process_castling_ability()")
        {
            CHECK(detail::fen::process_castling_ability("-") == CastlingAbility{});
            CHECK(detail::fen::process_castling_ability("k") == CastlingAbility{CastlingRight::black_king});
            CHECK(detail::fen::process_castling_ability("K") == CastlingAbility{CastlingRight::white_king});
            CHECK(detail::fen::process_castling_ability("q") == CastlingAbility{CastlingRight::black_queen});
            CHECK(detail::fen::process_castling_ability("Q") == CastlingAbility{CastlingRight::white_queen});
            CHECK(detail::fen::process_castling_ability("kq") == CastlingAbility{CastlingRight::black_king, CastlingRight::black_queen});
            CHECK(detail::fen::process_castling_ability("KQ") == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen});
            CHECK(detail::fen::process_castling_ability("KQkq") == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});

            CHECK_THROWS(detail::fen::process_castling_ability(""));
            CHECK_THROWS(detail::fen::process_castling_ability("abc"));
            CHECK_THROWS(detail::fen::process_castling_ability("kKabc"));
            CHECK_THROWS(detail::fen::process_castling_ability("qq"));
            CHECK_THROWS(detail::fen::process_castling_ability("kKqQ-"));
        }

        SECTION("process_en_passant_target_square()")
        {
            CHECK(detail::fen::process_en_passant_target_square("-") == std::nullopt);
            CHECK(detail::fen::process_en_passant_target_square("e3") == Square{"e3"});
            CHECK(detail::fen::process_en_passant_target_square("c6") == Square{"c6"});

            CHECK_THROWS(detail::fen::process_en_passant_target_square(""));
            CHECK_THROWS(detail::fen::process_en_passant_target_square("?"));
            CHECK_THROWS(detail::fen::process_en_passant_target_square("???"));
        }

        SECTION("process_halfmove_clock()")
        {
            CHECK(detail::fen::process_halfmove_clock("0") == 0);
            CHECK(detail::fen::process_halfmove_clock("1") == 1);
            CHECK(detail::fen::process_halfmove_clock("10") == 10);

            CHECK_THROWS(detail::fen::process_halfmove_clock(""));
            CHECK_THROWS(detail::fen::process_halfmove_clock("-1"));
            CHECK_THROWS(detail::fen::process_halfmove_clock("?"));
            CHECK_THROWS(detail::fen::process_halfmove_clock("abc"));
        }

        SECTION("process_fullmove_counter()")
        {
            CHECK(detail::fen::process_fullmove_counter("1") == 1);
            CHECK(detail::fen::process_fullmove_counter("10") == 10);

            CHECK_THROWS(detail::fen::process_fullmove_counter(""));
            CHECK_THROWS(detail::fen::process_fullmove_counter("-1"));
            CHECK_THROWS(detail::fen::process_fullmove_counter("0"));
            CHECK_THROWS(detail::fen::process_fullmove_counter("?"));
            CHECK_THROWS(detail::fen::process_fullmove_counter("abc"));
        }
    }
}

}  // namespace chess
