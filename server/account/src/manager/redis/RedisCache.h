//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include "manager/BaseCache.h"
#include "hiredis.h"
#include <glog/logging.h>

class RedisCache:public BaseCache {
public:
    int connect(const std::string &host, int port) override;

    void disconnect() override;

    int getValue(const std::string &key, std::string &value) override;

    int setValue(const std::string &key, const std::string &value) override;

    int deleteKey(const std::string &key) override;

private:
    redisContext *mRedisContext = nullptr;
};



