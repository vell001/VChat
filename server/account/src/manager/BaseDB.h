//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include <string>
#include <vector>
#include "GlobalValues.h"

class BaseDB {
public:
    virtual int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                        const std::string &password, const std::string &charset) { return global::DBCode::ERR; }

    virtual void disconnect() {}

    virtual int
    execSQL(const char *sql, int retColSize, std::vector<std::vector<std::string> > &ret) { return global::DBCode::ERR; }
};
