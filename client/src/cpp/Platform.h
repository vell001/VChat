//
// Created by vellhe on 2020-02-08.
//
#pragma once
#define IS_DEBUG 1

#if __ANDROID__
    #include "xlogger/android_xlog.h" // 使用xlog
    #include "sys/system_properties.h"
    #include "string"

    #define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
    #define FILE_TAG __FILENAME__ // 自动获取源代码文件名，可作为日志TAG

    #if IS_DEBUG
        #define TLog(...) LOGD(FILE_TAG, __VA_ARGS__) // 打印测试日志，正式环境中不IS_DEBUG开关需要关掉
    #else
        #define TLog(...)
    #endif

#elif __APPLE__
    #import <stdio.h>

    #if IS_DEBUG
        #define TLog(fmt, ...) printf("%s: ",__FILE__);printf((fmt), ##__VA_ARGS__);printf("\n");
    #else
        #define TLog(fmt, ...)
    #endif
#endif