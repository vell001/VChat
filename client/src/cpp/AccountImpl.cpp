//
// Created by vellhe on 2020-02-05.
//

#include "AccountImpl.h"

std::shared_ptr<account_djinni::AccountInterface> account_djinni::AccountInterface::get_instance() {
    static std::shared_ptr<AccountInterface> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<account_djinni::AccountInterface>(new AccountImpl());
    }
    return instance;
}

void AccountImpl::init() {
    if(inited) {
        return;
    }
    // 加载之前的登录信息
    auto accountInfo = AccountData::getInstance()->getAccountInfo();
    if (accountInfo != nullptr) {
        // 检查token是否过期

    }
    inited = true;
}

void AccountImpl::add_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) {
    if (listener && std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
        listeners.push_back(listener);
    }
}

void AccountImpl::remove_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) {
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void AccountImpl::signup(const account_djinni::SignupMsg &info) {
    account_djinni::AccountResp resp(0, "", account_djinni::TokenMsg("",0), "");
    AccountServer::getInstance()->signup(info, resp);
    callbackFunc(&account_djinni::AccountListener::on_signup_callback, resp);
}

void AccountImpl::login(const account_djinni::LoginMsg &info) {

}

void AccountImpl::logout() {

}

void AccountImpl::is_alive() {

}

template<typename _FUNC, typename... Args>
void AccountImpl::callbackFunc(_FUNC func, Args... args) {
    for (std::shared_ptr<account_djinni::AccountListener> listener:listeners) {
        (listener.get()->*func)(args...);
    }
}

bool AccountImpl::has_login() {
    return false;
}

