//
// Created by vell on 19-3-27.
//
#pragma once

#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

/**
 * 当前时间，纳秒
 *
 * @return
 */
long long nowNs();

/**
 * 当前时间，毫秒
 *
 * @return
 */
long long nowMs();

/**
 * 当前时间，秒
 *
 * @return
 */
double nowSec();

/**
 * 当前时间，字符串格式%Y-%m-%d_%H_%M_%S
 * @param str 输出字符串
 */
void nowStr(std::string &str);