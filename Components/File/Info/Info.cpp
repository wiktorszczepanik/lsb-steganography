#include <regex>
#include <array>
#include <fmt/base.h>
#include <iostream>
#include <utility>
#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include <fmt/chrono.h>
#include <chrono>
#include <string>
#include <map>


#include "../../../Constants/Format.hpp"
#include "Info.hpp"
#include "../File.hpp"

namespace stg {

    Info::Info(const input::Values &values) : Action(values) {
        ext2txt = std::map<Format, std::string> {
            {Format::BMP, ".bmp"}, {Format::PPM, ".ppm"}
        };
    }

    auto Info::run() -> void {
        if (!extension_check(values.get_path()))
            throw std::invalid_argument(
                R"(Incorrect extension. Available are ".bmp" and ".ppm".)");
        namespace fs = std::filesystem;
        auto extension = get_extension();
        auto exif_data = std::array {
            get_name(), extension, get_type(),
            get_img_size(extension.second), get_used_space(),
            get_timestamp()
        };
        for (auto [f, s] : exif_data)
            fmt::println("{} : {}", f, s);
    }

    auto Info::extension_check(std::filesystem::path path) const -> bool {
        auto extension = std::string(path.extension());
        return extension == ext2txt.at(Format::BMP)
            || extension == ext2txt.at(Format::PPM);
    }

    auto Info::get_name() const -> std::pair<std::string, std::string> {
        using namespace std;
        return pair<string, string>("Name      ", values.get_path().filename());
    }

    auto Info::get_extension() const -> std::pair<std::string, std::string> {
        using namespace std;
        auto ext = string(values.get_path().extension());
        return pair<string, string>("Extension ", ext);
    }

    // reference : https://en.cppreference.com/w/cpp/filesystem/file_type
    auto Info::get_type() const -> std::pair<std::string, std::string> {
        using namespace std; namespace fs = std::filesystem;
        auto status = fs::status(values.get_path());
        auto status_value = string({});
        switch (status.type()) {
            case fs::file_type::regular:
                status_value = "regular file"; break;
            case fs::file_type::not_found:
                status_value = "not found"; break;
            case fs::file_type::none:
                status_value = "none"; break;
            case fs::file_type::unknown:
                status_value = "unknown type"; break;
            case fs::file_type::symlink:
                status_value = "symbolic link"; break;
            default: throw invalid_argument("Unsupported file type.");
        }
        return pair<string, string>("Type      ", status_value);
    }

    auto Info::get_used_space() const -> std::pair<std::string, std::string> {
        using namespace std; namespace fs = std::filesystem;
        auto size = fs::file_size(values.get_path());
        return pair<string, string>("File Size ", to_string(size).append(" Bytes"));
    }

    auto Info::get_img_size(std::string extension) const -> std::pair<std::string, std::string> {
        auto file = std::fstream(values.get_path(), std::ios::in | std::ios::binary);
        auto which_is = [] (std::string& ext) { return ext == ".bmp"; };
        auto xy_size = which_is(extension)
            ? file::bmp::xy_size(file) : file::ppm::xy_size(file);
        return std::pair("Image Size", std::to_string(xy_size.first).append(" x ")
            .append(std::to_string(xy_size.second)));
    }

    // https://en.cppreference.com/w/cpp/filesystem/last_write_time
    // https://en.cppreference.com/w/cpp/chrono/c/localtime
    // https://en.cppreference.com/w/cpp/io/manip/put_time
    // https://www.reddit.com/r/cpp_questions/comments/udev33/using_format_on_file_time_type/
    // https://groups.google.com/a/isocpp.org/g/std-proposals/c/GVFNRtkkjHY
    auto Info::get_timestamp() const -> std::pair<std::string, std::string> {
        using namespace std; namespace fs = std::filesystem;
        auto timestamp = fs::last_write_time(values.get_path()); // UTC 0
        auto system_time = chrono::time_point_cast<chrono::system_clock::duration>(
            timestamp - chrono::file_clock::now() + chrono::system_clock::now());
        auto time_ptr = chrono::system_clock::to_time_t(system_time);
        auto time_to_str = std::stringstream();
        time_to_str << std::put_time(std::localtime(&time_ptr), "%Y-%m-%d %H:%M:%S");
        auto formatted_timestamp = time_to_str.str();
        return std::pair<string, string>("Timestamp ", formatted_timestamp);
    }

}
