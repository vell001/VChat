//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include <memory>
#include <glog/logging.h>
#include "json/json.h"
#include <fstream>
#include "utils/FileUtils.h"

class GlobalConfig {
private:
    Json::Value config;
public:
    static std::shared_ptr<GlobalConfig> getInstance();

    void init(const std::string &configPath);

    std::string getDBHost();

    int getDBPort();

    std::string getDBName();

    std::string getDBUser();

    std::string getDBPassword();

    std::string getDBCharset();

    std::string getRedisHost();

    int getRedisPort();

    std::string getAESKeyHex();

    std::string getAESIvHex();

    int getTokenExpirationPeriodSec();

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



