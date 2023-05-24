#include "catch2/catch_test_macros.hpp"

#include "../src/move_generator/game_state.hpp"

namespace chess {

TEST_CASE("move_generator/game_state")
{
    SECTION("a default constructed GameState has no flags/values set")
    {
        const GameState game_state;

        CHECK(game_state.halfmove_clock == 0);
        CHECK(game_state.fullmove_counter == 1);
        CHECK(game_state.castling_ability == CastlingAbility{});
        CHECK(game_state.en_passant_target_square.has_value() == false);
    }

    SECTION("comparison")
    {
        const GameState game_state;

        CHECK(game_state == GameState{});
        CHECK((game_state != GameState{}) == false);

        CHECK(game_state != GameState{10, 1, CastlingAbility{}, std::nullopt});
        CHECK((game_state == GameState{10, 1, CastlingAbility{}, std::nullopt}) == false);
        CHECK(game_state != GameState{0, 10, CastlingAbility{}, std::nullopt});
        CHECK((game_state == GameState{0, 10, CastlingAbility{}, std::nullopt}) == false);

        CHECK(GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}});
        CHECK((GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}}) == false);

        CHECK(GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"e6"}});
        CHECK((GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"e6"}}) == false);
        CHECK(GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} != GameState{0, 1, CastlingAbility{CastlingRight::black_queen}, Square{"a3"}});
        CHECK((GameState{0, 1, CastlingAbility{CastlingRight::white_king}, Square{"a3"}} == GameState{0, 1, CastlingAbility{CastlingRight::black_queen}, Square{"a3"}}) == false);
    }

    SECTION("update_game_state()")
    {
        SECTION("halfmove clock")
        {
            GameState game_state{10, 50, CastlingAbility{}, std::nullopt};

            SECTION("reset to zero after a capture")
            {
                SECTION("normal capture")
                {
                    game_state = update_game_state(game_state, Move::create_capture({"d3"}, {"e4"}, Piece{'B'}, Piece{'p'}));
                    CHECK(game_state.halfmove_clock == 0);

                    game_state = update_game_state(game_state, Move::create_capture({"f5"}, {"f4"}, Piece{'r'}, Piece{'N'}));
                    CHECK(game_state.halfmove_clock == 0);
                }

                SECTION("capture and promotion")
                {
                    game_state = update_game_state(game_state, Move::create_capture_and_promotion(Square{"g7"}, Square{"h8"}, Piece{'Q'}, Piece{'r'}));
                    CHECK(game_state.halfmove_clock == 0);
                }

                SECTION("en passant")
                {
                    game_state = update_game_state(game_state, Move::create_en_passant(Square{"d5"}, Square{"e6"}, Piece{'P'}));
                    CHECK(game_state.halfmove_clock == 0);
                }
            }

            SECTION("reset to zero after a pawn move")
            {
                game_state = update_game_state(game_state, Move::create_normal({"a7"}, {"a6"}, Piece{'p'}));
                CHECK(game_state.halfmove_clock == 0);

                game_state = update_game_state(game_state, Move::create_normal({"a2"}, {"a3"}, Piece{'P'}));
                CHECK(game_state.halfmove_clock == 0);
            }

            SECTION("increment otherwise")
            {
                game_state = update_game_state(game_state, Move::create_normal({"a1"}, {"a3"}, Piece{'R'}));
                CHECK(game_state.halfmove_clock == 11);

                game_state = update_game_state(game_state, Move::create_normal({"c7"}, {"b6"}, Piece{'b'}));
                CHECK(game_state.halfmove_clock == 12);
            }
        }

        SECTION("fullmove counter")
        {
            GameState game_state;

            SECTION("incremented after Black move")
            {
                game_state = update_game_state(game_state, Move::create_normal({"a7"}, {"a6"}, Piece{'p'}));
                CHECK(game_state.fullmove_counter == 2);

                game_state = update_game_state(game_state, Move::create_normal({"b7"}, {"b6"}, Piece{'p'}));
                CHECK(game_state.fullmove_counter == 3);

                game_state = update_game_state(game_state, Move::create_normal({"c7"}, {"c6"}, Piece{'p'}));
                CHECK(game_state.fullmove_counter == 4);
            }

            SECTION("not incremented after White move")
            {
                game_state = update_game_state(game_state, Move::create_normal({"a2"}, {"a3"}, Piece{'P'}));
                CHECK(game_state.fullmove_counter == 1);

                game_state = update_game_state(game_state, Move::create_normal({"b2"}, {"b3"}, Piece{'P'}));
                CHECK(game_state.fullmove_counter == 1);

                game_state = update_game_state(game_state, Move::create_normal({"c2"}, {"c3"}, Piece{'P'}));
                CHECK(game_state.fullmove_counter == 1);
            }
        }

        SECTION("castling ability")
        {
            const auto all_castling_rights = CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen};

            SECTION("clear all castling rights after king moved")
            {
                SECTION("white")
                {
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"e1"}, {"f1"}, Piece{'K'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"e1"}, {"f1"}, Piece{'K'})).castling_ability == CastlingAbility{CastlingRight::black_king, CastlingRight::black_queen});
                }

                SECTION("black")
                {
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"e8"}, {"f8"}, Piece{'k'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"e8"}, {"f8"}, Piece{'k'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen});
                }
            }

            SECTION("rook moved")
            {
                SECTION("clear castling right on one side after rook moved from its starting position")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"a1"}, {"a3"}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"h1"}, {"h3"}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"a1"}, {"a3"}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"h1"}, {"h3"}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"a8"}, {"a6"}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"h8"}, {"h6"}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"a8"}, {"a6"}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"h8"}, {"h6"}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen});
                    }
                }

                SECTION("don't change castling rights after a rook moved somewhere else on the board")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'R'})).castling_ability == all_castling_rights);
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'R'})).castling_ability == all_castling_rights);
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"a4"}, {"h4"}, Piece{'r'})).castling_ability == all_castling_rights);
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"h4"}, {"a4"}, Piece{'r'})).castling_ability == all_castling_rights);
                    }
                }
            }

            SECTION("rook captured")
            {
                SECTION("clear castling right on one side after rook was captured (on its starting position)")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"a2"}, {"a1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"h2"}, {"h1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"a2"}, {"a1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"h2"}, {"h1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});

                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"b2"}, {"a1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"g2"}, {"h1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"b2"}, {"a1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::black_king, CastlingRight::black_queen});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"g2"}, {"h1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{CastlingRight::white_queen, CastlingRight::black_king, CastlingRight::black_queen});
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"a7"}, {"a8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"h7"}, {"h8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"a7"}, {"a8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"h7"}, {"h8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen});

                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"b7"}, {"a8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"g7"}, {"h8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"b7"}, {"a8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_king});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"g7"}, {"h8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{CastlingRight::white_king, CastlingRight::white_queen, CastlingRight::black_queen});
                    }
                }

                SECTION("don't change castling rights after a rook was captured somewhere else on the board")
                {
                    SECTION("white")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'q'}, Piece{'R'})).castling_ability == all_castling_rights);
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'q'}, Piece{'R'})).castling_ability == all_castling_rights);

                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"c1"}, Piece{'q'}, Piece{'R'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"c1"}, Piece{'q'}, Piece{'R'})).castling_ability == all_castling_rights);
                    }

                    SECTION("black")
                    {
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"b4"}, {"a4"}, Piece{'Q'}, Piece{'r'})).castling_ability == all_castling_rights);
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"g4"}, {"h4"}, Piece{'Q'}, Piece{'r'})).castling_ability == all_castling_rights);

                        CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"c8"}, Piece{'Q'}, Piece{'r'})).castling_ability == CastlingAbility{});
                        CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"c8"}, Piece{'Q'}, Piece{'r'})).castling_ability == all_castling_rights);
                    }
                }
            }

            SECTION("don't change castling rights after other pieces move")
            {
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})).castling_ability == CastlingAbility{});
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})).castling_ability == CastlingAbility{});
                CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})).castling_ability == all_castling_rights);
                CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})).castling_ability == all_castling_rights);
            }

            SECTION("don't change castling rights after a promotion to rook")
            {
                SECTION("white")
                {
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_promotion({"d7"}, {"d8"}, Piece{'R'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"e8"}, Piece{'R'}, Piece{'b'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_promotion({"d7"}, {"d8"}, Piece{'R'})).castling_ability == all_castling_rights);
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d7"}, {"e8"}, Piece{'R'}, Piece{'b'})).castling_ability == all_castling_rights);
                }

                SECTION("black")
                {
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_promotion({"d2"}, {"d1"}, Piece{'r'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"e1"}, Piece{'r'}, Piece{'B'})).castling_ability == CastlingAbility{});
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_promotion({"d2"}, {"d1"}, Piece{'r'})).castling_ability == all_castling_rights);
                    CHECK(update_game_state(GameState{0, 1, all_castling_rights, std::nullopt}, Move::create_capture_and_promotion({"d2"}, {"e1"}, Piece{'r'}, Piece{'B'})).castling_ability == all_castling_rights);
                }
            }
        }

        SECTION("en passant")
        {
            SECTION("set en passant target square after a pawn moved two spaces from its starting position")
            {
                CHECK(update_game_state(GameState{}, Move::create_normal({"d7"}, {"d5"}, Piece{'p'})).en_passant_target_square == Square{"d6"});
                CHECK(update_game_state(GameState{}, Move::create_normal({"b2"}, {"b4"}, Piece{'P'})).en_passant_target_square == Square{"b3"});
            }

            SECTION("clear en passant target square after pawn moved only one square")
            {
                // pawn moved from starting position
                CHECK(update_game_state(GameState{}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{}, Move::create_normal({"b2"}, {"b3"}, Piece{'P'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_normal({"d7"}, {"d6"}, Piece{'p'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_normal({"b2"}, {"b3"}, Piece{'P'})).en_passant_target_square == std::nullopt);

                // pawn moved from another rank on the board
                CHECK(update_game_state(GameState{}, Move::create_normal({"d4"}, {"d3"}, Piece{'p'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{}, Move::create_normal({"a6"}, {"a7"}, Piece{'P'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_normal({"d4"}, {"d3"}, Piece{'p'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_normal({"a6"}, {"a7"}, Piece{'P'})).en_passant_target_square == std::nullopt);
            }

            SECTION("clear en passant target square after non-pawn moves")
            {
                CHECK(update_game_state(GameState{}, Move::create_normal({"a1"}, {"a8"}, Piece{'R'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_normal({"a1"}, {"a8"}, Piece{'R'})).en_passant_target_square == std::nullopt);

                CHECK(update_game_state(GameState{}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})).en_passant_target_square == std::nullopt);
                CHECK(update_game_state(GameState{0, 1, CastlingAbility{}, Square{"a3"}}, Move::create_capture({"e4"}, {"d6"}, Piece{'n'}, Piece{'P'})).en_passant_target_square == std::nullopt);
            }
        }
    }
}

}  // namespace chess
