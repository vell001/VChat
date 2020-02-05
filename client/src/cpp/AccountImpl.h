//
// Created by vellhe on 2020-02-05.
//
#pragma once

#include <vector>
#include "account_interface.hpp"
#include "account_resp.hpp"
#include "account_listener.hpp"

using namespace account;
using namespace std;

class AccountImpl : public AccountInterface {
private:
    vector<shared_ptr<AccountListener> > listeners;

    // 调用listener的更新函数
    template<typename _FUNC, typename... Args>
    void callbackFunc(_FUNC func, Args... args);
public:
    void add_listener(const std::shared_ptr<AccountListener> &listener) override;

    void remove_listener(const std::shared_ptr<AccountListener> &listener) override;

    void signup(const SignupMsg &info) override;

    void login(const LoginMsg &info) override;

    void logout(const TokenMsg &token) override;

    void is_alive(const TokenMsg &token) override;
};


