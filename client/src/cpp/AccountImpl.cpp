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
    auto ret = AccountService::getInstance()->signup("user","pwd");
    account_djinni::AccountResp resp(0, "succ", "test", ret);
    callbackFunc(&account_djinni::AccountListener::on_signup_callback, resp);
}

void AccountImpl::login(const account_djinni::LoginMsg &info) {

}

void AccountImpl::logout(const account_djinni::TokenMsg &token) {

}

void AccountImpl::is_alive(const account_djinni::TokenMsg &token) {

}

template<typename _FUNC, typename... Args>
void AccountImpl::callbackFunc(_FUNC func, Args... args) {
    for (std::shared_ptr<account_djinni::AccountListener> listener:listeners) {
        (listener.get()->*func)(args...);
    }
}
