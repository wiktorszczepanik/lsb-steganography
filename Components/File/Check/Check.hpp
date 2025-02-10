#pragma once

#include "../../Action.hpp"

namespace stg {
    class Check : public Action {
    public:
        Check(const input::Values& values);

        auto run() -> void;

        static auto bmp_state(std::fstream&, std::string) -> bool;
        static auto ppm_state(std::fstream&, std::string) -> bool;
    };
}
