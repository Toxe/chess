#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/game/print.hpp"
#include "../src/move_generator/print.hpp"

namespace chess {

TEST_CASE("move_generator/print")
{
    SECTION("print_game_state()")
    {
        CHECK_THAT(print_game_state(GameState{}), Catch::Matchers::Equals("- - 0 1"));
        CHECK_THAT(print_game_state(GameState{0, 1, CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt}), Catch::Matchers::Equals("KQkq - 0 1"));
        CHECK_THAT(print_game_state(GameState{10, 20, CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king}, Square{"e3"}}), Catch::Matchers::Equals("Qk e3 10 20"));
    }
}

}  // namespace chess
