#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/game_state.hpp"

namespace chess {

TEST_CASE("move_generator/game_state")
{
    SECTION("a default constructed GameState has no flags/values set")
    {
        const GameState game_state;

        CHECK(game_state.castling_ability == CastlingAbility{});
        CHECK(game_state.en_passant_target_square.has_value() == false);
    }

    SECTION("comparison")
    {
        const GameState game_state;

        CHECK(game_state == GameState{});
        CHECK((game_state != GameState{}) == false);

        CHECK(GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}});
        CHECK((GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}}) == false);

        CHECK(GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{CastlingAbility{CastlingRight::white_king}, Square{"e6"}});
        CHECK((GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{CastlingAbility{CastlingRight::white_king}, Square{"e6"}}) == false);
        CHECK(GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{CastlingAbility{CastlingRight::black_queen}, Square{"a3"}});
        CHECK((GameState{CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{CastlingAbility{CastlingRight::black_queen}, Square{"a3"}}) == false);
    }

    SECTION("update_game_state()")
    {
        SECTION("castling ability")
        {
            const auto all_castling_rights = CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen};

            SECTION("clear all castling rights after king moved")
            {
                SECTION("white")
                {
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"e1"}, {"f1"}, Piece{'K'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"e1"}, {"f1"}, Piece{'K'})) == GameState{CastlingAbility{CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                }

                SECTION("black")
                {
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"e8"}, {"f8"}, Piece{'k'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"e8"}, {"f8"}, Piece{'k'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen}, std::nullopt});
                }
            }

            SECTION("rook moved")
            {
                SECTION("clear castling right on one side after rook moved from its starting position")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"a1"}, {"a3"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"h1"}, {"h3"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"a1"}, {"a3"}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"h1"}, {"h3"}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"a8"}, {"a6"}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"h8"}, {"h6"}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"a8"}, {"a6"}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"h8"}, {"h6"}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen}, std::nullopt});
                    }
                }

                SECTION("don't change castling rights after a rook moved somewhere else on the board")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});
                    }
                }
            }

            SECTION("rook captured")
            {
                SECTION("clear castling right on one side after rook was captured (on its starting position)")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"a2"}, {"a1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"h2"}, {"h1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"a2"}, {"a1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"h2"}, {"h1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});

                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"b2"}, {"a1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"g2"}, {"h1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"b2"}, {"a1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"g2"}, {"h1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen}, std::nullopt});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"a7"}, {"a8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"h7"}, {"h8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"a7"}, {"a8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"h7"}, {"h8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen}, std::nullopt});

                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"b7"}, {"a8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"g7"}, {"h8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"b7"}, {"a8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"g7"}, {"h8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen}, std::nullopt});
                    }
                }

                SECTION("don't change castling rights after a rook was captured somewhere else on the board")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'q'}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'q'}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});

                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"c1"}, Piece{'q'}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"c1"}, Piece{'q'}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'Q'}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'Q'}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});

                        CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"c8"}, Piece{'Q'}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                        CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"c8"}, Piece{'Q'}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});
                    }
                }
            }

            SECTION("don't change castling rights after other pieces move")
            {
                CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})) == GameState{all_castling_rights, std::nullopt});
                CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})) == GameState{all_castling_rights, std::nullopt});
            }

            SECTION("don't change castling rights after a promotion to rook")
            {
                SECTION("white")
                {
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_promotion({"d7"}, {"d8"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"e8"}, Piece{'R'}, Piece{'b'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_promotion({"d7"}, {"d8"}, Piece{'R'})) == GameState{all_castling_rights, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"e8"}, Piece{'R'}, Piece{'b'})) == GameState{all_castling_rights, std::nullopt});
                }

                SECTION("black")
                {
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_promotion({"d2"}, {"d1"}, Piece{'r'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"e1"}, Piece{'r'}, Piece{'B'})) == GameState{CastlingAbility{}, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_promotion({"d2"}, {"d1"}, Piece{'r'})) == GameState{all_castling_rights, std::nullopt});
                    CHECK(update_game_state(GameState{all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"e1"}, Piece{'r'}, Piece{'B'})) == GameState{all_castling_rights, std::nullopt});
                }
            }
        }

        SECTION("en passant")
        {
            SECTION("set en passant target square after a pawn moved two spaces from its starting position")
            {
                CHECK(update_game_state(GameState{}, Move::create_normal({"d7"}, {"d5"}, Piece{'p'})) == GameState{CastlingAbility{}, Square{"d6"}});
                CHECK(update_game_state(GameState{}, Move::create_normal({"b2"}, {"b4"}, Piece{'P'})) == GameState{CastlingAbility{}, Square{"b3"}});
            }

            SECTION("clear en passant target square after pawn moved only one square")
            {
                // pawn moved from starting position
                CHECK(update_game_state(GameState{}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{}, Move::create_normal({"b2"}, {"b3"}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_normal({"b2"}, {"b3"}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});

                // pawn moved from another rank on the board
                CHECK(update_game_state(GameState{}, Move::create_normal({"d4"}, {"d3"}, Piece{'p'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{}, Move::create_normal({"a6"}, {"a7"}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_normal({"d4"}, {"d3"}, Piece{'p'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_normal({"a6"}, {"a7"}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
            }

            SECTION("clear en passant target square after non-pawn moves")
            {
                CHECK(update_game_state(GameState{}, Move::create_normal({"a1"}, {"a8"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_normal({"a1"}, {"a8"}, Piece{'R'})) == GameState{CastlingAbility{}, std::nullopt});

                CHECK(update_game_state(GameState{}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
                CHECK(update_game_state(GameState{CastlingAbility{}, Square{"a3"}}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})) == GameState{CastlingAbility{}, std::nullopt});
            }
        }
    }
}

}  // namespace chess
