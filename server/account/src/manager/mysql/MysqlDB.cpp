//
// Created by vellhe on 2020/2/18.
//

#include "MysqlDB.h"

MysqlDB::MysqlDB() {}

int MysqlDB::connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                     const std::string &password, const std::string &charset) {
    this->mHost = host;
    this->mPort = port;
    this->mDBName = dbName;
    this->mUser = user;
    this->mPassword = password;
    this->mCharset = charset;

    if (mysql_init(&mysql) == nullptr) {
        return global::DBCode::CONN_INIT_ERR;
    }

    if (mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), dbName.c_str(), port, nullptr, 0) ==
        nullptr) {
        return global::DBCode::CONN_ERR;
    }

    // 自动重连
    char reconnectOk = 0;
    mysql_options(&mysql, MYSQL_OPT_RECONNECT, &reconnectOk);
    LOG(INFO) << "mysql_options MYSQL_OPT_RECONNECT: " << (int) reconnectOk;

    if (mysql_set_character_set(&mysql, charset.c_str()) != 0) {
        return global::DBCode::CONN_CHARSET_ERR;
    }
    return global::DBCode::OK;
}

void MysqlDB::reconnect() {
    LOG(INFO) << "reconnect";
    disconnect();
    connect(mHost, mPort, mDBName, mUser, mPassword, mCharset);
}

void MysqlDB::disconnect() {
    mysql_close(&mysql);
}

int MysqlDB::execSQL(const char *sql, int retColSize, DB_TABLE_PTR ret) {
    int query_result = -1;

    // 重试三次
    int retryCount = 3;
    while (retryCount > 0) {
        try {
            query_result = mysql_real_query(&mysql, sql, (unsigned int) strlen(sql));
        } catch (const std::exception &e) {
            LOG(ERROR) << "mysql_query error: " << query_result << " sql: " << sql;
            return global::DBCode::QUERY_ERR;
        }

        if (query_result == 1) {
            // TODO 考虑连接断开重连 CR_SERVER_LOST or SERVER_GONE_ERROR
            reconnect();
        } else {
            break;
        }
        retryCount--;
    }

    if (query_result != 0) {
        LOG(ERROR) << "mysql_query error: " << query_result << " sql: " << sql;
        return global::DBCode::QUERY_ERR;
    }

    MYSQL_ROW row;
    MYSQL_RES *res;

    if (retColSize < 0 || ret == nullptr) {
        // 不需要查询结果，直接返回
        return global::DBCode::OK;
    }

    res = mysql_store_result(&mysql);
    if (res == nullptr) {
        // 结果为空
        return global::DBCode::OK;
    }

    while (row = mysql_fetch_row(res)) {
        auto retRow = DB_ROW_PTR(new DB_ROW());
        for (uint i = 0; i < retColSize; i++) {
            if (row[i] == nullptr) {
                retRow->emplace_back(std::string());
            } else {
                retRow->emplace_back(std::string(row[i]));
            }
        }
        ret->push_back(retRow);
    }

    mysql_free_result(res);

    return global::DBCode::OK;
}
