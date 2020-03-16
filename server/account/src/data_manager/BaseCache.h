//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include <string>
#include "GlobalValues.h"

/**
 * 缓存基础操作抽象接口类
 */
class BaseCache {
public:
    /**
     * 连接缓存服务
     *
     * @param host
     * @param port
     * @return
     */
    virtual int connect(const std::string &host, int port) { return global::CacheCode::ERR; }

    /**
     * 断开连接
     */
    virtual void disconnect() {}

    /**
     * 获取缓存值
     *
     * @param key
     * @param value 返回值
     * @return 状态码
     */
    virtual int getValue(const std::string &key, std::string &value) {};

    /**
     * 设置缓存值
     *
     * @param key
     * @param value 设置值
     * @return 状态码
     */
    virtual int setValue(const std::string &key, const std::string &value) {};

    /**
     * 删除缓存
     *
     * @param key 需要删除的key
     * @return 状态码
     */
    virtual int deleteKey(const std::string &key) {};
};



