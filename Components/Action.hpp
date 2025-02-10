#pragma once

#include "../Constants/Format.hpp"
#include "../Entry/Input.hpp"

namespace stg {
    class Action {
    protected:
        input::Values values;
    public:
        Action(const input::Values&);
        virtual auto run() -> void = 0;
        virtual ~Action() = default;
    };
    auto extension(const std::filesystem::path&) -> Format;
    auto is_avaiable(const std::filesystem::path&) -> bool;

    auto is_bmp(const Format&) -> bool;
    auto is_bmp(const std::string&) -> bool;
    auto is_bmp(const std::filesystem::path& path) -> bool;

    auto is_ppm(const Format&) -> bool;
    auto is_ppm(const std::string&) -> bool;
    auto is_ppm(const std::filesystem::path& path) -> bool;
}
