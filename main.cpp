#include <fmt/base.h>
#include <fmt/ranges.h>

#include "Components/Action.hpp"
#include "Components/File/Check/Check.hpp"
#include "Components/File/Decrypt/Decrypt.hpp"
#include "Components/File/Encrypt/Encrypt.hpp"
#include "Components/Help/Help.hpp"
#include "Components/File/Info/Info.hpp"
#include "Entry/Input.hpp"
#include "Constants/Mode.hpp"

// https://stackoverflow.com/questions/14737957/handling-command-line-flags-in-c-c
auto main(int argc, char* argv[]) -> int {
    try {
        auto flags = input::collect(argc, argv);
        auto input = input::Values(flags);
        input.validate();
        std::unique_ptr<stg::Action> action;
        switch (input.get_type()) {
            case Mode::HELP: action = std::make_unique<stg::Help>(input); break;
            case Mode::DECRYPT:
                if (stg::is_bmp(input.get_path()))
                    action = std::make_unique<stg::decrypt::BMP>(input);
                else action = std::make_unique<stg::decrypt::PPM>(input);
                break;
            case Mode::ENCRYPT:
                if (stg::is_bmp(input.get_path()))
                    action = std::make_unique<stg::encrypt::BMP>(input);
                else action = std::make_unique<stg::encrypt::PPM>(input);
                break;
            case Mode::INFO: action = std::make_unique<stg::Info>(input); break;
            case Mode::CHECK: action = std::make_unique<stg::Check>(input); break;
            default: throw std::invalid_argument("Provided mode does not exist.");
        } action -> run();
    } catch(std::exception& exception) {
        fmt::println(
        "Error: {} \nUse the \"-h\" flag "
        "to understand how the program works.",
        exception.what());
    }
    return 0;
}