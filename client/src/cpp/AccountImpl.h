//
// Created by vellhe on 2020-02-05.
//
#pragma once

#include <vector>
#include "Platform.h"
#include "account_interface.hpp"
#include "account_listener.hpp"
#include "account_resp.hpp"
#include "server/AccountServer.h"
#include "datacenter/AccountData.h"
#include "utils/TimeUtils.h"
#include "Handler.h"
#include "GlobalValues.h"

using namespace std;

class AccountImpl : public account_djinni::AccountInterface {
private:
    vector<shared_ptr<account_djinni::AccountListener> > listeners;

    // 调用listener的更新函数
    template<typename _FUNC, typename... Args>
    void callbackFunc(_FUNC func, Args... args);
public:
    static std::shared_ptr<AccountImpl> getInstance();
    void init() override;

    void add_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) override;

    void remove_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) override;

    void signup(const account_djinni::SignupMsg &info, int32_t seqId) override;

    void login(const account_djinni::LoginMsg &info, int32_t seqId) override;

    void logout(int32_t seqId) override;

    account_djinni::AccountInfo getAccountInfo() override;

    void is_alive() override;

    bool has_login() override;

    void startHeartbeat();

    void stopHeartbeat();
private:
    bool inited = false;
    bool hasLogin = false;
    bool heartbeating = false;

    std::shared_ptr<Handler> serverHandler = std::shared_ptr<Handler>(new Handler); // 服务端异步请求处理
    std::shared_ptr<Handler> heartbeatHandler = std::shared_ptr<Handler>(new Handler); // 心跳处理

    bool isAccountInfoValid(std::shared_ptr<account_djinni::AccountInfo> accountInfo);
    void resetLocalAccountInfo(); // 重置本地的账号信息
    void heartbeat();
    void refreshToken(); // 重新向服务器获取token
};


