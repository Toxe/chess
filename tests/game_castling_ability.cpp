#include "catch2/catch_test_macros.hpp"

#include "../src/game/castling_ability.hpp"

namespace chess {

TEST_CASE("game/castling_ability")
{
    SECTION("a default constructed CastlingAbility has no flags set")
    {
        const CastlingAbility castling_ability;

        CHECK(castling_ability.has(CastlingRight::white_king) == false);
        CHECK(castling_ability.has(CastlingRight::white_queen) == false);
        CHECK(castling_ability.has(CastlingRight::black_king) == false);
        CHECK(castling_ability.has(CastlingRight::black_queen) == false);
    }

    SECTION("can construct CastlingAbility with initializer list")
    {
        CastlingAbility castling_ability{};

        CHECK(castling_ability == CastlingAbility{});

        castling_ability.set(CastlingRight::white_king);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king});

        castling_ability.set(CastlingRight::white_queen);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen});

        castling_ability.set(CastlingRight::black_king);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king});

        castling_ability.set(CastlingRight::black_queen);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});
    }

    SECTION("can clear flags")
    {
        CastlingAbility castling_ability{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen};

        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});

        castling_ability.clear(CastlingRight::black_king);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen});

        castling_ability.clear(CastlingRight::white_queen);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::black_queen});

        castling_ability.clear(CastlingRight::white_king);
        CHECK(castling_ability == CastlingAbility{CastlingRight::black_queen});

        castling_ability.clear(CastlingRight::black_queen);
        CHECK(castling_ability == CastlingAbility{});
    }

    SECTION("comparison")
    {
        CastlingAbility castling_ability;

        CHECK(castling_ability == CastlingAbility{});
        CHECK((castling_ability != CastlingAbility{}) == false);
        CHECK(castling_ability != CastlingAbility{CastlingRight::black_king});
        CHECK((castling_ability == CastlingAbility{CastlingRight::black_king}) == false);

        castling_ability.set(CastlingRight::black_king);

        CHECK(castling_ability != CastlingAbility{});
        CHECK((castling_ability == CastlingAbility{}) == false);
        CHECK(castling_ability == CastlingAbility{CastlingRight::black_king});
        CHECK((castling_ability != CastlingAbility{CastlingRight::black_king}) == false);

        castling_ability.set(CastlingRight::white_king);

        CHECK(castling_ability != CastlingAbility{});
        CHECK((castling_ability == CastlingAbility{}) == false);
        CHECK(castling_ability != CastlingAbility{CastlingRight::black_king});
        CHECK((castling_ability == CastlingAbility{CastlingRight::black_king}) == false);
        CHECK(castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::black_king});
        CHECK((castling_ability != CastlingAbility{CastlingRight::white_king, CastlingRight::black_king}) == false);
    }
}

}  // namespace chess
