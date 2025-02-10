#pragma once
#include "../Action.hpp"

namespace stg {
    class Help : public Action {
    public:
        Help(const input::Values& values);
        auto run() -> void override;
    };
    auto small_help() -> std::string;
}