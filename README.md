## LSB Steganography

### Overview

LSB Steganography is a program for image steganography that hides messages by modifying the least significant bit of RGB (and optionally Alpha) values. 
The program supports **.bmp** and **.ppm** file formats. 
Project was developed as part of the PJC course at PJATK.

### Flags

The program supports the following command-line flags:

Flag    | Alias     | Description
--------|-----------|---------------------------------------------------------------------------------
-i      | --info    | Checks if the path leads to a supported file format and displays file details.   
-e      | --encrypt | Opens an image and embeds the specified message in it.                           
-d      | --decrypt | Reads and extracts the hidden message from the given file.                      
-c      | --check   | Checks if the file can store the hidden message and verifies available capacity. 
-h      | --help    | Displays information about the program and its flags.                           `

> **Warning!** Encoded messages can only be stored in ASCII format.

### Examples
```Bash
lsb-steganography -i /path/to/bmp/or/ppm/file.xyz
lsb-steganography -e /path/to/bmp/or/ppm/file.xyz "Message to be saved"
lsb-steganography -d /path/to/bmp/or/ppm/file.xyz
lsb-steganography -c /path/to/bmp/or/ppm/file.xyz "Hidden message"
lsb-steganography -h
```

### Installation & Compilation

To use this program, ensure you have a compatible **C++** compiler, **cmake** and required dependencies installed to build the project.
(The **fmt** library is resolved by "FetchContent_Declare" in *CMakeLists.txt* file.)
```cmake
cmake_minimum_required(VERSION 3.29)
set(CMAKE_CXX_STANDARD 20)
```
Once you've confirmed, follow the steps below:
```Bash
git clone https://github.com/wiktorszczepanik/lsb-steganography.git
cd lsb-steganography/
mkdir build/
cd build/
cmake ..
make
```
Now you can run the program.
```Bash
./lsb-steganography
```
### Also
The repository also contains a **lsbstg.sh** file, which was created to demonstrate functionality with files containing different headers and parameters. 
File can be deleted as it does not affect the program in any way.
