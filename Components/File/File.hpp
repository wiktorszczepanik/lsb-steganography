#pragma once
#include "../Action.hpp"

class RGB {
    int r, g, b;
public:
    RGB(int, int, int);
    auto get_r() const -> int;
    auto get_g() const -> int;
    auto get_b() const -> int;
};

namespace file {
    auto get_bytes(std::fstream&, int, int) -> std::vector<char>;
    auto little_endian_bytes2int(std::vector<char>& vector) -> int;
    namespace bmp {
        auto xy_size(std::fstream&) -> const std::pair<int, int>;
        auto pix_size(std::fstream&) -> int; // How many bits per pixel
        auto pix_array_start(std::fstream&) -> int;
    }
    namespace ppm {
        auto is_raw(std::fstream&) -> bool;
        auto is_ascii(std::fstream&) -> bool;
        auto xy_size(std::fstream&) -> const std::pair<int, int>;
        auto pix_array_start(std::fstream&) -> int;
    }
}