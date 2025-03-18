#include "utils/file_util.h"

#include <fstream>
#include <iostream>

std::vector<uint8_t> FileUtil::readFile(const char *filename) {
    std::ifstream fs(filename, std::ios::binary | std::ios::ate);

    if (!fs) {
        throw std::runtime_error("Failed to open file");
    }

    std::cout << "Loading file" << filename << std::endl;

    const std::ifstream::pos_type pos = fs.tellg();
    auto fileSize = static_cast<std::uint32_t>(pos);

    if (fileSize == 0) {
        throw std::runtime_error("File is empty");
    }

    std::vector<char> fileContents(fileSize);

    fs.seekg(0, std::ios::beg);
    fs.read(&fileContents[0], fileSize);
    fs.close();

    auto fileData = std::vector<uint8_t>(fileContents.begin(), fileContents.end());
    return fileData;
}
