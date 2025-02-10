#pragma once
#include <fstream>
#include "../../Action.hpp"

namespace stg::decrypt {
    class BMP : public Action {
        std::fstream file;
    public:
        BMP(const input::Values&);
        auto run() -> void override;
    };
    class PPM : public Action {
        std::fstream file;
    public:
        PPM(const input::Values&);
        auto run() -> void override;
    };
    auto lsb8raw_decrypt(std::fstream&, int) -> std::string;
    auto lsb8ascii_decrypt(std::fstream&, int) -> std::string;
}
