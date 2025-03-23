#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <cstdint>
#include <vector>

namespace FileUtil {
    std::vector<uint8_t> readFile(const char* filename);
};

#endif //FILEUTIL_H