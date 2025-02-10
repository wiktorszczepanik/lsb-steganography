#pragma once

#include <string>
#include <map>

#include "../../Action.hpp"
#include "../../../Constants/Format.hpp"

namespace stg {
    class Info : public Action {
    std::map<Format, std::string> ext2txt;
    public:
        Info(const input::Values& values);
        auto run() -> void override;
    private:
        auto extension_check(std::filesystem::path) const -> bool;
        auto get_name() const -> std::pair<std::string, std::string>;
        auto get_extension() const -> std::pair<std::string, std::string>;
        auto get_type() const -> std::pair<std::string, std::string>;
        auto get_used_space() const -> std::pair<std::string, std::string>;
        auto get_img_size(std::string) const -> std::pair<std::string, std::string>;
        auto get_timestamp() const -> std::pair<std::string, std::string>;
    };
}
