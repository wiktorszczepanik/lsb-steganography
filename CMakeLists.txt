cmake_minimum_required(VERSION 3.29)
project(steganography)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY  https://github.com/fmtlib/fmt
        GIT_TAG         11.0.2
)

FetchContent_MakeAvailable(fmt)

add_executable( lsb-steganography
        main.cpp
        Entry/Input.cpp
        Entry/Input.hpp
        Constants/Mode.hpp
        Components/Action.hpp
        Components/Help/Help.hpp
        Components/Help/Help.cpp
        Components/Action.cpp
        Constants/Format.hpp
        Components/File/Info/Info.hpp
        Components/File/Info/Info.cpp
        Components/File/Check/Check.hpp
        Components/File/Check/Check.cpp
        Components/File/File.hpp
        Components/File/File.cpp
        Components/File/Decrypt/Decrypt.hpp
        Components/File/Encrypt/Encrypt.hpp
        Components/File/Encrypt/Encrypt.cpp
        Components/File/Decrypt/Decrypt.cpp)
target_link_libraries(lsb-steganography fmt)
