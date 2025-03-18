#ifndef FILEUTIL_H
#define FILEUTIL_H
#include <cstdint>
#include <vector>

class FileUtil {
public:
    static std::vector<uint8_t> readFile(const char* filename);
};

#endif //FILEUTIL_H