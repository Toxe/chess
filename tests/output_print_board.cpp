#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/output/print_board.hpp"

namespace chess {

TEST_CASE("output/print_board")
{
    SECTION("empty board")
    {
        const std::string s = "\n"
                              "[Board]\n"
                              "\n";

        const Board board;

        CHECK_THAT(print_board(board), Catch::Matchers::Equals(s));
    }
}

}  // namespace chess
