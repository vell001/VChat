//
// Created by vellhe on 2020/2/11.
//

#pragma once

#include "./mysql/MysqlDB.h"
#include "BaseDB.h"
#include <memory>
#include <glog/logging.h>
#include <model/AccountModel.h>
#include "utils/StringUtils.h"
#include "utils/ReadWriteLocker.h"

class DBManager {
public:
    static std::shared_ptr<DBManager> getInstance();

    int init(const std::string &host, int port, const std::string &dbName, const std::string &user,
             const std::string &password, const std::string &charset);

    std::shared_ptr<AccountModel> getAccountByUsername(const std::string &username, int &code);
    int addAccount(std::shared_ptr<AccountModel> accountModel);
private:
    std::shared_ptr<BaseDB> db = nullptr;
    int createAccountTable();
    ReadWriteLocker locker;
};



