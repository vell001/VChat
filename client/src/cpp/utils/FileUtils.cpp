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

bool createDirTree(const std::string full_path, mode_t mode) {
    size_t pos = 0;
    bool ret_val = true;

    while(ret_val && pos != std::string::npos) {
        pos = full_path.find('/', pos + 1);
        ret_val = createDir(full_path.substr(0, pos).c_str(), mode);
    }

    return ret_val;
}

std::string findDirByStart(const std::string &dirPath, const char *startStr) {
    std::string filePath;
    if (dirPath.empty()) {
        LOGE(FILE_TAG, "dirPath is null !");
        return filePath;
    }
    DIR *dir = opendir(dirPath.c_str());
    if (NULL == dir) {
        LOGE(FILE_TAG, "Can not open dir. Check path or permission!");
        return filePath;
    }

    struct dirent *file;
    // read all the files in dir
    while ((file = readdir(dir)) != NULL) {
        // skip "." and ".."
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            LOGV(FILE_TAG, "ignore . and ..");
            continue;
        }
        if (file->d_type == DT_DIR && startsWith(file->d_name, startStr)) {
            filePath = strFmt("%s/%s", dirPath.c_str(), file->d_name);
            break;
        }
    }
    closedir(dir);
    return filePath;
}

void showAllFiles(const std::string &dirPath) {
    if (dirPath.empty()) {
        LOGE(FILE_TAG, "dir_name is null !");
        return;
    }
    DIR *dir = opendir(dirPath.c_str());
    if (NULL == dir) {
        LOGE(FILE_TAG, "Can not open dir. Check path or permission!");
        return;
    }

    struct dirent *file;
    // read all the files in dir
    while ((file = readdir(dir)) != NULL) {
        // skip "." and ".."
        if (strcmp(file->d_name, ".") == 0 || strcmp(file->d_name, "..") == 0) {
            LOGV(FILE_TAG, "ignore . and ..");
            continue;
        }
        if (file->d_type == DT_DIR) {
            std::string filePath = strFmt("%s/%s", dirPath.c_str(), file->d_name);
            showAllFiles(filePath); // 递归执行
        } else {
            // 如果需要把路径保存到集合中去，就在这里执行 add 的操作
            LOGI(FILE_TAG, "filePath: %s/%s", dirPath.c_str(), file->d_name);

        }
    }
    closedir(dir);
}

int readFile(const std::string &filePath, char **buffer) {
    std::filebuf *pbuf;
    std::ifstream filestr;
    filestr.open(filePath, std::ios::binary);
    pbuf = filestr.rdbuf();
    int size = static_cast<int>(pbuf->pubseekoff(0, std::ios::end, std::ios::in));
    pbuf->pubseekpos(0, std::ios::in);
    *buffer = new char[size];
    pbuf->sgetn(*buffer, size);
    filestr.close();
    return size;
}

int readFileToVec(const std::string &filePath, std::vector<unsigned char> &buffer) {
    std::filebuf *pbuf;
    std::ifstream filestr;
    filestr.open(filePath, std::ios::binary);
    pbuf = filestr.rdbuf();
    int size = static_cast<int>(pbuf->pubseekoff(0, std::ios::end, std::ios::in));
    pbuf->pubseekpos(0, std::ios::in);
    buffer.resize(static_cast<unsigned int>(size));
    pbuf->sgetn((char *)&buffer[0], size);
    filestr.close();
    return size;
}