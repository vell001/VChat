//
// Created by vellhe on 2020-02-06.
//

#include "AccountService.h"

std::shared_ptr<AccountService> AccountService::getInstance() {
    if(_instance == nullptr) {
        _instance = std::shared_ptr<AccountService>(new AccountService());
    }
    return _instance;
}

std::shared_ptr<AccountService> AccountService::_instance = nullptr;

void
AccountService::signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp) {
    account::SignupMsg signupMsg;
    signupMsg.set_username(info.username);
    signupMsg.set_password(info.password);

    TLog("signup: %s", info.username.c_str());
    account::AccountResp reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->signup(&context, signupMsg, &reply);

    if (status.ok()) {
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        resp.token = reply.token();
        resp.code = reply.code();
    } else {
        resp.code = -1;
    }
}

void
AccountService::login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp) {

}

void
AccountService::logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}

void
AccountService::is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}
