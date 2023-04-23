#pragma once

#include <string_view>

namespace chess {

class ConsoleWriter {
public:
    ConsoleWriter(const bool write_output = true) : write_output_to_console_{write_output} { }

    void write(std::string_view text) const;
    void writeln(std::string_view text) const;

private:
    bool write_output_to_console_;
};

}  // namespace chess
