#include "catch2/catch_test_macros.hpp"

#include "../src/notation/fen.hpp"
#include "../src/perft/perft.hpp"

namespace chess {

void check_perft_divide(const PerftDivide& perft_divide, const PerftDivide& example_perft_divide)
{
    CHECK(perft_divide.size() == example_perft_divide.size());
    CHECK(perft_divide.total_moves() == example_perft_divide.total_moves());

    for (const auto& move : example_perft_divide.moves()) {
        const bool has_move = perft_divide.has_move(move);

        INFO("move: " << move);
        CHECK(has_move);

        if (has_move)
            CHECK(perft_divide.move_count(move) == example_perft_divide.move_count(move));
    }
}

TEST_CASE("perft/perft")
{
    SECTION("the board does not change")
    {
        auto fen = read_FEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
        const auto board_backup = fen.board;
        PerftDivide perft_divide;

        CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) > 0);
        CHECK(fen.board == board_backup);
    }

    SECTION("example 1 (default board)")
    {
        auto board = Board::create_with_default_pieces();
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("a2a3: 1\n"
                                             "b2b3: 1\n"
                                             "c2c3: 1\n"
                                             "d2d3: 1\n"
                                             "e2e3: 1\n"
                                             "f2f3: 1\n"
                                             "g2g3: 1\n"
                                             "h2h3: 1\n"
                                             "a2a4: 1\n"
                                             "b2b4: 1\n"
                                             "c2c4: 1\n"
                                             "d2d4: 1\n"
                                             "e2e4: 1\n"
                                             "f2f4: 1\n"
                                             "g2g4: 1\n"
                                             "h2h4: 1\n"
                                             "b1a3: 1\n"
                                             "b1c3: 1\n"
                                             "g1f3: 1\n"
                                             "g1h3: 1\n");

            CHECK(perft(Player::white, board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("a2a3: 20\n"
                                             "b2b3: 20\n"
                                             "c2c3: 20\n"
                                             "d2d3: 20\n"
                                             "e2e3: 20\n"
                                             "f2f3: 20\n"
                                             "g2g3: 20\n"
                                             "h2h3: 20\n"
                                             "a2a4: 20\n"
                                             "b2b4: 20\n"
                                             "c2c4: 20\n"
                                             "d2d4: 20\n"
                                             "e2e4: 20\n"
                                             "f2f4: 20\n"
                                             "g2g4: 20\n"
                                             "h2h4: 20\n"
                                             "b1a3: 20\n"
                                             "b1c3: 20\n"
                                             "g1f3: 20\n"
                                             "g1h3: 20\n");

            CHECK(perft(Player::white, board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("a2a3: 380\n"
                                             "b2b3: 420\n"
                                             "c2c3: 420\n"
                                             "d2d3: 539\n"
                                             "e2e3: 599\n"
                                             "f2f3: 380\n"
                                             "g2g3: 420\n"
                                             "h2h3: 380\n"
                                             "a2a4: 420\n"
                                             "b2b4: 421\n"
                                             "c2c4: 441\n"
                                             "d2d4: 560\n"
                                             "e2e4: 600\n"
                                             "f2f4: 401\n"
                                             "g2g4: 421\n"
                                             "h2h4: 420\n"
                                             "b1a3: 400\n"
                                             "b1c3: 440\n"
                                             "g1f3: 440\n"
                                             "g1h3: 400\n");

            CHECK(perft(Player::white, board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 4")
        {
            PerftDivide example_perft_divide("a2a3: 8457\n"
                                             "b2b3: 9345\n"
                                             "c2c3: 9272\n"
                                             "d2d3: 11959\n"
                                             "e2e3: 13134\n"
                                             "f2f3: 8457\n"
                                             "g2g3: 9345\n"
                                             "h2h3: 8457\n"
                                             "a2a4: 9329\n"
                                             "b2b4: 9332\n"
                                             "c2c4: 9744\n"
                                             "d2d4: 12435\n"
                                             "e2e4: 13160\n"
                                             "f2f4: 8929\n"
                                             "g2g4: 9328\n"
                                             "h2h4: 9329\n"
                                             "b1a3: 8885\n"
                                             "b1c3: 9755\n"
                                             "g1f3: 9748\n"
                                             "g1h3: 8881\n");

            CHECK(perft(Player::white, board, perft_divide, 4) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }
    }

    SECTION("example 2")
    {
        auto fen = read_FEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("a2a3: 1\n"
                                             "b2b3: 1\n"
                                             "g2g3: 1\n"
                                             "d5d6: 1\n"
                                             "a2a4: 1\n"
                                             "g2g4: 1\n"
                                             "g2h3: 1\n"
                                             "d5e6: 1\n"
                                             "c3b1: 1\n"
                                             "c3d1: 1\n"
                                             "c3a4: 1\n"
                                             "c3b5: 1\n"
                                             "e5d3: 1\n"
                                             "e5c4: 1\n"
                                             "e5g4: 1\n"
                                             "e5c6: 1\n"
                                             "e5g6: 1\n"
                                             "e5d7: 1\n"
                                             "e5f7: 1\n"
                                             "d2c1: 1\n"
                                             "d2e3: 1\n"
                                             "d2f4: 1\n"
                                             "d2g5: 1\n"
                                             "d2h6: 1\n"
                                             "e2d1: 1\n"
                                             "e2f1: 1\n"
                                             "e2d3: 1\n"
                                             "e2c4: 1\n"
                                             "e2b5: 1\n"
                                             "e2a6: 1\n"
                                             "a1b1: 1\n"
                                             "a1c1: 1\n"
                                             "a1d1: 1\n"
                                             "h1f1: 1\n"
                                             "h1g1: 1\n"
                                             "f3d3: 1\n"
                                             "f3e3: 1\n"
                                             "f3g3: 1\n"
                                             "f3h3: 1\n"
                                             "f3f4: 1\n"
                                             "f3g4: 1\n"
                                             "f3f5: 1\n"
                                             "f3h5: 1\n"
                                             "f3f6: 1\n"
                                             "e1d1: 1\n"
                                             "e1f1: 1\n"
                                             "e1g1: 1\n"
                                             "e1c1: 1\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("a2a3: 44\n"
                                             "b2b3: 42\n"
                                             "g2g3: 42\n"
                                             "d5d6: 41\n"
                                             "a2a4: 44\n"
                                             "g2g4: 42\n"
                                             "g2h3: 43\n"
                                             "d5e6: 46\n"
                                             "c3b1: 42\n"
                                             "c3d1: 42\n"
                                             "c3a4: 42\n"
                                             "c3b5: 39\n"
                                             "e5d3: 43\n"
                                             "e5c4: 42\n"
                                             "e5g4: 44\n"
                                             "e5c6: 41\n"
                                             "e5g6: 42\n"
                                             "e5d7: 45\n"
                                             "e5f7: 44\n"
                                             "d2c1: 43\n"
                                             "d2e3: 43\n"
                                             "d2f4: 43\n"
                                             "d2g5: 42\n"
                                             "d2h6: 41\n"
                                             "e2d1: 44\n"
                                             "e2f1: 44\n"
                                             "e2d3: 42\n"
                                             "e2c4: 41\n"
                                             "e2b5: 39\n"
                                             "e2a6: 36\n"
                                             "a1b1: 43\n"
                                             "a1c1: 43\n"
                                             "a1d1: 43\n"
                                             "h1f1: 43\n"
                                             "h1g1: 43\n"
                                             "f3d3: 42\n"
                                             "f3e3: 43\n"
                                             "f3g3: 43\n"
                                             "f3h3: 43\n"
                                             "f3f4: 43\n"
                                             "f3g4: 43\n"
                                             "f3f5: 45\n"
                                             "f3h5: 43\n"
                                             "f3f6: 39\n"
                                             "e1d1: 43\n"
                                             "e1f1: 43\n"
                                             "e1g1: 43\n"
                                             "e1c1: 43\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("a2a3: 2186\n"
                                             "b2b3: 1964\n"
                                             "g2g3: 1882\n"
                                             "d5d6: 1991\n"
                                             "a2a4: 2149\n"
                                             "g2g4: 1843\n"
                                             "g2h3: 1970\n"
                                             "d5e6: 2241\n"
                                             "c3b1: 2038\n"
                                             "c3d1: 2040\n"
                                             "c3a4: 2203\n"
                                             "c3b5: 2138\n"
                                             "e5d3: 1803\n"
                                             "e5c4: 1880\n"
                                             "e5g4: 1878\n"
                                             "e5c6: 2027\n"
                                             "e5g6: 1997\n"
                                             "e5d7: 2124\n"
                                             "e5f7: 2080\n"
                                             "d2c1: 1963\n"
                                             "d2e3: 2136\n"
                                             "d2f4: 2000\n"
                                             "d2g5: 2134\n"
                                             "d2h6: 2019\n"
                                             "e2d1: 1733\n"
                                             "e2f1: 2060\n"
                                             "e2d3: 2050\n"
                                             "e2c4: 2082\n"
                                             "e2b5: 2057\n"
                                             "e2a6: 1907\n"
                                             "a1b1: 1969\n"
                                             "a1c1: 1968\n"
                                             "a1d1: 1885\n"
                                             "h1f1: 1929\n"
                                             "h1g1: 2013\n"
                                             "f3d3: 2005\n"
                                             "f3e3: 2174\n"
                                             "f3g3: 2214\n"
                                             "f3h3: 2360\n"
                                             "f3f4: 2132\n"
                                             "f3g4: 2169\n"
                                             "f3f5: 2396\n"
                                             "f3h5: 2267\n"
                                             "f3f6: 2111\n"
                                             "e1d1: 1894\n"
                                             "e1f1: 1855\n"
                                             "e1g1: 2059\n"
                                             "e1c1: 1887\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }
    }

    SECTION("example 3")
    {
        auto fen = read_FEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("e2e3: 1\n"
                                             "g2g3: 1\n"
                                             "a5a6: 1\n"
                                             "e2e4: 1\n"
                                             "g2g4: 1\n"
                                             "b4b1: 1\n"
                                             "b4b2: 1\n"
                                             "b4b3: 1\n"
                                             "b4a4: 1\n"
                                             "b4c4: 1\n"
                                             "b4d4: 1\n"
                                             "b4e4: 1\n"
                                             "b4f4: 1\n"
                                             "a5a4: 1\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("e2e3: 15\n"
                                             "g2g3: 4\n"
                                             "a5a6: 15\n"
                                             "e2e4: 16\n"
                                             "g2g4: 17\n"
                                             "b4b1: 16\n"
                                             "b4b2: 16\n"
                                             "b4b3: 15\n"
                                             "b4a4: 15\n"
                                             "b4c4: 15\n"
                                             "b4d4: 15\n"
                                             "b4e4: 15\n"
                                             "b4f4: 2\n"
                                             "a5a4: 15\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("e2e3: 205\n"
                                             "g2g3: 54\n"
                                             "a5a6: 240\n"
                                             "e2e4: 177\n"
                                             "g2g4: 226\n"
                                             "b4b1: 265\n"
                                             "b4b2: 205\n"
                                             "b4b3: 248\n"
                                             "b4a4: 202\n"
                                             "b4c4: 254\n"
                                             "b4d4: 243\n"
                                             "b4e4: 228\n"
                                             "b4f4: 41\n"
                                             "a5a4: 224\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 4")
        {
            PerftDivide example_perft_divide("e2e3: 3107\n"
                                             "g2g3: 1014\n"
                                             "a5a6: 3653\n"
                                             "e2e4: 2748\n"
                                             "g2g4: 3702\n"
                                             "b4b1: 4199\n"
                                             "b4b2: 3328\n"
                                             "b4b3: 3658\n"
                                             "b4a4: 3019\n"
                                             "b4c4: 3797\n"
                                             "b4d4: 3622\n"
                                             "b4e4: 3391\n"
                                             "b4f4: 606\n"
                                             "a5a4: 3394\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 4) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }
    }

    SECTION("example 4")
    {
        auto fen = read_FEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("c4c5: 1\n"
                                             "d2d4: 1\n"
                                             "f3d4: 1\n"
                                             "b4c5: 1\n"
                                             "f1f2: 1\n"
                                             "g1h1: 1\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("c4c5: 43\n"
                                             "d2d4: 43\n"
                                             "f3d4: 45\n"
                                             "b4c5: 42\n"
                                             "f1f2: 45\n"
                                             "g1h1: 46\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("c4c5: 1409\n"
                                             "d2d4: 1643\n"
                                             "f3d4: 1687\n"
                                             "b4c5: 1352\n"
                                             "f1f2: 1623\n"
                                             "g1h1: 1753\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        // SECTION("depth 4")
        //{
        //     PerftDivide example_perft_divide("c4c5: 60769\n"
        //                                      "d2d4: 72051\n"
        //                                      "f3d4: 75736\n"
        //                                      "b4c5: 58167\n"
        //                                      "f1f2: 73972\n"
        //                                      "g1h1: 81638\n");

        //    CHECK(perft(fen.side_to_move, fen.board, perft_divide, 4) == example_perft_divide.total_moves());
        //    check_perft_divide(perft_divide, example_perft_divide);
        //}
    }

    SECTION("example 5")
    {
        auto fen = read_FEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("a2a3: 1\n"
                                             "b2b3: 1\n"
                                             "c2c3: 1\n"
                                             "g2g3: 1\n"
                                             "h2h3: 1\n"
                                             "a2a4: 1\n"
                                             "b2b4: 1\n"
                                             "g2g4: 1\n"
                                             "h2h4: 1\n"
                                             "d7c8q: 1\n"
                                             "d7c8r: 1\n"
                                             "d7c8b: 1\n"
                                             "d7c8n: 1\n"
                                             "b1d2: 1\n"
                                             "b1a3: 1\n"
                                             "b1c3: 1\n"
                                             "e2g1: 1\n"
                                             "e2c3: 1\n"
                                             "e2g3: 1\n"
                                             "e2d4: 1\n"
                                             "e2f4: 1\n"
                                             "c1d2: 1\n"
                                             "c1e3: 1\n"
                                             "c1f4: 1\n"
                                             "c1g5: 1\n"
                                             "c1h6: 1\n"
                                             "c4b3: 1\n"
                                             "c4d3: 1\n"
                                             "c4b5: 1\n"
                                             "c4d5: 1\n"
                                             "c4a6: 1\n"
                                             "c4e6: 1\n"
                                             "c4f7: 1\n"
                                             "h1f1: 1\n"
                                             "h1g1: 1\n"
                                             "d1d2: 1\n"
                                             "d1d3: 1\n"
                                             "d1d4: 1\n"
                                             "d1d5: 1\n"
                                             "d1d6: 1\n"
                                             "e1f1: 1\n"
                                             "e1d2: 1\n"
                                             "e1f2: 1\n"
                                             "e1g1: 1\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("a2a3: 34\n"
                                             "b2b3: 34\n"
                                             "c2c3: 34\n"
                                             "g2g3: 34\n"
                                             "h2h3: 34\n"
                                             "a2a4: 34\n"
                                             "b2b4: 33\n"
                                             "g2g4: 34\n"
                                             "h2h4: 34\n"
                                             "d7c8q: 31\n"
                                             "d7c8r: 31\n"
                                             "d7c8b: 41\n"
                                             "d7c8n: 41\n"
                                             "b1d2: 34\n"
                                             "b1a3: 34\n"
                                             "b1c3: 34\n"
                                             "e2g1: 34\n"
                                             "e2c3: 34\n"
                                             "e2g3: 34\n"
                                             "e2d4: 34\n"
                                             "e2f4: 34\n"
                                             "c1d2: 34\n"
                                             "c1e3: 34\n"
                                             "c1f4: 34\n"
                                             "c1g5: 32\n"
                                             "c1h6: 31\n"
                                             "c4b3: 34\n"
                                             "c4d3: 34\n"
                                             "c4b5: 34\n"
                                             "c4d5: 35\n"
                                             "c4a6: 33\n"
                                             "c4e6: 35\n"
                                             "c4f7: 32\n"
                                             "h1f1: 34\n"
                                             "h1g1: 34\n"
                                             "d1d2: 34\n"
                                             "d1d3: 34\n"
                                             "d1d4: 34\n"
                                             "d1d5: 35\n"
                                             "d1d6: 28\n"
                                             "e1f1: 34\n"
                                             "e1d2: 34\n"
                                             "e1f2: 28\n"
                                             "e1g1: 34\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("a2a3: 1373\n"
                                             "b2b3: 1368\n"
                                             "c2c3: 1440\n"
                                             "g2g3: 1308\n"
                                             "h2h3: 1371\n"
                                             "a2a4: 1433\n"
                                             "b2b4: 1398\n"
                                             "g2g4: 1337\n"
                                             "h2h4: 1402\n"
                                             "d7c8q: 1459\n"
                                             "d7c8r: 1296\n"
                                             "d7c8b: 1668\n"
                                             "d7c8n: 1607\n"
                                             "b1d2: 1174\n"
                                             "b1a3: 1303\n"
                                             "b1c3: 1467\n"
                                             "e2g1: 1431\n"
                                             "e2c3: 1595\n"
                                             "e2g3: 1523\n"
                                             "e2d4: 1554\n"
                                             "e2f4: 1555\n"
                                             "c1d2: 1368\n"
                                             "c1e3: 1587\n"
                                             "c1f4: 1552\n"
                                             "c1g5: 1422\n"
                                             "c1h6: 1312\n"
                                             "c4b3: 1275\n"
                                             "c4d3: 1269\n"
                                             "c4b5: 1332\n"
                                             "c4d5: 1375\n"
                                             "c4a6: 1256\n"
                                             "c4e6: 1438\n"
                                             "c4f7: 1328\n"
                                             "h1f1: 1364\n"
                                             "h1g1: 1311\n"
                                             "d1d2: 1436\n"
                                             "d1d3: 1685\n"
                                             "d1d4: 1751\n"
                                             "d1d5: 1688\n"
                                             "d1d6: 1500\n"
                                             "e1f1: 1445\n"
                                             "e1d2: 978\n"
                                             "e1f2: 1269\n"
                                             "e1g1: 1376\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        // SECTION("depth 4")
        //{
        //     PerftDivide example_perft_divide("a2a3: 46833\n"
        //                                      "b2b3: 46497\n"
        //                                      "c2c3: 49406\n"
        //                                      "g2g3: 44509\n"
        //                                      "h2h3: 46762\n"
        //                                      "a2a4: 48882\n"
        //                                      "b2b4: 46696\n"
        //                                      "g2g4: 45506\n"
        //                                      "h2h4: 47811\n"
        //                                      "d7c8q: 44226\n"
        //                                      "d7c8r: 38077\n"
        //                                      "d7c8b: 65053\n"
        //                                      "d7c8n: 62009\n"
        //                                      "b1d2: 40560\n"
        //                                      "b1a3: 44378\n"
        //                                      "b1c3: 50303\n"
        //                                      "e2g1: 48844\n"
        //                                      "e2c3: 54792\n"
        //                                      "e2g3: 51892\n"
        //                                      "e2d4: 52109\n"
        //                                      "e2f4: 51127\n"
        //                                      "c1d2: 46881\n"
        //                                      "c1e3: 53637\n"
        //                                      "c1f4: 52350\n"
        //                                      "c1g5: 45601\n"
        //                                      "c1h6: 40913\n"
        //                                      "c4b3: 43453\n"
        //                                      "c4d3: 43565\n"
        //                                      "c4b5: 45559\n"
        //                                      "c4d5: 48002\n"
        //                                      "c4a6: 41884\n"
        //                                      "c4e6: 49872\n"
        //                                      "c4f7: 43289\n"
        //                                      "h1f1: 46101\n"
        //                                      "h1g1: 44668\n"
        //                                      "d1d2: 48843\n"
        //                                      "d1d3: 57153\n"
        //                                      "d1d4: 57744\n"
        //                                      "d1d5: 56899\n"
        //                                      "d1d6: 43766\n"
        //                                      "e1f1: 49775\n"
        //                                      "e1d2: 33423\n"
        //                                      "e1f2: 36783\n"
        //                                      "e1g1: 47054\n");

        //    CHECK(perft(fen.side_to_move, fen.board, perft_divide, 4) == example_perft_divide.total_moves());
        //    CHECK(check_perft_divide(perft_divide, example_perft_divide);
        //}
    }

    SECTION("example 6")
    {
        auto fen = read_FEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
        PerftDivide perft_divide;

        SECTION("depth 1")
        {
            PerftDivide example_perft_divide("b2b3: 1\n"
                                             "g2g3: 1\n"
                                             "h2h3: 1\n"
                                             "a3a4: 1\n"
                                             "d3d4: 1\n"
                                             "b2b4: 1\n"
                                             "h2h4: 1\n"
                                             "c3b1: 1\n"
                                             "c3d1: 1\n"
                                             "c3a2: 1\n"
                                             "c3a4: 1\n"
                                             "c3b5: 1\n"
                                             "c3d5: 1\n"
                                             "f3e1: 1\n"
                                             "f3d2: 1\n"
                                             "f3d4: 1\n"
                                             "f3h4: 1\n"
                                             "f3e5: 1\n"
                                             "c4a2: 1\n"
                                             "c4b3: 1\n"
                                             "c4b5: 1\n"
                                             "c4d5: 1\n"
                                             "c4a6: 1\n"
                                             "c4e6: 1\n"
                                             "c4f7: 1\n"
                                             "g5c1: 1\n"
                                             "g5d2: 1\n"
                                             "g5e3: 1\n"
                                             "g5f4: 1\n"
                                             "g5h4: 1\n"
                                             "g5f6: 1\n"
                                             "g5h6: 1\n"
                                             "a1b1: 1\n"
                                             "a1c1: 1\n"
                                             "a1d1: 1\n"
                                             "a1e1: 1\n"
                                             "a1a2: 1\n"
                                             "f1b1: 1\n"
                                             "f1c1: 1\n"
                                             "f1d1: 1\n"
                                             "f1e1: 1\n"
                                             "e2d1: 1\n"
                                             "e2e1: 1\n"
                                             "e2d2: 1\n"
                                             "e2e3: 1\n"
                                             "g1h1: 1\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 1) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 2")
        {
            PerftDivide example_perft_divide("b2b3: 46\n"
                                             "g2g3: 46\n"
                                             "h2h3: 46\n"
                                             "a3a4: 46\n"
                                             "d3d4: 45\n"
                                             "b2b4: 45\n"
                                             "h2h4: 46\n"
                                             "c3b1: 46\n"
                                             "c3d1: 46\n"
                                             "c3a2: 46\n"
                                             "c3a4: 46\n"
                                             "c3b5: 46\n"
                                             "c3d5: 45\n"
                                             "f3e1: 47\n"
                                             "f3d2: 47\n"
                                             "f3d4: 46\n"
                                             "f3h4: 47\n"
                                             "f3e5: 50\n"
                                             "c4a2: 46\n"
                                             "c4b3: 46\n"
                                             "c4b5: 46\n"
                                             "c4d5: 45\n"
                                             "c4a6: 47\n"
                                             "c4e6: 45\n"
                                             "c4f7: 4\n"
                                             "g5c1: 47\n"
                                             "g5d2: 47\n"
                                             "g5e3: 46\n"
                                             "g5f4: 48\n"
                                             "g5h4: 47\n"
                                             "g5f6: 44\n"
                                             "g5h6: 46\n"
                                             "a1b1: 46\n"
                                             "a1c1: 46\n"
                                             "a1d1: 46\n"
                                             "a1e1: 46\n"
                                             "a1a2: 46\n"
                                             "f1b1: 46\n"
                                             "f1c1: 46\n"
                                             "f1d1: 46\n"
                                             "f1e1: 46\n"
                                             "e2d1: 46\n"
                                             "e2e1: 46\n"
                                             "e2d2: 46\n"
                                             "e2e3: 45\n"
                                             "g1h1: 46\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 2) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        SECTION("depth 3")
        {
            PerftDivide example_perft_divide("b2b3: 1943\n"
                                             "g2g3: 2075\n"
                                             "h2h3: 2163\n"
                                             "a3a4: 2076\n"
                                             "d3d4: 2202\n"
                                             "b2b4: 2027\n"
                                             "h2h4: 2034\n"
                                             "c3b1: 1719\n"
                                             "c3d1: 1674\n"
                                             "c3a2: 1897\n"
                                             "c3a4: 1944\n"
                                             "c3b5: 1986\n"
                                             "c3d5: 2030\n"
                                             "f3e1: 1769\n"
                                             "f3d2: 2002\n"
                                             "f3d4: 2293\n"
                                             "f3h4: 2045\n"
                                             "f3e5: 2403\n"
                                             "c4a2: 1944\n"
                                             "c4b3: 1947\n"
                                             "c4b5: 1915\n"
                                             "c4d5: 1951\n"
                                             "c4a6: 1943\n"
                                             "c4e6: 2093\n"
                                             "c4f7: 165\n"
                                             "g5c1: 1841\n"
                                             "g5d2: 2026\n"
                                             "g5e3: 2114\n"
                                             "g5f4: 2205\n"
                                             "g5h4: 1898\n"
                                             "g5f6: 1933\n"
                                             "g5h6: 2065\n"
                                             "a1b1: 1943\n"
                                             "a1c1: 1899\n"
                                             "a1d1: 1853\n"
                                             "a1e1: 1764\n"
                                             "a1a2: 1854\n"
                                             "f1b1: 1944\n"
                                             "f1c1: 1990\n"
                                             "f1d1: 2034\n"
                                             "f1e1: 2035\n"
                                             "e2d1: 1897\n"
                                             "e2e1: 1944\n"
                                             "e2d2: 2079\n"
                                             "e2e3: 2121\n"
                                             "g1h1: 2211\n");

            CHECK(perft(fen.side_to_move, fen.board, perft_divide, 3) == example_perft_divide.total_moves());
            check_perft_divide(perft_divide, example_perft_divide);
        }

        // SECTION("depth 4")
        //{
        //     PerftDivide example_perft_divide("b2b3: 83959\n"
        //                                      "g2g3: 89798\n"
        //                                      "h2h3: 93404\n"
        //                                      "a3a4: 89719\n"
        //                                      "d3d4: 93464\n"
        //                                      "b2b4: 85907\n"
        //                                      "h2h4: 87792\n"
        //                                      "c3b1: 74196\n"
        //                                      "c3d1: 72167\n"
        //                                      "c3a2: 81990\n"
        //                                      "c3a4: 83785\n"
        //                                      "c3b5: 86102\n"
        //                                      "c3d5: 84310\n"
        //                                      "f3e1: 77246\n"
        //                                      "f3d2: 87558\n"
        //                                      "f3d4: 98744\n"
        //                                      "f3h4: 89355\n"
        //                                      "f3e5: 111761\n"
        //                                      "c4a2: 83990\n"
        //                                      "c4b3: 84078\n"
        //                                      "c4b5: 84686\n"
        //                                      "c4d5: 82111\n"
        //                                      "c4a6: 87691\n"
        //                                      "c4e6: 88890\n"
        //                                      "c4f7: 8203\n"
        //                                      "g5c1: 81175\n"
        //                                      "g5d2: 89433\n"
        //                                      "g5e3: 91743\n"
        //                                      "g5f4: 99547\n"
        //                                      "g5h4: 83607\n"
        //                                      "g5f6: 79097\n"
        //                                      "g5h6: 89238\n"
        //                                      "a1b1: 83917\n"
        //                                      "a1c1: 81943\n"
        //                                      "a1d1: 79961\n"
        //                                      "a1e1: 76017\n"
        //                                      "a1a2: 80000\n"
        //                                      "f1b1: 83966\n"
        //                                      "f1c1: 85946\n"
        //                                      "f1d1: 87918\n"
        //                                      "f1e1: 87928\n"
        //                                      "e2d1: 82176\n"
        //                                      "e2e1: 84117\n"
        //                                      "e2d2: 89961\n"
        //                                      "e2e3: 90128\n"
        //                                      "g1h1: 95870\n");

        //    CHECK(perft(fen.side_to_move, fen.board, perft_divide, 4) == example_perft_divide.total_moves());
        //    CHECK(check_perft_divide(perft_divide, example_perft_divide);
        //}
    }
}

}  // namespace chess
