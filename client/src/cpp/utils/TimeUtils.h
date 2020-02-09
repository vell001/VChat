//
// Created by vell on 19-3-27.
//
#pragma once

#include <Platform.h>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

long long nowNs();

long long nowMs();

double nowSec();

void nowStr(std::string &str);

#define TS(name) long long t_##name = nowNs()
#define TE(name) TLog("TIMER_" #name ": %0.3fms\n",(nowNs() - t_##name) / 1000000.0)