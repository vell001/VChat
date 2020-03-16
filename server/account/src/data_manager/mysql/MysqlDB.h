//
// Created by vellhe on 2020/2/18.
//

#pragma once

#include "mysql/mysql.h"
#include "mysql/errmsg.h"
#include "data_manager/BaseDB.h"
#include <glog/logging.h>
#include <map>
#include "utils/StringUtils.h"

/**
 * mysql数据库服务实现
 */
class MysqlDB : public BaseDB {
public:
    MysqlDB();
    virtual ~MysqlDB();

    int connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                const std::string &password, const std::string &charset) override;

    void reconnect() override;

    void disconnect() override;

    int execSQL(const char *sql, int retColSize, DB_TABLE_PTR ret) override;

    int execStmt(const std::string &sql, const std::vector<KeyType> &keyTypes,
                 const std::vector<std::string> &values, int &affectedRows) override;

    int
    execStmtFetch(const std::string &sql, const std::vector<KeyType> &keyTypes, const std::vector<std::string> &values,
                  const std::vector<KeyType> &retColTypes, DB_TABLE_PTR ret) override;

private:
    MYSQL mysql;

    std::string mHost;
    int mPort;
    std::string mDBName;
    std::string mUser;
    std::string mPassword;
    std::string mCharset;

    /**
     * PreparedStatement对应变量抽象类
     */
    class StmtBuffer {
    public:
        MYSQL_STMT *stmt = nullptr;

        // bind cache
        int keyNum = 0;
        MYSQL_BIND *bind;
        char **buffer = nullptr;
        int *buffer_length = nullptr;
        bool *is_null = nullptr;
        unsigned long *length = nullptr;
        bool *error = nullptr;


        StmtBuffer(int keyNum) : keyNum(keyNum) {
            bind = new MYSQL_BIND[keyNum];
            memset(bind, 0, keyNum * sizeof(MYSQL_BIND));
            buffer = new char *[keyNum];
            memset(buffer, 0, keyNum * sizeof(char *));
            buffer_length = new int[keyNum];
            memset(buffer_length, 0, keyNum * sizeof(int));
            is_null = new bool[keyNum];
            memset(is_null, 0, keyNum * sizeof(bool));
            length = new unsigned long[keyNum];
            memset(length, 0, keyNum * sizeof(unsigned long));
            error = new bool[keyNum];
            memset(error, 0, keyNum * sizeof(bool));
        }


        virtual ~StmtBuffer() {
            delete[] (bind);
            for (int i = 0; i < keyNum; i++) {
                char *s = buffer[i];
                if (s != nullptr) {
                    delete[] (s);
                }
            }
            delete[] (buffer);
            delete[] (buffer_length);
            delete[] (is_null);
            delete[] (length);
            delete[] (error);
        };
    };

    // 缓存Stmt
    std::map<std::string, std::shared_ptr<StmtBuffer> > stmtCaches;

    int getStmtCache(std::shared_ptr<StmtBuffer> &stmtCache,
                     const std::string &sql, const std::vector<KeyType> &keyTypes);

    void bindBuffer(const std::vector<KeyType> &keyTypes, std::shared_ptr<StmtBuffer> stmtCache);

};
