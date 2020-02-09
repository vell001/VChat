//
// Created by vellhe on 2020-02-05.
//
#pragma once

#include <vector>
#include "account_interface.hpp"
#include "account_listener.hpp"
#include "account_resp.hpp"
#include "server/AccountServer.h"
#include "datacenter/AccountData.h"
#include "Platform.h"

using namespace std;

class AccountImpl : public account_djinni::AccountInterface {
private:
    vector<shared_ptr<account_djinni::AccountListener> > listeners;

    // 调用listener的更新函数
    template<typename _FUNC, typename... Args>
    void callbackFunc(_FUNC func, Args... args);
public:
    void init() override;

    void add_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) override;

    void remove_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) override;

    void signup(const account_djinni::SignupMsg &info) override;

    void login(const account_djinni::LoginMsg &info) override;

    void logout() override;

    void is_alive() override;

    bool has_login() override;

private:
    bool inited = false;
    bool hasLogin = false;
    std::shared_ptr<account_djinni::AccountInfo> mAccountInfo;
};


