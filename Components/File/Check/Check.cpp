#include <fmt/base.h>
#include <fmt/ranges.h>
#include <fstream>
#include <string>

#include "Check.hpp"
#include "../Info/Info.hpp"
#include "../File.hpp"

namespace stg {

    Check::Check(const input::Values& values) : Action(values) {}

    auto Check::run() -> void {
        auto path = values.get_path();
        auto message = values.get_message();
        auto ext = extension(path);
        auto file = std::fstream(path);
        if (!file.is_open())
            throw std::ios_base::failure("File could not be opened.");
        bool state = is_bmp(ext)
            ? bmp_state(file, message)
            : ppm_state(file, message);
        if (state) fmt::println("Space is available to encode the message.\n"
             "The file may contain the given message.");
        else fmt::println("There is no space to encode the message.\n"
             "The file is not able to contain the given message.");
    }

    auto Check::bmp_state(std::fstream& file, std::string message) -> bool {
        auto [x, y] = file::bmp::xy_size(file);
        auto bit_num = (x * y) * 3; // For RGB channels
        return bit_num > message.size() * 8;
    }

    auto Check::ppm_state(std::fstream& file, std::string message) -> bool {
        auto [x, y] = file::ppm::xy_size(file); // here
        auto bit_num = (x * y) * 3; // For RGB channels
        return bit_num > message.size() * 8;
    }

}
