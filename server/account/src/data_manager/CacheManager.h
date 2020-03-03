//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include <memory>
#include <data_manager/BaseCache.h>
#include <data_manager/redis/RedisCache.h>
#include <utils/StringUtils.h>
#include <utils/ReadWriteLocker.h>
#include "json/json.h"

class CacheManager {
public:
    static std::shared_ptr<CacheManager> getInstance();

    int init(const std::string &host, int port);

    enum TokenType {
        TOKEN,
        REFRESH_TOKEN
    };

    bool saveToken(TokenType tokenType, const std::string &username, const std::string &token, double expirationTimeSec);

    bool deleteToken(TokenType tokenType, const std::string &username);

    // 会检查token是否正确再删除，保证不会误删
    bool deleteTokenCheckCorrect(TokenType tokenType, const std::string &username, const std::string &token);

    bool getToken(TokenType tokenType, const std::string &username, std::string &token, double &expirationTimeSec);

private:
    std::shared_ptr<BaseCache> cache;
    ReadWriteLocker locker;

    std::string getTokenKey(TokenType tokenType, const std::string &username);
};



