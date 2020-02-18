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
    if (!reader.parse(configPath, config, false)) {
        LOG(ERROR) << "读取配置文件失败，使用默认参数: " << configPath;
        return;
    }

    Json::FastWriter writer;
    LOG(INFO) << "成功读取配置文件: " << writer.write(config);
}

std::string GlobalConfig::getDBHost() {
    return config.get("db_host", "192.168.1.3").asString();
}

int GlobalConfig::getDBPort() {
    return config.get("db_port", 3306).asInt();
}

std::string GlobalConfig::getDBName() {
    return config.get("db_name", std::string("account")).asString();
}

std::string GlobalConfig::getDBUser() {
    return config.get("user", std::string("root")).asString();
}

std::string GlobalConfig::getDBPassword() {
    return config.get("password", std::string("vell001")).asString();
}

std::string GlobalConfig::getDBCharset() {
    return config.get("charset", std::string("utf8")).asString();
}
