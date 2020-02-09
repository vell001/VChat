//
// Created by vellhe on 2020-02-08.
//

#include "AccountData.h"
#include "../../../../../../Library/Android/sdk/ndk-bundle/toolchains/llvm/prebuilt/darwin-x86_64/sysroot/usr/include/c++/v1/string"

std::shared_ptr<AccountData> AccountData::getInstance() {
    static std::shared_ptr<AccountData> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<AccountData>(new AccountData());
    }
    return instance;
}

std::shared_ptr<account_djinni::AccountInfo> AccountData::getAccountInfo() {
    return nullptr;
}

void AccountData::setAccountInfo(std::shared_ptr<account_djinni::AccountInfo> info) {

}
