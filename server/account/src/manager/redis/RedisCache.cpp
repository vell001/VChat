//
// Created by vellhe on 2020/2/19.
//

#include "RedisCache.h"

int RedisCache::connect(const std::string &host, int port) {
    mRedisContext = redisConnect(host.c_str(), port);
    if (mRedisContext == nullptr || mRedisContext->err != 0) {
        LOG(ERROR) << "redisConnect error: " << mRedisContext->err;
        return global::CacheCode::CONN_ERR;
    }
    return global::CacheCode::OK;
}

void RedisCache::disconnect() {
    redisFree(mRedisContext);
}

int RedisCache::getValue(const std::string &key, std::string &value) {
    int code = global::CacheCode::OK;
    redisReply *reply = nullptr;
    try {
        reply = (redisReply *) redisCommand(mRedisContext, "GET %s", key.c_str());
        // TODO 区分 REDIS_REPLY_NIL 状态，代表没有数据
        if (nullptr != reply && reply->type == REDIS_REPLY_STRING) {
            value = reply->str;
            code = global::CacheCode::OK;
            LOG(INFO) << "GET " << key << " >>> " << value;
        } else {
            if(reply){
                LOG(ERROR) << "redisCommand reply error type: " << reply->type << " str: " << reply->str << " integer:" << reply->integer;
            } else {
                LOG(ERROR) << "redisCommand reply error";
            }
            code = global::CacheCode::GET_ERR;
        }
    } catch (const std::exception &e) {
        LOG(ERROR) << "redisCommand error: " << e.what();
        code = global::CacheCode::GET_ERR;
    }
    if (reply) {
        freeReplyObject(reply);
        reply = nullptr;
    }
    return code;
}

int RedisCache::setValue(const std::string &key, const std::string &value) {
    int code = global::CacheCode::OK;
    redisReply *reply = nullptr;
    try {
        reply = (redisReply *) redisCommand(mRedisContext, "SET %s %s", key.c_str(), value.c_str());
        if (nullptr != reply && reply->type == REDIS_REPLY_STATUS && strcasecmp(reply->str, "OK") == 0) {
            code = global::CacheCode::OK;
            LOG(INFO) << "SET " << key << " " << value;
        } else {
            LOG(ERROR) << "redisCommand reply error";
            code = global::CacheCode::SET_ERR;
        }
    } catch (const std::exception &e) {
        LOG(ERROR) << "redisCommand error: " << e.what();
        code = global::CacheCode::SET_ERR;
    }
    if (reply) {
        freeReplyObject(reply);
        reply = nullptr;
    }
    return code;
}

int RedisCache::deleteKey(const std::string &key) {
    int code = global::CacheCode::OK;
    redisReply *reply = nullptr;
    try {
        reply = (redisReply *) redisCommand(mRedisContext, "DEL %s", key.c_str());
        if (nullptr != reply && reply->type == REDIS_REPLY_INTEGER) {
            code = global::CacheCode::OK;
            LOG(INFO) << "DEL " << key << " count: " << reply->integer;
        } else {
            LOG(ERROR) << "redisCommand reply error";
            code = global::CacheCode::SET_ERR;
        }
    } catch (const std::exception &e) {
        LOG(ERROR) << "redisCommand error: " << e.what();
        code = global::CacheCode::SET_ERR;
    }
    if (reply) {
        freeReplyObject(reply);
        reply = nullptr;
    }
    return code;
}
