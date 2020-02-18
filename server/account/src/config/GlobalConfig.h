//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include <memory>
#include "utils/Config.h"
#include <glog/logging.h>
#include "json/json.h"

class GlobalConfig {
private:
//    Config config;
    Json::Value config;
public:
    static std::shared_ptr<GlobalConfig> getInstance();

    void init(const std::string &configPath);

    std::string getDBHost();

    int getDBPort();

    string getDBName();

    string getDBUser();

    string getDBPassword();

    string getDBCharset();
};



