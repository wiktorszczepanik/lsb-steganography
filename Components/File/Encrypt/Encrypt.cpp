#include <fstream>
#include <fmt/ostream.h>
#include <fmt/base.h>

#include "Encrypt.hpp"
#include "../../Action.hpp"
#include "../Check/Check.hpp"
#include "../File.hpp"
#include "fmt/std.h"

namespace stg::encrypt {

    BMP::BMP(const input::Values& values) : Action(values), rgb(0, 0 , 0) {
        file = std::fstream(values.get_path(), std::ios::in | std::ios::out | std::ios::binary);
        rgb = (file::bmp::pix_size(file) > 16)
            ? RGB(8, 8, 8) : RGB(5, 6, 5);
    }

    auto BMP::run() -> void {
        if (!file.is_open()) throw std::ios_base::failure(
            "File permissions do not allow writing.");
        auto message = values.get_message();
        if (!Check::bmp_state(file, message))
            throw std::length_error("There is no space to encode the message.");
        auto start = file::bmp::pix_array_start(file);
        if (is_8bits(rgb)) lsb8raw_encrypt(file, message, start);
        else throw std::invalid_argument(
            "Pixel size is to small (5, 6, 5) to perform valid lsb steganography.\n"
            "Supported are 24 bits per pixel and 32 bits per pixel."
        );
        fmt::println("Message has been encrypted.");
    }

    auto BMP::is_8bits(RGB rgb) -> bool {
        return rgb.get_r() == 8
            && rgb.get_g() == 8
            && rgb.get_b() == 8;
    }


    PPM::PPM(const input::Values& values) : Action(values), rgb(8, 8, 8) {
        file = std::fstream(values.get_path(),
        std::ios::in | std::ios::out | std::ios::binary);
    }

    auto PPM::run() -> void {
        if (!file.is_open()) throw std::ios_base::failure(
            "File permissions do not allow writing.");
        auto message = values.get_message();
        if (!Check::ppm_state(file, message))
            throw std::length_error("There is no space to encode the message.");
        auto start = file::ppm::pix_array_start(file);
        if (file::ppm::is_raw(file))
            lsb8raw_encrypt(file, message, start);
        else if (file::ppm::is_ascii(file))
            lsb8ascii_encrypt(file, message, start);
        else throw std::invalid_argument(
            "Invalid data formatting.\nAvaiable are ASCII(P3) and RAW(P6)"
        );
        fmt::println("Message has been encrypted.");
    }

    auto PPM::get_line(std::fstream& file) -> std::string {
        auto text_number = std::string();
        auto character = char(0);
        while (!std::isspace(character)) {
            file.get(character);
            text_number.append(&character);
        }
        return text_number;
    }

    // https://en.cppreference.com/w/cpp/io/basic_fstream
    auto lsb8raw_encrypt(std::fstream &file, std::string message, int start) -> void {
        file.seekg(start);
        auto file_byte = char();
        auto char_counter = int(0), byte_counter = int(0);
        while (char_counter < message.size()) {
            auto ascii_char = message.at(char_counter);
            for (int i = 0; i < 8; i++, byte_counter++) {
                file.get(file_byte);
                auto ascii_bit = (ascii_char >> (7 - i)) & 0b1;
                file_byte = (file_byte & 0xFE) | ascii_bit;
                file.seekp(start + byte_counter);
                file.put(file_byte);
            }
            char_counter++;
        }
    }

    // https://en.cppreference.com/w/cpp/io/basic_fstream
    auto lsb8ascii_encrypt(std::fstream &file, std::string message, int start) -> void {
        file.seekg(start);
        auto char_counter = int(0), line_counter = int(0);
        while (char_counter < message.size()) {
            auto ascii_char = message.at(char_counter);
            for (int i = 0; i < 8; i++, line_counter++) {
                auto position = file.tellg();
                auto line = PPM::get_line(file);
                auto file_number = std::stoi(line);
                auto ascii_bit = (ascii_char >> (7 - i)) & 0b1;
                file.seekp(position); // back to init position
                if (file_number % 2 == 1 && ascii_bit == 0)
                    fmt::print(file, "{}", file_number - 1);
                else if (file_number % 2 == 0 && ascii_bit == 1)
                    fmt::print(file, "{}", file_number + 1);
                else fmt::print(file, "{}", file_number);
                file.seekp(position + std::streamoff(line.size()));
            }
            char_counter++;
        }
    }

}
