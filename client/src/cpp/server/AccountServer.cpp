//
// Created by vellhe on 2020-02-06.
//

#include <GlobalValues.h>
#include "AccountServer.h"

std::shared_ptr<AccountServer> AccountServer::getInstance() {
    static std::shared_ptr<AccountServer> instance;
    if(instance == nullptr) {
        instance = std::shared_ptr<AccountServer>(new AccountServer());
    }
    return instance;
}

void
AccountServer::signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp, account_djinni::AccountInfo &accountInfo) {
    account::SignupMsg signupMsg;
    signupMsg.set_username(info.username);
    signupMsg.set_password(info.password);

    TLog("signup: %s", info.username.c_str());
    account::AccountRespWithInfo reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->signup(&context, signupMsg, &reply);

    if (status.ok()) {
        account::AccountInfo replyAccountInfo = reply.info();
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        account_djinni::TokenMsg tokenMsg(replyAccountInfo.token().token(), replyAccountInfo.token().expiration_time_sec());
        resp.token = tokenMsg;
        resp.code = reply.code();

        accountInfo.username = replyAccountInfo.username();
        accountInfo.phoneNumber = replyAccountInfo.phonenumber();
        accountInfo.email = replyAccountInfo.email();
        accountInfo.extra = replyAccountInfo.extra();
    } else {
        resp.code = global::AccountRespCode::ReqErr;
        resp.msg = status.error_message();
        resp.extra = status.error_details();
    }
}

void
AccountServer::login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp, account_djinni::AccountInfo &accountInfo) {
    account::LoginMsg loginMsg;
    loginMsg.set_account(info.account);
    loginMsg.set_password(info.password);

    TLog("login: %s", info.account.c_str());
    account::AccountRespWithInfo reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->login(&context, loginMsg, &reply);

    if (status.ok()) {
        account::AccountInfo replyAccountInfo = reply.info();
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        account_djinni::TokenMsg tokenMsg(replyAccountInfo.token().token(), replyAccountInfo.token().expiration_time_sec());
        resp.token = tokenMsg;
        resp.code = reply.code();

        accountInfo.username = replyAccountInfo.username();
        accountInfo.phoneNumber = replyAccountInfo.phonenumber();
        accountInfo.email = replyAccountInfo.email();
        accountInfo.extra = replyAccountInfo.extra();
    } else {
        resp.code = global::AccountRespCode::ReqErr;
        resp.msg = status.error_message();
        resp.extra = status.error_details();
    }
}

void
AccountServer::logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}

void
AccountServer::is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {

}
