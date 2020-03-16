//
// Created by vellhe on 2020/2/11.
//

#pragma once

#include "./mysql/MysqlDB.h"
#include "BaseDB.h"
#include <memory>
#include <glog/logging.h>
#include <model/AccountModel.h>
#include "utils/StringUtils.h"
#include "utils/ReadWriteLocker.h"

/**
 * 数据库管理器，管理所有数据库的业务操作
 */
class DBManager {
public:
    /**
     * 获取数据库管理器
     * @return 管理器指针
     */
    static std::shared_ptr<DBManager> getInstance();

    /**
     * 初始化数据库管理器
     *
     * @param host
     * @param port
     * @param dbName
     * @param user
     * @param password
     * @param charset
     * @return 状态码
     */
    int init(const std::string &host, int port, const std::string &dbName, const std::string &user,
             const std::string &password, const std::string &charset);

    /**
     * 根据用户名获取用户信息
     *
     * @param username 要获取的用户名
     * @param code 状态码
     * @return 用户信息对象指针
     */
    std::shared_ptr<AccountModel> getAccountByUsername(const std::string &username, int &code);

    /**
     * 添加用户到数据库
     *
     * @param accountModel 用户信息
     * @return 状态码
     */
    int addAccount(std::shared_ptr<AccountModel> accountModel);

private:
    std::shared_ptr<BaseDB> db = nullptr; // 数据库实例

    /**
     * 用户表不存在则创建
     *
     * @return 状态码
     */
    int createAccountTable();

    ReadWriteLocker locker; // 读写控制锁
};



