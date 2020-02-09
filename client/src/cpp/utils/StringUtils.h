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

template<typename ... Args>
std::string strFormat(const std::string &format, Args ... args);

std::string strFmt(const std::string fmt_str, ...);

bool startsWith(const char *str, const char *pre);