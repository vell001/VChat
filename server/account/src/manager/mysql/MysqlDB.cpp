//
// Created by vellhe on 2020/2/18.
//

#include "MysqlDB.h"

MysqlDB::MysqlDB() {}

int MysqlDB::connect(const std::string &host, int port, const std::string &dbName, const std::string &user,
                     const std::string &password, const std::string &charset) {
    if (mysql_init(&mysql) == nullptr) {
        return global::DBCode::CONN_INIT_ERR;
    }

    if (mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), dbName.c_str(), port, nullptr, 0) ==
        nullptr) {
        return global::DBCode::CONN_ERR;
    }

    if (mysql_set_character_set(&mysql, charset.c_str()) != 0) {
        return global::DBCode::CONN_CHARSET_ERR;
    }
    return global::DBCode::OK;
}

void MysqlDB::disconnect() {
    mysql_close(&mysql);
}

int MysqlDB::execSQL(const char *sql, int retColSize, std::vector<std::vector<std::string> > &ret) {
    int query_result = -1;
    try {
        query_result = mysql_query(&mysql, sql);
    } catch (const std::exception &e) {
        //释放写锁
        return global::DBCode::QUERY_ERR;
    }

    if (query_result != 0) {
        return global::DBCode::QUERY_ERR;
    }

    MYSQL_ROW row;
    MYSQL_RES *res;

    if (retColSize < 0) {
        // 不需要查询结果，直接返回
        return global::DBCode::OK;
    }

    res = mysql_store_result(&mysql);
    if (res == nullptr) {
        // 结果为空
        return global::DBCode::QUERY_RET_EMPTY;
    }

    while (row = mysql_fetch_row(res)) {
        std::vector<std::string> retRow;
        for (uint i = 0; i < retColSize; i++) {
            retRow.emplace_back(std::string(row[i]));
        }
        ret.push_back(retRow);
    }

    mysql_free_result(res);

    return global::DBCode::OK;
}