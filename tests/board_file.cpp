#include "catch2/catch_test_macros.hpp"

#include "../src/board/file.hpp"

namespace chess {

TEST_CASE("board/file")
{
    SECTION("is_valid_file_char()")
    {
        CHECK(is_valid_file_char('a'));
        CHECK(is_valid_file_char('b'));
        CHECK(is_valid_file_char('c'));
        CHECK(is_valid_file_char('f'));
        CHECK(is_valid_file_char('g'));
        CHECK(is_valid_file_char('h'));

        CHECK(is_valid_file_char('@') == false);
        CHECK(is_valid_file_char('i') == false);
        CHECK(is_valid_file_char('-') == false);
        CHECK(is_valid_file_char('\0') == false);
    }

    SECTION("from_file()")
    {
        CHECK(from_file('a') == 0);
        CHECK(from_file('b') == 1);
        CHECK(from_file('c') == 2);
        CHECK(from_file('f') == 5);
        CHECK(from_file('g') == 6);
        CHECK(from_file('h') == 7);
    }

    SECTION("to_file()")
    {
        CHECK(to_file(0) == 'a');
        CHECK(to_file(1) == 'b');
        CHECK(to_file(2) == 'c');
        CHECK(to_file(5) == 'f');
        CHECK(to_file(6) == 'g');
        CHECK(to_file(7) == 'h');
    }
}

}  // namespace chess
