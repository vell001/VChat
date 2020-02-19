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

template<typename ... Args>
std::string strFormat(const std::string &format, Args ... args);

std::string strFmt(const std::string &fmt_str, ...);

bool startsWith(const char *str, const char *pre);

int strAsInt(const std::string &s);

bool regMatch(const std::string &pattern, const std::string &text);

std::string randStr(int len);