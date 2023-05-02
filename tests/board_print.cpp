#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/board/print.hpp"
#include "../src/notation/fen.hpp"

namespace chess {

TEST_CASE("board/print")
{
    SECTION("print_square()")
    {
        CHECK_THAT(print_square({0, 0}), Catch::Matchers::Equals("a8"));  // eighth rank
        CHECK_THAT(print_square({1, 0}), Catch::Matchers::Equals("b8"));
        CHECK_THAT(print_square({6, 0}), Catch::Matchers::Equals("g8"));
        CHECK_THAT(print_square({7, 0}), Catch::Matchers::Equals("h8"));

        CHECK_THAT(print_square({0, 1}), Catch::Matchers::Equals("a7"));  // seventh rank
        CHECK_THAT(print_square({1, 1}), Catch::Matchers::Equals("b7"));
        CHECK_THAT(print_square({6, 1}), Catch::Matchers::Equals("g7"));
        CHECK_THAT(print_square({7, 1}), Catch::Matchers::Equals("h7"));

        CHECK_THAT(print_square({0, 6}), Catch::Matchers::Equals("a2"));  // second rank
        CHECK_THAT(print_square({1, 6}), Catch::Matchers::Equals("b2"));
        CHECK_THAT(print_square({6, 6}), Catch::Matchers::Equals("g2"));
        CHECK_THAT(print_square({7, 6}), Catch::Matchers::Equals("h2"));

        CHECK_THAT(print_square({0, 7}), Catch::Matchers::Equals("a1"));  // first rank
        CHECK_THAT(print_square({1, 7}), Catch::Matchers::Equals("b1"));
        CHECK_THAT(print_square({6, 7}), Catch::Matchers::Equals("g1"));
        CHECK_THAT(print_square({7, 7}), Catch::Matchers::Equals("h1"));

        CHECK_THAT(print_square({"a8"}), Catch::Matchers::Equals("a8"));  // eighth rank
        CHECK_THAT(print_square({"b8"}), Catch::Matchers::Equals("b8"));
        CHECK_THAT(print_square({"g8"}), Catch::Matchers::Equals("g8"));
        CHECK_THAT(print_square({"h8"}), Catch::Matchers::Equals("h8"));

        CHECK_THAT(print_square({"a7"}), Catch::Matchers::Equals("a7"));  // seventh rank
        CHECK_THAT(print_square({"b7"}), Catch::Matchers::Equals("b7"));
        CHECK_THAT(print_square({"g7"}), Catch::Matchers::Equals("g7"));
        CHECK_THAT(print_square({"h7"}), Catch::Matchers::Equals("h7"));

        CHECK_THAT(print_square({"a2"}), Catch::Matchers::Equals("a2"));  // second rank
        CHECK_THAT(print_square({"b2"}), Catch::Matchers::Equals("b2"));
        CHECK_THAT(print_square({"g2"}), Catch::Matchers::Equals("g2"));
        CHECK_THAT(print_square({"h2"}), Catch::Matchers::Equals("h2"));

        CHECK_THAT(print_square({"a1"}), Catch::Matchers::Equals("a1"));  // first rank
        CHECK_THAT(print_square({"b1"}), Catch::Matchers::Equals("b1"));
        CHECK_THAT(print_square({"g1"}), Catch::Matchers::Equals("g1"));
        CHECK_THAT(print_square({"h1"}), Catch::Matchers::Equals("h1"));
    }

    SECTION("print_board()")
    {
        SECTION("empty board")
        {
            const std::string s = "\n"
                                  "┌────────────────────────────┐\n"
                                  "│8  ███   ███   ███   ███    │\n"
                                  "│7     ███   ███   ███   ███ │\n"
                                  "│6  ███   ███   ███   ███    │\n"
                                  "│5     ███   ███   ███   ███ │\n"
                                  "│4  ███   ███   ███   ███    │\n"
                                  "│3     ███   ███   ███   ███ │\n"
                                  "│2  ███   ███   ███   ███    │\n"
                                  "│1     ███   ███   ███   ███ │\n"
                                  "│                            │\n"
                                  "│    a  b  c  d  e  f  g  h  │\n"
                                  "└────────────────────────────┘\n"
                                  "\n";

            const Board board;

            CHECK_THAT(print_board(board), Catch::Matchers::Equals(s));
        }

        SECTION("board with default pieces")
        {
            const std::string s = "\n"
                                  "┌────────────────────────────┐\n"
                                  "│8  ▌♖▐ ♘ ▌♗▐ ♕ ▌♔▐ ♗ ▌♘▐ ♖  │\n"
                                  "│7   ♙ ▌♙▐ ♙ ▌♙▐ ♙ ▌♙▐ ♙ ▌♙▐ │\n"
                                  "│6  ███   ███   ███   ███    │\n"
                                  "│5     ███   ███   ███   ███ │\n"
                                  "│4  ███   ███   ███   ███    │\n"
                                  "│3     ███   ███   ███   ███ │\n"
                                  "│2  ▌♟▐ ♟ ▌♟▐ ♟ ▌♟▐ ♟ ▌♟▐ ♟  │\n"
                                  "│1   ♜ ▌♞▐ ♝ ▌♛▐ ♚ ▌♝▐ ♞ ▌♜▐ │\n"
                                  "│                            │\n"
                                  "│    a  b  c  d  e  f  g  h  │\n"
                                  "└────────────────────────────┘\n"
                                  "\n";

            const Board board = Board::create_with_default_pieces();

            CHECK_THAT(print_board(board), Catch::Matchers::Equals(s));
        }

        SECTION("board from FEN")
        {
            const std::string s = "\n"
                                  "┌────────────────────────────┐\n"
                                  "│8  ███ ♔ ███ ♖ ███   ███ ♖  │\n"
                                  "│7   ♙ ▌♙▐   ███   ███ ♙ ▌♙▐ │\n"
                                  "│6  ███   ███   ███   ███    │\n"
                                  "│5     ███ ♙ ▌♙▐   ▌♙▐ ♕ ███ │\n"
                                  "│4  ███   ███   ███   ███    │\n"
                                  "│3   ♟ ███   ███   ███   ███ │\n"
                                  "│2  ▌♟▐ ♜ ▌♟▐   ███ ♟ ███ ♟  │\n"
                                  "│1     ▌♛▐   ███   ▌♜▐   ▌♚▐ │\n"
                                  "│                            │\n"
                                  "│    a  b  c  d  e  f  g  h  │\n"
                                  "└────────────────────────────┘\n"
                                  "\n";

            const auto fen = read_FEN("1k1r3r/pp4pp/8/2pp1pq1/8/P7/PRP2P1P/1Q3R1K b - - 0 18");

            CHECK_THAT(print_board(fen.board), Catch::Matchers::Equals(s));
        }
    }
}

}  // namespace chess
