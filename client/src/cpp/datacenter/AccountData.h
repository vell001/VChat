//
// Created by vellhe on 2020-02-08.
//

#pragma once

#include "account_info.hpp"
#include <string>
#include "utils/FileUtils.h"
#include <GlobalValues.h>
#include "json/json.h"

class AccountData {
public:
    static std::shared_ptr<AccountData> getInstance();

    std::shared_ptr<account_djinni::AccountInfo> getAccountInfo();

    void setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info);

    AccountData();

private:
    std::shared_ptr<account_djinni::AccountInfo> accountInfo;
};
