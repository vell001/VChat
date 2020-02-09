//
// Created by vellhe on 2020-02-08.
//

#pragma once

#include "account_info.hpp"

class AccountData {
public:
    static std::shared_ptr<AccountData> getInstance();

    std::shared_ptr<account_djinni::AccountInfo> getAccountInfo();
    void setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info);
};
