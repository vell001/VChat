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

int MysqlDB::execStmt(const std::string &sql, const std::vector<KeyType> &keyTypes,
                      const std::vector<std::string> &values, int &affectedRows) {
    if (keyTypes.size() != values.size()) {
        LOG(ERROR) << "execStmt param error, keyTypes.size() != values.size(): " << keyTypes.size() << " : "
                   << values.size();
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }
    if (keyTypes.empty()) {
        LOG(ERROR) << "execStmt param error, keyTypes.empty()";
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    int keyNum = keyTypes.size();
    std::shared_ptr<StmtBuffer> stmtBuffer;
    int bindCode = getStmtCache(stmtBuffer, sql, keyTypes);
    if (bindCode != global::DBCode::OK) {
        return bindCode;
    }

    unsigned long paramCount = mysql_stmt_param_count(stmtBuffer->stmt);
    if (paramCount != keyNum) {
        LOG(ERROR) << "execStmt param error, paramCount != keyNum: " << paramCount << " : " << keyNum;
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmtBuffer->stmt, stmtBuffer->bind)) {
        LOG(ERROR) << "mysql_stmt_bind_param() failed " << mysql_stmt_error(stmtBuffer->stmt);
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    // 数据赋值
    for (int i = 0; i < keyNum; i++) {
        const std::string &value = values[i];
        memcpy(stmtBuffer->buffer[i], value.c_str(), value.size());
        stmtBuffer->length[i] = value.size();
    }

    // 重试三次
    int retryCount = 3;
    int code;
    while (retryCount > 0) {
        code = mysql_stmt_execute(stmtBuffer->stmt);
        if (code != 0) {
            LOG(ERROR) << "mysql_stmt_execute(), failed" << mysql_stmt_error(stmtBuffer->stmt);
            if (code == 1 || code == 2013 || code == 2006 || code == 2000) {
                reconnect();
            } else {
                return global::DBCode::QUERY_STMT_ERR;
            }
        } else {
            break;
        }
        retryCount--;
    }
    if (code != 0) {
        return global::DBCode::QUERY_STMT_ERR;
    }


    affectedRows = (int) mysql_stmt_affected_rows(stmtBuffer->stmt);

    return global::DBCode::OK;
}

int MysqlDB::execStmtFetch(const std::string &sql, const std::vector<KeyType> &keyTypes,
                           const std::vector<std::string> &values, const std::vector<KeyType> &retColTypes,
                           DB_TABLE_PTR ret) {
    if (keyTypes.size() != values.size()) {
        LOG(ERROR) << "execStmtFetch param error, keyTypes.size() != values.size(): " << keyTypes.size() << " : "
                   << values.size();
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }
    if (keyTypes.empty()) {
        LOG(ERROR) << "execStmtFetch param error, keyTypes.empty()";
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    int keyNum = keyTypes.size();
    std::shared_ptr<StmtBuffer> stmtBuffer;
    int bindCode = getStmtCache(stmtBuffer, sql, keyTypes);
    if (bindCode != global::DBCode::OK) {
        return bindCode;
    }

    unsigned long paramCount = mysql_stmt_param_count(stmtBuffer->stmt);
    if (paramCount != keyNum) {
        LOG(ERROR) << "execStmt param error, paramCount != keyNum: " << paramCount << " : " << keyNum;
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    /* Bind the buffers */
    if (mysql_stmt_bind_param(stmtBuffer->stmt, stmtBuffer->bind)) {
        LOG(ERROR) << "mysql_stmt_bind_param() failed" << mysql_stmt_error(stmtBuffer->stmt);
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    /* Fetch result set meta information */
    MYSQL_RES *prepare_meta_result = mysql_stmt_result_metadata(stmtBuffer->stmt);
    if (!prepare_meta_result) {
        LOG(ERROR) << "mysql_stmt_result_metadata(), returned no meta information "
                   << mysql_stmt_error(stmtBuffer->stmt);
    }

    /* Get total columns in the query */
    int retColNum = retColTypes.size();
    int column_count = (int) mysql_num_fields(prepare_meta_result);
    if (column_count != retColNum) {
        LOG(ERROR) << "execStmtFetch param error, column_count != retColTypes.size()";
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    // 数据赋值
    for (int i = 0; i < keyNum; i++) {
        const std::string &value = values[i];
        memcpy(stmtBuffer->buffer[i], value.c_str(), value.size());
        stmtBuffer->length[i] = value.size();
    }

    // 重试三次
    int retryCount = 3;
    int code;
    while (retryCount > 0) {
        code = mysql_stmt_execute(stmtBuffer->stmt);
        if (code != 0) {
            LOG(ERROR) << "mysql_stmt_execute(), failed" << mysql_stmt_error(stmtBuffer->stmt) << " code: " << code;
            if (code == 1 || code == 2013 || code == 2006 || code == 2000) {
                reconnect();
            } else {
                return global::DBCode::QUERY_STMT_ERR;
            }
        } else {
            break;
        }
        retryCount--;
    }
    if (code != 0) {
        return global::DBCode::QUERY_STMT_ERR;
    }

    // 获取ret
    std::shared_ptr<StmtBuffer> retStmtBuffer = std::shared_ptr<StmtBuffer>(new StmtBuffer(retColNum));
    retStmtBuffer->stmt = stmtBuffer->stmt;
    bindBuffer(retColTypes, retStmtBuffer);
    /* Bind the result buffers */
    if (mysql_stmt_bind_result(retStmtBuffer->stmt, retStmtBuffer->bind)) {
        LOG(ERROR) << "mysql_stmt_bind_result() failed " << mysql_stmt_error(retStmtBuffer->stmt);
        return global::DBCode::QUERY_STMT_PARAM_ERR;
    }

    // 读取buffer数据
    /* Now buffer all results to client (optional step) */
    if (mysql_stmt_store_result(retStmtBuffer->stmt)) {
        LOG(ERROR) << "mysql_stmt_store_result() failed " << mysql_stmt_error(retStmtBuffer->stmt);
        return global::DBCode::QUERY_STMT_RET_ERR;
    }

    /* Fetch all rows */
    while (!mysql_stmt_fetch(retStmtBuffer->stmt)) {
        auto retRow = DB_ROW_PTR(new DB_ROW());
        for (int i = 0; i < retColNum; i++) {
            retRow->emplace_back(std::string(retStmtBuffer->buffer[i], retStmtBuffer->length[i]));
        }
        ret->push_back(retRow);
    }

    /* Free the prepared result metadata */
    mysql_free_result(prepare_meta_result);

    return global::DBCode::OK;
}

int MysqlDB::getStmtCache(std::shared_ptr<StmtBuffer> &stmtCache, const std::string &sql,
                          const std::vector<KeyType> &keyTypes) {
    int keyNum = keyTypes.size();

    auto iter = stmtCaches.find(sql);
    if (iter != stmtCaches.end()) {
        // 找到缓存，使用缓存
        stmtCache = iter->second;
    }

    if (stmtCache == nullptr || keyNum != stmtCache->keyNum) {
        stmtCaches.erase(sql);
        stmtCache = nullptr;
    }

    if (stmtCache == nullptr) {
        // 没找到缓存，创建缓存
        stmtCache = std::shared_ptr<StmtBuffer>(new StmtBuffer(keyNum));

        stmtCache->stmt = mysql_stmt_init(&mysql);
        if (!stmtCache->stmt) {
            LOG(ERROR) << "execStmt mysql_stmt_init error, out of memory";
            return global::DBCode::QUERY_STMT_INIT_ERR;
        }
        // 重试三次
        int retryCount = 3;
        int code;
        while (retryCount > 0) {
            code = mysql_stmt_prepare(stmtCache->stmt, sql.c_str(), sql.size());
            if (code != 0) {
                LOG(ERROR) << " mysql_stmt_prepare() failed " << mysql_stmt_error(stmtCache->stmt) << " code: " << code;
                if (code == 1 || code == 2013 || code == 2006 || code == 2000) {
                    reconnect();
                } else {
                    return global::DBCode::QUERY_STMT_INIT_ERR;
                }
            } else {
                break;
            }
            retryCount--;
        }
        if (code != 0) {
            return global::DBCode::QUERY_STMT_INIT_ERR;
        }

        bindBuffer(keyTypes, stmtCache);

        // 保存到缓存，供下次使用
//        stmtCaches[sql] = stmtCache;
    }

    return global::DBCode::OK;
}

void
MysqlDB::bindBuffer(const std::vector<KeyType> &keyTypes, std::shared_ptr<StmtBuffer> stmtCache) {
    int keyNum = keyTypes.size();

    // 绑定数据
    for (int i = 0; i < keyNum; i++) {
        KeyType keyType = keyTypes[i];
        // TODO 支持更多类型的statement，暂时只会用到这几类，参考:https://dev.mysql.com/doc/refman/8.0/en/mysql-stmt-fetch.html
        if (keyType == INT) {
            stmtCache->bind[i].buffer_type = MYSQL_TYPE_LONG;
            stmtCache->bind[i].buffer_length = sizeof(int);
            stmtCache->buffer[i] = new char[stmtCache->bind[i].buffer_length];
        } else if (keyType == STR_128) {
            stmtCache->bind[i].buffer_type = MYSQL_TYPE_STRING;
            stmtCache->bind[i].buffer_length = 128;
            stmtCache->buffer[i] = new char[stmtCache->bind[i].buffer_length];
        } else if (keyType == STR_512) {
            stmtCache->bind[i].buffer_type = MYSQL_TYPE_STRING;
            stmtCache->bind[i].buffer_length = 512;
            stmtCache->buffer[i] = new char[stmtCache->bind[i].buffer_length];
        }

        stmtCache->bind[i].buffer = stmtCache->buffer[i];
        stmtCache->bind[i].is_null = &stmtCache->is_null[i];
        stmtCache->bind[i].length = &stmtCache->length[i];
        stmtCache->bind[i].error = &stmtCache->error[i];
    }
}

MysqlDB::~MysqlDB() {
    for (auto &stmtCache : stmtCaches) {
        LOG(INFO) << "release statement " << stmtCache.first;
        if (stmtCache.second->stmt != nullptr) {
            mysql_stmt_close(stmtCache.second->stmt);
            stmtCache.second->stmt = nullptr;
        }
    }
}
