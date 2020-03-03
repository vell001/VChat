//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include <string>
#include "account/src/GlobalValues.h"

class BaseCache {
public:
    virtual int connect(const std::string &host, int port) { return global::CacheCode::ERR; }

    virtual void disconnect() {}

    virtual int getValue(const std::string &key, std::string &value) {};

    virtual int setValue(const std::string &key, const std::string &value) {};

    virtual int deleteKey(const std::string &key) {};
};



