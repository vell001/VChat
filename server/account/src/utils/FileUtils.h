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
#include <iostream>
#include <fstream>

/**
 * 创建单个文件夹
 *
 * @param name  文件夹名
 * @param mode 文件夹权限
 * @return 是否创建成功
 */
bool createDir(const char *name, mode_t mode = 777);

/**
 * 递归创建文件夹
 *
 * @param full_path 完整文件夹路径
 * @param mode 文件夹权限
 * @return 是否创建成功
 */
bool createDirTree(const std::string &full_path, mode_t mode = 777);

/**
 * 将文件内容读取到字符串内
 *
 * @param filePath 文件路径
 * @return 文件内容字符串
 */
std::string readFileToStr(const std::string &filePath);