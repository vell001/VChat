//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include <memory>
#include <manager/BaseCache.h>
#include <manager/redis/RedisCache.h>
#include <utils/StringUtils.h>

class CacheManager {
public:
    static std::shared_ptr<CacheManager> getInstance();

    int init(const std::string &host, int port);

    bool saveToken(const std::string &token, double expirationTimeSec);

    bool deleteToken(const std::string &token);

    bool getToken(const std::string &token, double &expirationTimeSec);

private:
    std::shared_ptr<BaseCache> cache;

};



