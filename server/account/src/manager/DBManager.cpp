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
    // 连接数据库
    db = std::shared_ptr<BaseDB>(new MysqlDB());
    int code = db->connect(host, port, dbName, user, password, charset);
    if (code != global::DBCode::OK) {
        db = nullptr;
        LOG(ERROR) << "db connect error: " << code;
        return code;
    }

    // 初始化数据库表
    code = createAccountTable();
    if (code != global::DBCode::OK) {
        LOG(ERROR) << "createAccountTable error: " << code;
        return code;
    }

    // TODO for test
//    std::shared_ptr<AccountModel> accountModel = std::shared_ptr<AccountModel>(new AccountModel());
//
//    accountModel->setUsername("vell");
//    accountModel->setPassword("row[2]");
//    accountModel->setPasswordSalt("row[3]");
//    accountModel->setPhoneNumber("row[4]");
//    accountModel->setEmail("row[5]");
//    addAccount(accountModel);
    std::shared_ptr<AccountModel> accountModel = getAccountByUsername("vell", code);
    LOG(INFO) << "test getAccountByUsername: " << "id " << accountModel->getId() << " " << accountModel->getUsername();
    // end test

    return global::DBCode::OK;
}

int DBManager::createAccountTable() {
    ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);

    //构建查询语句
    const char *checkTableSql = "SELECT table_name FROM information_schema.TABLES WHERE table_name ='account';";
    auto checkTableRet = DB_TABLE_PTR(new DB_TABLE);
    db->execSQL(checkTableSql, 1, checkTableRet);
    if (checkTableRet->empty()) {
        // 不存在
        const char *createTableSql = "CREATE TABLE account (           "
                                     "            id            INT PRIMARY KEY AUTO_INCREMENT      NOT NULL,   "
                                     "            username      CHAR(128)                           NOT NULL UNIQUE,   "
                                     "            password      CHAR(128)                           NOT NULL,   "
                                     "            password_salt CHAR(128)                           NOT NULL,    "
                                     "            phone_number   CHAR(32)                            ,    "
                                     "            email         CHAR(128)                           ,    "
                                     "            extra         TINYTEXT                              "
                                     "            );";
        int createTableCode = db->execSQL(createTableSql, 0, nullptr);
        if (createTableCode == global::DBCode::OK) {
            LOG(INFO) << "account table created";
        } else {
            LOG(ERROR) << "create account table error: " << createTableCode;
        }
        return createTableCode;
    } else {
        LOG(INFO) << "account table exist";
    }
    return global::DBCode::OK;
}

std::shared_ptr<AccountModel> DBManager::getAccountByUsername(const std::string &username, int &code) {
//    std::string selectAccountSql =
//            "SELECT id, username, password, password_salt, phone_number, email, extra FROM account where username='" +
//            username + "'";
//    DB_TABLE_PTR selectAccountRet = DB_TABLE_PTR(new DB_TABLE);
//
//    {
//        ReadWriteLocker::Holder lock(ReadWriteLocker::READ, locker);
//        code = db->execSQL(selectAccountSql.c_str(), 7, selectAccountRet);
//    }

    std::string selectAccountSql = "SELECT id, username, password, password_salt, phone_number, email, extra FROM account where username=?";
    DB_TABLE_PTR selectAccountRet = DB_TABLE_PTR(new DB_TABLE);
    {
        ReadWriteLocker::Holder lock(ReadWriteLocker::READ, locker);
        std::vector<BaseDB::KeyType> keyTypes;
        std::vector<std::string> values;
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(username);

        std::vector<BaseDB::KeyType> retColTypes;
        retColTypes.emplace_back(BaseDB::INT);
        retColTypes.emplace_back(BaseDB::STR_128);
        retColTypes.emplace_back(BaseDB::STR_128);
        retColTypes.emplace_back(BaseDB::STR_128);
        retColTypes.emplace_back(BaseDB::STR_128);
        retColTypes.emplace_back(BaseDB::STR_128);
        retColTypes.emplace_back(BaseDB::STR_512);

        code = db->execStmtFetch(selectAccountSql, keyTypes, values, retColTypes, selectAccountRet);
    }

    if (code == global::DBCode::OK) {
        LOG(INFO) << selectAccountSql << " succ";
        if (selectAccountRet->empty()) {
            LOG(INFO) << "user not exist: " << username;
            return nullptr;
        }
        if (selectAccountRet->size() > 1) {
            LOG(ERROR) << "multi user: " << username << " count: " << selectAccountRet->size();
        }
        std::vector<std::string> &row = *((*selectAccountRet)[0]);
        std::shared_ptr<AccountModel> accountModel = std::shared_ptr<AccountModel>(new AccountModel());
        accountModel->setId(buffer2Int(row[0]));
        accountModel->setUsername(row[1]);
        accountModel->setPassword(row[2]);
        accountModel->setPasswordSalt(row[3]);
        accountModel->setPhoneNumber(row[4]);
        accountModel->setEmail(row[5]);
        accountModel->setExtra(row[6]);
        return accountModel;
    } else {
        LOG(ERROR) << "selectAccountSql error: " << selectAccountSql << "code: " << code;
    }
    return nullptr;
}

int DBManager::addAccount(std::shared_ptr<AccountModel> accountModel) {
    // TODO 先简单粗暴的拼接sql，后续改成PreparedStatement方式
//    std::string insertAccountSql =
//            "INSERT INTO `account`.`account`(`username`, `password`, `password_salt`, `phone_number`, `email`, `extra`) "
//            "VALUES ('" + accountModel->getUsername() + "', '" + accountModel->getPassword() + "', '" +
//            accountModel->getPasswordSalt() + "', '" + accountModel->getPhoneNumber() + "', '" +
//            accountModel->getEmail() + "', '" + accountModel->getExtra() + "')";
//
//    int insertAccountCode;
//    {
//        ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
//        insertAccountCode = db->execSQL(insertAccountSql.c_str(), 0, nullptr);
//    }
    std::string insertAccountSql =
            "INSERT INTO `account`.`account`(`username`, `password`, `password_salt`, `phone_number`, `email`, `extra`) "
            "VALUES (?,?,?,?,?,?)";

    int insertAccountCode;
    int affectedRows;
    {
        ReadWriteLocker::Holder lock(ReadWriteLocker::WRITE, locker);
        std::vector<BaseDB::KeyType> keyTypes;
        std::vector<std::string> values;
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(accountModel->getUsername());
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(accountModel->getPassword());
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(accountModel->getPasswordSalt());
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(accountModel->getPhoneNumber());
        keyTypes.emplace_back(BaseDB::STR_128);
        values.emplace_back(accountModel->getEmail());
        keyTypes.emplace_back(BaseDB::STR_512);
        values.emplace_back(accountModel->getExtra());

        insertAccountCode = db->execStmt(insertAccountSql, keyTypes, values, affectedRows);
    }

    if (insertAccountCode == global::DBCode::OK) {
        LOG(INFO) << insertAccountSql << " succ affectedRows: " << affectedRows;
    } else {
        LOG(ERROR) << insertAccountSql << " error: " << insertAccountCode;
    }
    return insertAccountCode;
}
