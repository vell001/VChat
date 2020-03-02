//
// Created by vellhe on 2020/2/18.
//

#include "GlobalConfig.h"

std::shared_ptr<GlobalConfig> GlobalConfig::getInstance() {
    static std::shared_ptr<GlobalConfig> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<GlobalConfig>(new GlobalConfig());
    }
    return instance;
}

void GlobalConfig::init(const std::string &configPath) {
//    if (config.ReadFile(configPath)) {
//        LOG(INFO) << "成功读取配置文件: " << configPath;
//    } else {
//        LOG(ERROR) << "读取配置文件失败，使用默认参数" << configPath;
//    }

    Json::Reader reader;
    std::ifstream in(configPath);
    if (!reader.parse(in, config, false)) {
        LOG(ERROR) << "读取配置文件失败，使用默认参数: " << configPath;
        return;
    }

    Json::FastWriter writer;
    LOG(INFO) << "成功读取配置文件: " << writer.write(config);
}

std::string GlobalConfig::getDBHost() {
    return config.get("db_host", "192.168.43.96").asString();
}

int GlobalConfig::getDBPort() {
    return config.get("db_port", 3306).asInt();
}

std::string GlobalConfig::getDBName() {
    return config.get("db_name", std::string("account")).asString();
}

std::string GlobalConfig::getDBUser() {
    return config.get("db_user", std::string("root")).asString();
}

std::string GlobalConfig::getDBPassword() {
    return config.get("db_password", std::string("vell001")).asString();
}

std::string GlobalConfig::getDBCharset() {
    return config.get("db_charset", std::string("utf8")).asString();
}

std::string GlobalConfig::getRedisHost() {
    return config.get("redis_host", "127.0.0.1").asString();
}

int GlobalConfig::getRedisPort() {
    return config.get("redis_port", 6379).asInt();
}

string GlobalConfig::getAESKeyHex() {
    return config.get("aes_key", "DFB370401839D4ABD1698202B2281C149AB32FA7C30C9847868513D6D77C05BF").asString();
}

string GlobalConfig::getAESIvHex() {
    return config.get("aes_iv", "1CC67545BD8208A8236698F0AF49A58A").asString();
}

int GlobalConfig::getTokenExpirationPeriodSec() {
    return config.get("token_expiration_period_sec", 6).asInt();
}

int GlobalConfig::getRefreshTokenExpirationPeriodSec() {
    return config.get("refresh_token_expiration_period_sec", 12).asInt();
}
