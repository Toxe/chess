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

    SECTION("construct with col/row")
    {
        CHECK(Square{0, 0}.col() == 0);
        CHECK(Square{0, 0}.row() == 0);

        CHECK(Square{2, 1}.col() == 2);
        CHECK(Square{2, 1}.row() == 1);

        CHECK(Square{1, 2}.col() == 1);
        CHECK(Square{1, 2}.row() == 2);

        CHECK(Square{7, 7}.col() == 7);
        CHECK(Square{7, 7}.row() == 7);
    }

    SECTION("construct with text notation")
    {
        CHECK(Square{"a1"}.col() == 0);
        CHECK(Square{"a1"}.row() == 7);

        CHECK(Square{"c7"}.col() == 2);
        CHECK(Square{"c7"}.row() == 1);

        CHECK(Square{"h8"}.col() == 7);
        CHECK(Square{"h8"}.row() == 0);
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
