#include "catch2/catch_test_macros.hpp"

#include "../src/board/square.hpp"

namespace chess {

TEST_CASE("game/square")
{
    SECTION("default construct")
    {
        const Square square;

        CHECK(square.col() == 0);
        CHECK(square.row() == 0);
    }

    SECTION("construct")
    {
        const Square square{2, 1};

        CHECK(square.col() == 2);
        CHECK(square.row() == 1);
    }

    SECTION("row and column must be between 0 to 7")
    {
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                const Square square{col, row};
                CHECK(square.col() == col);
                CHECK(square.row() == row);
            }
        }
    }
}

}  // namespace chess
