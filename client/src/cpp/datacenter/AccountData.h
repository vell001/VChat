//
// Created by vellhe on 2020-02-08.
//

#pragma once

#include "account_info.hpp"
#include <string>

class AccountData {
public:
    static std::shared_ptr<AccountData> getInstance();

    std::shared_ptr<account_djinni::AccountInfo> getAccountInfo();

    void setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info);

private:
    std::shared_ptr<account_djinni::AccountInfo> accountInfo;
};
