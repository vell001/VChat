//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include "mysql/mysql.h"
#include "mysql/errmsg.h"
#include "manager/BaseDB.h"
#include <glog/logging.h>

class MysqlDB : public BaseDB {
public:
    MysqlDB();

    int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                const std::string &password, const std::string &charset) override;

    void reconnect() override;

    void disconnect() override;

    int execSQL(const char *sql, int retColSize, DB_TABLE_PTR ret) override;

private:
    MYSQL mysql;

    std::string mHost;
    int mPort;
    std::string mDBName;
    std::string mUser;
    std::string mPassword;
    std::string mCharset;
};
