#include "catch2/catch_test_macros.hpp"

#include "../src/board/rank.hpp"

namespace chess {

TEST_CASE("board/rank")
{
    SECTION("nth_rank()")
    {
        CHECK(nth_rank(Player::black, 1) == 0);
        CHECK(nth_rank(Player::black, 2) == 1);
        CHECK(nth_rank(Player::black, 7) == 6);
        CHECK(nth_rank(Player::black, 8) == 7);

        CHECK(nth_rank(Player::white, 1) == 7);
        CHECK(nth_rank(Player::white, 2) == 6);
        CHECK(nth_rank(Player::white, 7) == 1);
        CHECK(nth_rank(Player::white, 8) == 0);
    }

    SECTION("on_home_rank()")
    {
        CHECK(on_home_rank(Player::black, Square{"a8"}));
        CHECK(on_home_rank(Player::white, Square{"a1"}));

        CHECK(on_home_rank(Player::black, Square{"a7"}) == false);
        CHECK(on_home_rank(Player::black, Square{"a6"}) == false);
        CHECK(on_home_rank(Player::black, Square{"a2"}) == false);
        CHECK(on_home_rank(Player::black, Square{"a1"}) == false);
        CHECK(on_home_rank(Player::white, Square{"a2"}) == false);
        CHECK(on_home_rank(Player::white, Square{"a3"}) == false);
        CHECK(on_home_rank(Player::white, Square{"a7"}) == false);
        CHECK(on_home_rank(Player::white, Square{"a8"}) == false);
    }

    SECTION("on_second_rank()")
    {
        CHECK(on_second_rank(Player::black, Square{"a7"}));
        CHECK(on_second_rank(Player::white, Square{"a2"}));

        CHECK(on_second_rank(Player::black, Square{"a8"}) == false);
        CHECK(on_second_rank(Player::black, Square{"a6"}) == false);
        CHECK(on_second_rank(Player::black, Square{"a2"}) == false);
        CHECK(on_second_rank(Player::black, Square{"a1"}) == false);
        CHECK(on_second_rank(Player::white, Square{"a1"}) == false);
        CHECK(on_second_rank(Player::white, Square{"a3"}) == false);
        CHECK(on_second_rank(Player::white, Square{"a7"}) == false);
        CHECK(on_second_rank(Player::white, Square{"a8"}) == false);
    }
}

}  // namespace chess
