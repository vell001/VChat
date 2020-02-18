//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include "mysql/mysql.h"
#include "manager/BaseDB.h"

class MysqlDB : public BaseDB {
public:
    MysqlDB();

    int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                const std::string &password, const std::string &charset) override;

    void disconnect() override;

    int execSQL(const char *sql, int retColSize, std::vector<std::vector<std::string> > &ret) override;

private:
    MYSQL mysql;
};
