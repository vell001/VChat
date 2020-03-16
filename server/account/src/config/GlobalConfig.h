//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include <memory>
#include <glog/logging.h>
#include "json/json.h"
#include <fstream>
#include "utils/FileUtils.h"

/**
 * 全局配置信息
 */
class GlobalConfig {
private:
    Json::Value config; // 配置信息存储实例
public:
    /**
     * 获取配置信息实例
     *
     * @return 配置信息制作
     */
    static std::shared_ptr<GlobalConfig> getInstance();

    /**
     * 初始化配置信息
     *
     * @param configPath 配置信息存储路径
     */
    void init(const std::string &configPath);

    /**
     * 数据库host
     * @return
     */
    std::string getDBHost();

    /**
     * 数据库port
     * @return
     */
    int getDBPort();

    /**
     * 数据库名
     * @return
     */
    std::string getDBName();

    /**
     * 数据库用户名
     * @return
     */
    std::string getDBUser();

    /**
     * 数据库密码
     *
     * @return
     */
    std::string getDBPassword();

    /**
     * 数据库字符编码
     * @return
     */
    std::string getDBCharset();

    /**
     * 缓存服务host
     * @return
     */
    std::string getRedisHost();

    /**
     * 缓存服务port
     * @return
     */
    int getRedisPort();

    /**
     * AES 密钥，16进制编码
     * @return
     */
    std::string getAESKeyHex();

    /**
     * AES 初始向量，16进制编码
     * @return
     */
    std::string getAESIvHex();

    /**
     * token过期周期
     * @return
     */
    int getTokenExpirationPeriodSec();

    /**
     * refresh token 过期周期
     * @return
     */
    int getRefreshTokenExpirationPeriodSec();

    /**
     * CA机构根证书
     * @return
     */
    std::string getSslCARootCert();

    /**
     * 服务私钥
     * @return
     */
    std::string getSslServerKey();

    /**
     * 服务证书
     * @return
     */
    std::string getSslServerCert();
};



