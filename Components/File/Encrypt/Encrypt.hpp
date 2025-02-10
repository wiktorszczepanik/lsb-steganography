#pragma once
#include <fstream>

#include "../../../Entry/Input.hpp"
#include "../../Action.hpp"
#include "../File.hpp"

namespace stg::encrypt {
    class BMP : public Action {
        std::fstream file;
        RGB rgb;
    public:
        BMP(const input::Values&);
        auto run() -> void override;
    private:
        static auto is_8bits(RGB) -> bool;
    };
    class PPM : public Action {
        std::fstream file;
        RGB rgb;
    public:
        PPM(const input::Values&);
        auto run() -> void override;
        static auto get_line(std::fstream&) -> std::string;
    };
    auto lsb8raw_encrypt(std::fstream &, std::string, int) -> void;
    auto lsb8ascii_encrypt(std::fstream &, std::string, int) -> void;
}
