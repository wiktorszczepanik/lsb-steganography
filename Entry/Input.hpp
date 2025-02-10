#pragma once

#include <filesystem>
#include <vector>
#include <string>

#include "../Constants/Mode.hpp"

namespace input {
    class Values {
        Mode type;
        std::filesystem::path path;
        std::string message;
        int param_counter;
    public:
        Values(const std::vector<std::string>&);
        auto get_type() const -> Mode;
        auto get_path() const -> std::filesystem::path;
        auto get_message() const -> std::string;
        auto validate() const -> void;
    private:
        auto set_for0(const std::vector<std::string>&) -> void;
        auto set_for0() -> void;
        auto set_for1(const std::vector<std::string>&) -> void;
        auto set_for2(const std::vector<std::string>&) -> void;
        auto str2path(std::string) const -> std::filesystem::path;
        static auto check_message(std::string) -> void;
    };
    auto collect(int argc, char* argv[]) -> std::vector<std::string>;
}