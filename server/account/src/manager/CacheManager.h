//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include <memory>
#include <manager/BaseCache.h>
#include <manager/redis/RedisCache.h>

class CacheManager {
public:
    static std::shared_ptr<CacheManager> getInstance();
    int init(const std::string &host, int port);

private:
    std::shared_ptr<BaseCache> cache;
};



