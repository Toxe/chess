#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_string.hpp"

#include "../src/perft/print.hpp"

namespace chess {

TEST_CASE("perft/print")
{
    SECTION("print_perft_divide()")
    {
        SECTION("with entries")
        {
            PerftDivide perft_divide;
            perft_divide.add(Square{"a1"}, Square{"a3"}, 50);
            perft_divide.add(Square{"a1"}, Square{"a2"}, 5);
            perft_divide.add(Square{"f4"}, Square{"f6"}, 20);
            perft_divide.add(Square{"b2"}, Square{"c2"}, 10);
            perft_divide.add(Square{"f4"}, Square{"f5"}, 100);

            const std::string s = "a1a2: 5\n"
                                  "a1a3: 50\n"
                                  "b2c2: 10\n"
                                  "f4f5: 100\n"
                                  "f4f6: 20\n"
                                  "total: 185";

            CHECK_THAT(print_perft_divide(perft_divide), Catch::Matchers::Equals(s));
        }

        SECTION("when empty")
        {
            const PerftDivide perft_divide;
            CHECK_THAT(print_perft_divide(perft_divide), Catch::Matchers::Equals("total: 0"));
        }
    }
}

}  // namespace chess
