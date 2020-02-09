//
// Created by vellhe on 2020-02-06.
//

#include "AccountServer.h"

std::shared_ptr<AccountServer> AccountServer::getInstance() {
    static std::shared_ptr<AccountServer> instance;
    if(instance == nullptr) {
        instance = std::shared_ptr<AccountServer>(new AccountServer());
    }
    return instance;
}

void
AccountServer::signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp) {
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
        account_djinni::TokenMsg tokenMsg(reply.token().token(), reply.token().expiration_time_sec());
        resp.token = tokenMsg;
        resp.code = reply.code();
    } else {
        resp.code = -1;
    }
}

void
AccountServer::login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp) {

}

void
AccountServer::logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}

void
AccountServer::is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}
