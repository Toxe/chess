#include "catch2/catch_test_macros.hpp"

#include "../src/board/square.hpp"

namespace chess {

TEST_CASE("board/square")
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

        CHECK(Square{-1, -2}.col() == -1);
        CHECK(Square{-1, -2}.row() == -2);
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

    SECTION("check if Square coordinates would be on a board")
    {
        CHECK(Square{0, 0}.on_board());
        CHECK(Square{0, 7}.on_board());
        CHECK(Square{7, 0}.on_board());
        CHECK(Square{7, 7}.on_board());
        CHECK(Square{-1, 0}.on_board() == false);
        CHECK(Square{0, -1}.on_board() == false);
        CHECK(Square{8, 0}.on_board() == false);
        CHECK(Square{0, 8}.on_board() == false);
    }

    SECTION("read_square()")
    {
        CHECK(read_square("a1") == Square{0, 7});
        CHECK(read_square("c7") == Square{2, 1});
        CHECK(read_square("h8") == Square{7, 0});

        CHECK(read_square("") == std::nullopt);
        CHECK(read_square("?") == std::nullopt);
        CHECK(read_square("b") == std::nullopt);
        CHECK(read_square("2") == std::nullopt);
        CHECK(read_square("bb") == std::nullopt);
        CHECK(read_square("22") == std::nullopt);
        CHECK(read_square("2b") == std::nullopt);
        CHECK(read_square("xy") == std::nullopt);
        CHECK(read_square("?!") == std::nullopt);
        CHECK(read_square("abc") == std::nullopt);
        CHECK(read_square("b2c") == std::nullopt);
        CHECK(read_square("b2c3") == std::nullopt);
    }
}

}  // namespace chess
