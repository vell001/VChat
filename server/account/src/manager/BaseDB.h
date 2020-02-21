//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include <string>
#include <vector>
#include "GlobalValues.h"
#include <memory>

typedef std::shared_ptr<std::vector<std::shared_ptr<std::vector<std::string> > > > DB_TABLE_PTR;
typedef std::vector<std::shared_ptr<std::vector<std::string> > > DB_TABLE;
typedef std::shared_ptr<std::vector<std::string> > DB_ROW_PTR;
typedef std::vector<std::string> DB_ROW;

class BaseDB {
public:
    virtual int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                        const std::string &password, const std::string &charset) { return global::DBCode::ERR; }

    virtual void reconnect() {}
    virtual void disconnect() {}

    virtual int
    execSQL(const char *sql, int retColSize, DB_TABLE_PTR ret) { return global::DBCode::ERR; }
};
