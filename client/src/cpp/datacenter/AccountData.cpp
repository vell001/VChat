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

std::shared_ptr<account_djinni::AccountInfo> AccountData::getAccountInfo() {
    if(accountInfo == nullptr) {
        // 从文件中加载

    }
    return accountInfo;
}

void AccountData::setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info) {
    if(info == nullptr) {
        // 删除账号信息

    } else {
        // 保存到本地文件

    }
    accountInfo = info;
}
