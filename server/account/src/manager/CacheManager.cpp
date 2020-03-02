//
// Created by vellhe on 2020/2/19.
//

#include "CacheManager.h"

std::shared_ptr<CacheManager> CacheManager::getInstance() {
    static std::shared_ptr<CacheManager> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<CacheManager>(new CacheManager());
    }
    return instance;
}

int CacheManager::init(const std::string &host, int port) {
    cache = std::shared_ptr<BaseCache>(new RedisCache());
    int code = cache->connect(host, port);
    if (code != global::CacheCode::OK) {
        cache = nullptr;
        LOG(ERROR) << "cache connect error: " << code;
        return code;
    }

    // TODO for test
    std::string username;
    cache->getValue("username", username);
    cache->setValue("username", "vell002");
    cache->getValue("username", username);
    LOG(INFO) << "username: " << username;
    cache->deleteKey("username");
    // end test

    return code;
}

bool CacheManager::saveToken(TokenType tokenType, const std::string &username, const std::string &token,
                             double expirationTimeSec) {
    if (cache) {
        Json::Value tokenJson;
        tokenJson["token"] = token;
        tokenJson["expirationTimeSec"] = expirationTimeSec;
        Json::FastWriter fast;

        int code;
        {
            ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
            code = cache->setValue(getTokenKey(tokenType, username), fast.write(tokenJson));
        }
        return code == global::CacheCode::OK;
    }
    return false;
}

bool CacheManager::deleteToken(TokenType tokenType, const std::string &username) {
    if (cache) {
        int code;
        {
            ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
            code = cache->deleteKey(getTokenKey(tokenType, username));
        }
        return code == global::CacheCode::OK;
    }
    return false;
}

bool CacheManager::deleteTokenCheckCorrect(TokenType tokenType, const std::string &username, const std::string &token) {
    if (cache) {
        std::string existTokenJson;
        const std::string &tokenKey = getTokenKey(tokenType, username);

        int code;
        {
            ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);

            code = cache->getValue(tokenKey, existTokenJson);
            if (code == global::CacheCode::OK) {
                Json::Reader reader;
                Json::Value root;
                if (reader.parse(existTokenJson, root)) {
                    std::string existToken = root.get("token", "").asString();
                    if (existToken == token) {
                        code = cache->deleteKey(tokenKey);
                    }
                } else {
                    // 对应值不对，保护性删除
                    cache->deleteKey(tokenKey);
                }
            }
        }
        return code == global::CacheCode::OK;
    }
    return false;
}

bool CacheManager::getToken(TokenType tokenType, const std::string &username, std::string &token,
                            double &expirationTimeSec) {
    if (cache) {
        std::string existTokenJson;
        const std::string &tokenKey = getTokenKey(tokenType, username);

        int code;
        {
            ReadWriteLocker::Holder lock(ReadWriteLocker::READ, locker);
            code = cache->getValue(tokenKey, existTokenJson);
        }

        if (code == global::CacheCode::OK) {
            Json::Reader reader;
            Json::Value root;
            if (reader.parse(existTokenJson, root)) {
                token = root.get("token", "").asString();
                expirationTimeSec = root.get("expirationTimeSec", 0).asInt();
                LOG(INFO) << "getToken: " << token << std::fixed << " " << expirationTimeSec;
                return !token.empty();
            } else {
                LOG(ERROR) << "token json error delete" << existTokenJson;
                // 对应值不对，保护性删除
                {
                    ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
                    cache->deleteKey(tokenKey);
                }
                return false;
            }
        }
        return code == global::CacheCode::OK;
    }
    return false;
}

std::string CacheManager::getTokenKey(CacheManager::TokenType tokenType, const std::string &username) {
    if (tokenType == TOKEN) {
        return username + "_token";
    } else if (tokenType == REFRESH_TOKEN) {
        return username + "_refresh_token";
    }
    return std::string();
}
