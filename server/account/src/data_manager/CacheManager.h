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

/**
 * 缓存管理器，管理跟缓存相关的所有业务操作
 */
class CacheManager {
public:
    /**
     * 获取缓存管理器
     *
     * @return 缓存管理器指针
     */
    static std::shared_ptr<CacheManager> getInstance();

    /**
     * 初始化管理器
     *
     * @param host
     * @param port
     * @return 状态码
     */
    int init(const std::string &host, int port);

    /**
     * token类型
     */
    enum TokenType {
        TOKEN,
        REFRESH_TOKEN
    };

    /**
     * 保存token到缓存
     *
     * @param tokenType token类型
     * @param username token对应用户名
     * @param token
     * @param expirationTimeSec 过期时间
     * @return 是否保存成功
     */
    bool
    saveToken(TokenType tokenType, const std::string &username, const std::string &token, double expirationTimeSec);

    /**
     * 删除token
     *
     * @param tokenType token类型
     * @param username token对应用户名
     * @return 是否删除成功
     */
    bool deleteToken(TokenType tokenType, const std::string &username);

    /**
     * 会检查token是否正确再删除，保证不会误删
     *
     * @param tokenType token类型
     * @param username token对应用户名
     * @param token 要删除的token值，对应不上则不会删除
     * @return 是否删除成功
     */
    bool deleteTokenCheckCorrect(TokenType tokenType, const std::string &username, const std::string &token);

    /**
     * 获取token
     *
     * @param tokenType
     * @param username 要获取的用户名
     * @param token 返回获取到的token
     * @param expirationTimeSec 返回过期时间
     * @return 是否获取成功
     */
    bool getToken(TokenType tokenType, const std::string &username, std::string &token, double &expirationTimeSec);

private:
    std::shared_ptr<BaseCache> cache; // 缓存服务实例
    ReadWriteLocker locker; // 读写控制锁

    /**
     * 根据token类型和用户名，得到对应缓存服务里存储的key
     *
     * @param tokenType
     * @param username
     * @return 缓存服务存储时用的key
     */
    std::string getTokenKey(TokenType tokenType, const std::string &username);
};



