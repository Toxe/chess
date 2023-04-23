#include "console_writer.hpp"

#include "fmt/core.h"

namespace chess {

void ConsoleWriter::write(std::string_view text) const
{
    if (write_output_to_console_)
        fmt::print("{}", text);
}

void ConsoleWriter::writeln(std::string_view text) const
{
    if (write_output_to_console_)
        fmt::print("{}\n", text);
}

}  // namespace chess
