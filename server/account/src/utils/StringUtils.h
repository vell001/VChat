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

template<class T>
std::string T_as_string(const T &t);


/* static */
template<class T>
T string_as_T(const std::string &s);

int str2Int(const std::string &s);

int buffer2Int(const std::string &s);

std::string double2Str(double d);

double str2Double(const std::string &s);

bool regMatch(const std::string &pattern, const std::string &text);

std::string randStr(int len);