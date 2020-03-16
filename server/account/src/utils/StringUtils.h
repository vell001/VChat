//
// Created by vell on 19-5-10.
//
#pragma once

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include <stdarg.h>  // For va_start, etc.
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <ctime>
#include <regex>

/**
 * 字符串format
 *
 * @param fmt_str format格式
 * @param ... 对应参数
 * @return format后的字符串
 */
std::string strFmt(const std::string &fmt_str, ...);

/**
 * string 转int
 *
 * @param s
 * @return
 */
int str2Int(const std::string &s);

/**
 * 字节码转int
 *
 * @param s 输入字节码，存在string中
 * @return int
 */
int buffer2Int(const std::string &s);

/**
 * double 转 string
 * @param d
 * @return
 */
std::string double2Str(double d);

/**
 * string 转 double
 *
 * @param s
 * @return
 */
double str2Double(const std::string &s);

/**
 * 正则是否匹配
 *
 * @param pattern 正则规则
 * @param text 待匹配数据
 * @return 正则是否匹配
 */
bool regMatch(const std::string &pattern, const std::string &text);

/**
 * 生成随机字符串
 *
 * @param len 生成的字符串长度
 * @return 生成的字符串
 */
std::string randStr(int len);