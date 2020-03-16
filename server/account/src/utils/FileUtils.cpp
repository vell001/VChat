//
// Created by vell on 19-5-10.
//
#include "FileUtils.h"

bool createDir(const char *name, mode_t mode) {
    // 创建文件夹
    if (0 != access(name, 0)) {
        //目录不存在
        if (0 != mkdir(name, mode)) {
            // 创建不成功
            return false;
        }
    }
    return true;
}

bool createDirTree(const std::string &full_path, mode_t mode) {
    size_t pos = 0;
    bool ret_val = true;

    while(ret_val && pos != std::string::npos) {
        pos = full_path.find('/', pos + 1);
        ret_val = createDir(full_path.substr(0, pos).c_str(), mode);
    }

    return ret_val;
}

std::string readFileToStr(const std::string &filePath) {
    std::ifstream t(filePath);
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}
