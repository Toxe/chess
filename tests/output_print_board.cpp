#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/notation/fen.hpp"
#include "../src/output/print_board.hpp"

namespace chess {

TEST_CASE("output/print_board")
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

}  // namespace chess
