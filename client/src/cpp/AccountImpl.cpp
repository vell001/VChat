//
// Created by vellhe on 2020-02-05.
//

#include "AccountImpl.h"

std::shared_ptr<AccountInterface> AccountInterface::get_instance() {
    static std::shared_ptr<AccountInterface> instance;
    if (instance == nullptr){
        instance = std::make_shared<AccountImpl>();
    }
    return instance;
}

void AccountImpl::add_listener(const std::shared_ptr<AccountListener> &listener) {
    if (listener && std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
        listeners.push_back(listener);
    }
}

void AccountImpl::remove_listener(const std::shared_ptr<AccountListener> &listener) {
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void AccountImpl::signup(const SignupMsg &info) {
    AccountResp resp(0, "succ", "test", "");
    callbackFunc(&AccountListener::on_signup_callback, resp);
}

void AccountImpl::login(const LoginMsg &info) {

}

void AccountImpl::logout(const TokenMsg &token) {

}

void AccountImpl::is_alive(const TokenMsg &token) {

}

template<typename _FUNC, typename... Args>
void AccountImpl::callbackFunc(_FUNC func, Args... args) {
    for (std::shared_ptr<AccountListener> listener:listeners) {
        (listener.get()->*func)(args...);
    }
}
