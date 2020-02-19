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

    std::string username;
    cache->getValue("username",username);
    cache->setValue("username","vell002");
    cache->getValue("username",username);
    LOG(INFO) << "username: " <<username;
    cache->deleteKey("username");
    return code;
}
