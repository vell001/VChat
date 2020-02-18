//
// Created by vellhe on 2020/2/11.
//

#include "DBManager.h"

std::shared_ptr<DBManager> DBManager::getInstance() {
    static std::shared_ptr<DBManager> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<DBManager>(new DBManager());
    }
    return instance;
}

int DBManager::init(const std::string &host, int port, const std::string &dbName, const std::string &user,
                    const std::string &password, const std::string &charset) {
    db = std::shared_ptr<BaseDB>(new MysqlDB());
    int code = db->connect(host, port, dbName, user, password, charset);
    if (code != global::DBCode::OK) {
        db = nullptr;
        LOG(ERROR) << "db connect error: " << code;
        return code;
    }
}
