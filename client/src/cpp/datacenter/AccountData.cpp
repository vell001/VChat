//
// Created by vellhe on 2020-02-08.
//

#include "AccountData.h"

std::shared_ptr<AccountData> AccountData::getInstance() {
    static std::shared_ptr<AccountData> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<AccountData>(new AccountData());
    }
    return instance;
}

AccountData::AccountData() {
    // 创建文件夹
    createDirTree(global::AccountVariable::vchatSDCardBasePath);
}

std::shared_ptr<account_djinni::AccountInfo> AccountData::getAccountInfo() {
    if (accountInfo == nullptr) {
        // 从文件中加载
        Json::Reader reader;
        Json::Value root;
        std::ifstream in(global::AccountVariable::accountInfoSavePath);
        if (reader.parse(in, root, false) && !root.isNull()) {
            accountInfo = std::shared_ptr<account_djinni::AccountInfo>(
                    new account_djinni::AccountInfo(
                            root.get("username", "").asString(),
                            root.get("phoneNumber", "").asString(),
                            root.get("email", "").asString(),
                            root.get("extra", "").asString(),
                            account_djinni::TokenMsg(
                                    root.get("token.token", "").asString(),
                                    root.get("token.expiration_time_sec", 0).asInt()
                            )
                    ));
        }
    }
    return accountInfo;
}

void AccountData::setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info) {
    if (info == nullptr) {
        // 删除账号信息
        remove(global::AccountVariable::accountInfoSavePath.c_str());
    } else {
        // 保存到本地文件
        Json::Value root;
        root["username"] = info->username;
        root["phoneNumber"] = info->phoneNumber;
        root["email"] = info->email;
        root["extra"] = info->extra;
        root["token.token"] = info->token.token;
        root["token.expiration_time_sec"] = info->token.expiration_time_sec;
        Json::FastWriter fast;

        std::ofstream out(global::AccountVariable::accountInfoSavePath);
        out << fast.write(root);
        out.close();
    }
    accountInfo = info;
}

