#include <vector>
#include <fstream>

#include "File.hpp"

RGB::RGB(int r, int g, int b) : r(r), g(g), b(b) {}
auto RGB::get_r() const -> int { return r; }
auto RGB::get_g() const -> int { return g; }
auto RGB::get_b() const -> int { return b; }


namespace file {

    auto get_bytes(std::fstream& file, int pos, int size) -> std::vector<char> {
        if (!file.is_open())
            throw std::runtime_error("File is not open.");
        file.seekg(pos, std::ios::beg);
        auto bytes = std::vector<char>(size);
        file.read(bytes.data(), bytes.size());
        return bytes;
    }

    auto little_endian_bytes2int(std::vector<char>& container) -> int {
        auto number = int(0);
        for (int i = container.size() - 1; i >= 0; i--)
            number = (number << 8) | static_cast<unsigned char>(container[i] & 0xFF);
        return number;
    }

    namespace bmp {

        auto xy_size(std::fstream& file) -> const std::pair<int, int> {
            auto bytes = get_bytes(file, 18, 8);
            auto mid = bytes.size() / 2;
            auto height_bytes = std::vector(bytes.begin() + mid, bytes.end()),
                width_bytes = std::vector(bytes.begin(), bytes.begin() + mid);
            auto height = little_endian_bytes2int(height_bytes),
                width = little_endian_bytes2int(width_bytes);
            return std::pair(height, width);
        }

        auto pix_size(std::fstream& file) -> int {
            auto bytes = get_bytes(file, 28, 2);
            return little_endian_bytes2int(bytes);
        }

        auto pix_array_start(std::fstream& file) -> int {
            auto offset = 10, size = 4;
            auto bytes = get_bytes(file, offset, size);
            return  offset + little_endian_bytes2int(bytes);
        }

    }

    namespace ppm {

        auto is_raw(std::fstream& file) -> bool {
            file.seekg(0);
            auto bytes = get_bytes(file, 0, 2);
            auto header = std::string();
            for (auto& b : bytes) header += b;
            return header == std::string("P6");
        }

        auto is_ascii(std::fstream& file) -> bool {
            file.seekg(0);
            auto bytes = get_bytes(file, 0, 2);
            auto header = std::string();
            for (auto& b : bytes) header += b;
            return header == std::string("P3");
        }

        auto xy_size(std::fstream& file) -> const std::pair<int, int> {
            using namespace std;
            file.seekg(0);
            auto line = string(), width = string(), height = string();
            std::getline(file, line); // pass first line
            while (std::getline(file, line))
                if (line.at(0) != '#') {
                    auto space = line.find(' ');
                    width = line.substr(0,space);
                    height = line.substr(space, line.size());
                    break;
                }
            return pair(stoi(height), stoi(width));
        }

        auto pix_array_start(std::fstream& file) -> int {
            auto line = std::string();
            file.seekg(0);
            auto counter = int(0);
            for (int i = 0; i < 3; i++) {
                std::getline(file, line);
                if (line.at(0) == '#') --i;
                counter += line.size() + 1; // + \n character
            }
            return counter;
        }

    }

}

