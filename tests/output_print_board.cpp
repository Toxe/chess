#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

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
}

}  // namespace chess
