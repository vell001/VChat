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
    // TODO 完全列举对应的sql字段类型 https://dev.mysql.com/doc/refman/8.0/en/c-api-prepared-statement-type-codes.html
    enum KeyType {
        NUL,
        INT,
        FLOAT,
        DOUBLE,
        STR_128, // 128字节 String
        STR_512
    };

    virtual int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                        const std::string &password, const std::string &charset) { return global::DBCode::ERR; }

    virtual void reconnect() {}

    virtual void disconnect() {}

    virtual int
    execSQL(const char *sql, int retColSize, DB_TABLE_PTR ret) { return global::DBCode::ERR; }

    /**
     * PreparedStatement执行SQL，无返回值，INSERT、UPDATE、DELETE等
     * @param sql
     * @param keyTypes sql参数类型
     * @param values sql参数值
     * @param affectedRows 影响行数
     * @return 状态码
     */
    virtual int execStmt(const std::string &sql, const std::vector<KeyType> &keyTypes,
                         const std::vector<std::string> &values, int &affectedRows) { return global::DBCode::ERR; }

    /**
     * PreparedStatement执行SQL，有返回值，SELECT
     * @param sql
     * @param keyTypes sql参数类型
     * @param values sql参数值
     * @param retColTypes 返回值字段类型
     * @param ret 返回值
     * @return
     */
    virtual int execStmtFetch(const std::string &sql, const std::vector<KeyType> &keyTypes,
                              const std::vector<std::string> &values, const std::vector<KeyType> &retColTypes,
                              DB_TABLE_PTR ret) { return global::DBCode::ERR; }

};