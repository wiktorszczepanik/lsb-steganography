#include <string>
#include <filesystem>
#include "Action.hpp"

namespace stg {

    Action::Action(const input::Values& values)
    : values(values) {}

    auto extension(const std::filesystem::path& path) -> Format {
        auto ext = std::string(path.extension());
        return (ext == ".bmp") ? Format::BMP : Format::PPM;
    }

    auto is_avaiable(const std::filesystem::path& path) -> bool {
        return path.extension() == ".bmp"
            || path.extension() == ".ppm";
    }

    auto is_bmp(const Format& extension) -> bool {
        return extension == Format::BMP;
    }

    auto is_bmp(const std::string& extension) -> bool {
        return extension == ".bmp";
    }

    auto is_bmp(const std::filesystem::path& path) -> bool {
        return path.extension() == ".bmp";
    }

    auto is_ppm(const Format& extension) -> bool {
        return extension == Format::PPM;
    }

    auto is_ppm(const std::string& extension) -> bool {
        return extension == ".ppm";
    }

    auto is_ppm(const std::filesystem::path &path) -> bool {
        return path.extension() == ".ppm";
    }

}
