//
// Created by vell on 19-5-10.
//
#pragma once

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "StringUtils.h"
#include <vector>
#include "Platform.h"
#include <iostream>
#include <fstream>

bool createDir(const char *name, mode_t mode = 777);

bool createDirTree(const std::string full_path, mode_t mode = 777);

std::string findDirByStart(const std::string &dirPath, const char *startStr);

void showAllFiles(const std::string &dirPath);

int readFile(const std::string &filePath, char **buffer);

int readFileToVec(const std::string &filePath, std::vector<unsigned char> &buffer);