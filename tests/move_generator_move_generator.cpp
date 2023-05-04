#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/move_generator.hpp"

namespace chess {

TEST_CASE("move_generator/move_generator")
{
    SECTION("generate_move()")
    {
        Board board = Board::create_from_letter_data({
            "----k---",
            "--pp----",
            "--------",
            "--------",
            "--------",
            "--------",
            "--PP----",
            "----K---",
        });
        const auto move = generate_move(board, Player::white);

        REQUIRE(move.has_value());
        CHECK(move->piece.player == Player::white);
    }
}

}  // namespace chess
