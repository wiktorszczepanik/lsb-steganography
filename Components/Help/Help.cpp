#include <fmt/base.h>

#include "Help.hpp"

namespace stg {

    Help::Help(const input::Values& values) : Action(values) {}

    auto Help::run() -> void {
        fmt::print("The program supports the following flags:\n\n"
                "-i <file path>             : Checks if the path leads to a supported file format. "
                "If the file is supported, it will display its information (size, timestamp, etc.).\n"
                "-e <file path> <message>   : Opens an image and saves the specified message in it. "
                "The file must be in a supported format.\n"
                "-d <file path>             : Reads the message from the given file. "
                "The file must be in a supported format.\n"
                "-c <file path> <message>   : Checks if a hidden message can be saved in the given file. "
                "It also checks whether the file is large enough to accommodate the message.\n"
                "-h                         : Displays information about the program and its flags.\n\n"
                "Examples of usage:\n"
                "  lsb-steganography -i /path/to/bmp/or/ppm/file.xyz\n"
                "  lsb-steganography -e /path/to/bmp/or/ppm/file.xyz \"Message to be saved\"\n"
                "  lsb-steganography -d /path/to/bmp/or/ppm/file.xyz\n"
                "  lsb-steganography -c /path/to/bmp/or/ppm/file.xyz \"Hidden message\"\n"
                "  lsb-steganography -h\n\n"
                "Supported graphic formats are \".bmp\" and \".ppm\".\n"
            );
    }

    auto small_help() -> std::string {
        return std::string("\nAvailable program variants are:\n"
           "  lsb-steganography -e /path/to/bmp/or/ppm/file.xyz \"Message to be saved\"\n"
           "  lsb-steganography -c /path/to/bmp/or/ppm/file.xyz \"Hidden message\"\n"
           "  lsb-steganography -i /path/to/bmp/or/ppm/file.xyz\n"
           "  lsb-steganography -d /path/to/bmp/or/ppm/file.xyz\n"
           "  lsb-steganography -h"
           );
    }

}