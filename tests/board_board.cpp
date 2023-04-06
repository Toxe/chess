#include "catch2/catch_test_macros.hpp"

#include "../src/board/board.hpp"

namespace chess {

TEST_CASE("game/board")
{
    SECTION("a new Board is empty")
    {
        const Board board;

        for (int row = 0; row < board.rows(); ++row)
            for (int col = 0; col < board.cols(); ++col)
                CHECK(board.empty_square({col, row}));
    }

    SECTION("cols() returns the number of columns")
    {
        CHECK(Board{}.cols() == 8);
    }

    SECTION("rows() returns the number of rows")
    {
        CHECK(Board{}.rows() == 8);
    }
}

}  // namespace chess
