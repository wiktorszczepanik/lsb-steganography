#include <stdexcept>
#include <fstream>
#include <fmt/base.h>
#include <fmt/ranges.h>

#include "Input.hpp"
#include "../Constants/Mode.hpp"
#include "../Components/Help/Help.hpp"
#include "fmt/chrono.h"

namespace input {

    Values::Values(const std::vector<std::string>& flags) {
        auto extra_flags = int(flags.size() - 1);
        param_counter = int(0);
        if (extra_flags == 1) set_for1(flags);
        else if (extra_flags == 2) set_for2(flags);
        else if (extra_flags == 0) set_for0(flags);
        else if (extra_flags == -1) set_for0();
        else throw std::length_error("Incorrect number of flags.");
    }

    auto Values::get_type() const -> Mode { return type; }
    auto Values::get_path() const -> std::filesystem::path { return path; }
    auto Values::get_message() const -> std::string { return message; }

    auto Values::validate() const -> void {
        auto notify = std::string("Number of flags for provided mode are incorrect.");
        if ((type == Mode::ENCRYPT || type == Mode::CHECK) && param_counter != 2)
            throw std::invalid_argument(notify.append("\nRequired are path to file and message."));
        if ((type == Mode::DECRYPT || type == Mode::INFO) && param_counter != 1)
            throw std::invalid_argument(notify.append("\nRequired is path to file."));
        if (type == Mode::HELP && param_counter != 0)
            throw std::invalid_argument("No flags for --help mode.");
        if (!message.empty()) check_message(message);
    }

    auto Values::check_message(std::string message) -> void {
        for (auto character : message)
            if (character < 0 || character > 128)
                throw std::invalid_argument(
                    "Only ASCII characters are applicable for provided message."
                );
    }

    auto Values::set_for0(const std::vector<std::string>& flag) -> void {
        auto mode = flag.begin();
        type = (*mode == "-h" || *mode == "--help") ?
            Mode::HELP : throw std::invalid_argument(
            std::string("Probably incorrect type mode. "
                "For mode without flags allowed is (-h).")
                .append(stg::small_help()));
    }

    auto Values::set_for0() -> void {
        type = Mode::HELP; path = ""; message = {};
    }

    auto Values::set_for1(const std::vector<std::string>& flags) -> void {
        auto flag = flags.begin();
        if (*flag == "-i" || *flag == "--info") type = Mode::INFO;
        else if (*flag == "-d" || *flag == "--decrypt") type = Mode::DECRYPT;
        else throw std::invalid_argument(
            std::string("Probably incorrect type mode. "
                "Available modes with 1 flag are (-i) and (-d).")
                .append(stg::small_help()));
        path = str2path(*(++flag)), param_counter++;
        message = {};
    }

    auto Values::set_for2(const std::vector<std::string>& flags) -> void {
        auto flag = flags.begin();
        if (*flag == "-e" || *flag == "--encrypt") type = Mode::ENCRYPT;
        else if (*flag == "-c" || *flag == "--check") type = Mode::CHECK;
        else throw std::invalid_argument(
        std::string("Probably incorrect type mode. "
            "Available modes with 2 flag are (-e) and (-c).")
            .append(stg::small_help())
        );
        path = str2path(*(++flag)), param_counter++;
        message = std::string(*(++flag) + '\0'), param_counter++;
    }

    auto Values::str2path(const std::string text) const -> std::filesystem::path {
        auto temp_path = std::filesystem::path(text);
        if (!exists(temp_path))
            throw std::ios_base::failure(
                "File path " + text + " does not exist. ");
        auto perm_file = std::ifstream(temp_path);
        if (!perm_file.is_open())
            throw std::ios_base::failure(
                "File permissions do not allow reading.");
        if (!stg::is_avaiable(temp_path))
            throw std::invalid_argument(
                R"(Unsupported file type. Available are ".bmp" and ".ppm".)");
        return temp_path;
    }

    // https://stackoverflow.com/questions/14737957/handling-command-line-flags-in-c-c
    auto collect(int argc, char* argv[]) -> std::vector<std::string> {
        auto flags = std::vector<std::string>();
        auto in_quotes = false;
        auto modified_flag = std::string({});
        for (int i = 1; i < argc; i++) {
            auto arg = std::string(argv[i]);
            if (arg.front() == '"' && !in_quotes) {
                modified_flag = arg.erase(0, 1);
                in_quotes = true;
            } else if (arg.back() == '"' && in_quotes) {
                modified_flag.append(" " + arg.erase(arg.size() - 1, 1));
                in_quotes = false;
            } else if (in_quotes)
                modified_flag.append(" " + arg);
            else flags.push_back(argv[i]);
        }
        if (in_quotes)
            throw std::invalid_argument(
                "Unclosed quotes in last argument.");
        return flags;
    }

}
