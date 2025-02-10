#include "Decrypt.hpp"

#include <fstream>
#include <fmt/base.h>

#include "../File.hpp"
#include "../../Action.hpp"

namespace stg::decrypt {

    BMP::BMP(const input::Values& values) : Action(values) {
        file = std::fstream(values.get_path(), std::ios::in | std::ios::out | std::ios::binary);
    }

    auto BMP::run() -> void {
        auto start = file::bmp::pix_array_start(file);
        auto decrypted_message = lsb8raw_decrypt(file, start);
        fmt::println("Decrypted message is:\n{}", decrypted_message);
    }


    PPM::PPM(const input::Values& values) : Action(values) {
        file = std::fstream(values.get_path(), std::ios::in | std::ios::out | std::ios::binary);
    }

    auto PPM::run() -> void {
        auto start = file::ppm::pix_array_start(file);
        auto decrypted_message = std::string();
        if (file::ppm::is_raw(file))
            decrypted_message = lsb8raw_decrypt(file, start);
        else if (file::ppm::is_ascii(file))
            decrypted_message = lsb8ascii_decrypt(file, start);
        else throw std::invalid_argument(
            "Invalid data formatting.\nAvaiable formats for decryption are ASCII(P3) and RAW(P6)");
        fmt::println("Decrypted message is:\n{}", decrypted_message);
    }

    auto lsb8raw_decrypt(std::fstream &file, int start) -> std::string {
        file.seekg(start);
        auto message = std::string();
        auto exit_char = char(0x20), file_byte = char();
        while (exit_char != 0x00) {
            exit_char == 0b0;
            for (int i = 0; i < 8; i++) {
                file.get(file_byte);
                exit_char <<= 1;
                exit_char |= file_byte & 0x01;
            }
            message += exit_char;
        }
        message.pop_back();
        return message;
    }

    auto lsb8ascii_decrypt(std::fstream &file, int start) -> std::string {
        file.seekg(start);
        auto message = std::string(), line = std::string();
        auto exit_char = char(0x20);
        while (exit_char != 0x00) {
            exit_char = 0b0;
            for (int i = 0; i < 8; i++) {
                std::getline(file, line);
                auto bit = std::stoi(line) % 2 == 0
                    ? 0b00000000 : 0b00000001;
                exit_char <<= 1, exit_char |= bit;
            }
            message += exit_char;
        }
        message.pop_back();
        return message;
    }


}