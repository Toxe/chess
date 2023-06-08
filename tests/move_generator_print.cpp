#include "catch2/catch_test_macros.hpp"

#include "../src/game/print.hpp"
#include "../src/move_generator/print.hpp"

namespace chess {

TEST_CASE("move_generator/print")
{
    SECTION("print_game_state()")
    {
        CHECK(print_game_state(GameState{}) == "- - 0 1");
        CHECK(print_game_state(GameState{0, 1, CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt}) == "KQkq - 0 1");
        CHECK(print_game_state(GameState{10, 20, CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king}, Square{"e3"}}) == "Qk e3 10 20");
    }

    SECTION("print_move_legality()")
    {
        CHECK(print_move_legality(MoveLegality::ok) == "ok");
        CHECK(print_move_legality(MoveLegality::en_passant_target_square_not_set) == "illegal move: no en passant target square");
        CHECK(print_move_legality(MoveLegality::en_passant_target_square_wrong) == "illegal move: wrong en passant target square");
        CHECK(print_move_legality(MoveLegality::check) == "illegal move: check");
        CHECK(print_move_legality(MoveLegality::would_result_in_check) == "illegal move: would result in check");
        CHECK(print_move_legality(MoveLegality::square_under_attack) == "illegal move: king would pass through or finish on a square that is under attack");
        CHECK(print_move_legality(MoveLegality::no_castling_ability) == "illegal move: no castling ability");
    }
}

}  // namespace chess
