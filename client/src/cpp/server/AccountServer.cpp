//
// Created by vellhe on 2020-02-06.
//


#include "AccountServer.h"

std::shared_ptr<AccountServer> AccountServer::getInstance() {
    static std::shared_ptr<AccountServer> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<AccountServer>(new AccountServer());
    }
    return instance;
}

void
AccountServer::signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp,
                      account_djinni::AccountInfo &accountInfo) {
    account::SignupMsg signupMsg;
    signupMsg.set_username(info.username);
    signupMsg.set_password(info.password);
    signupMsg.set_phonenumber(info.phoneNumber);
    signupMsg.set_email(info.email);
    signupMsg.set_extra(info.extra);

    TLog("signup: %s", info.username.c_str());
    account::AccountRespWithInfo reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->signup(&context, signupMsg, &reply);

    if (status.ok()) {
        account::AccountInfo replyAccountInfo = reply.info();
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        account_djinni::TokenMsg tokenMsg(replyAccountInfo.token().token(),
                                          replyAccountInfo.token().expiration_time_sec(),
                                          replyAccountInfo.token().username());
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
AccountServer::login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp,
                     account_djinni::AccountInfo &accountInfo) {
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
        account_djinni::TokenMsg tokenMsg(replyAccountInfo.token().token(),
                                          replyAccountInfo.token().expiration_time_sec(),
                                          replyAccountInfo.token().username());
        resp.token = tokenMsg;
        resp.code = reply.code();
        resp.username = replyAccountInfo.username();

        accountInfo.username = replyAccountInfo.username();
        accountInfo.phoneNumber = replyAccountInfo.phonenumber();
        accountInfo.email = replyAccountInfo.email();
        accountInfo.extra = replyAccountInfo.extra();
        accountInfo.token = tokenMsg;
    } else {
        resp.code = global::AccountRespCode::ReqErr;
        resp.msg = status.error_message();
        resp.extra = status.error_details();
    }
}

void
AccountServer::logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {
    account::TokenMsg tokenMsg;
    tokenMsg.set_token(token.token);
    tokenMsg.set_expiration_time_sec(token.expiration_time_sec);
    tokenMsg.set_username(token.username);

    TLog("logout: %s", token.token.c_str());
    account::AccountResp reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->logout(&context, tokenMsg, &reply);

    if (status.ok()) {
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        account_djinni::TokenMsg tokenMsgReply(reply.token().token(),
                                               reply.token().expiration_time_sec(),
                                               reply.token().username());
        resp.token = tokenMsgReply;
        resp.code = reply.code();
    } else {
        resp.code = global::AccountRespCode::ReqErr;
        resp.msg = status.error_message();
        resp.extra = status.error_details();
    }
}

void
AccountServer::is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp) {
    account::TokenMsg tokenMsg;
    tokenMsg.set_token(token.token);
    tokenMsg.set_expiration_time_sec(token.expiration_time_sec);
    tokenMsg.set_username(token.username);

    TLog("is_alive: %s %s", token.username.c_str(), token.token.c_str());
    account::AccountResp reply;
    grpc::ClientContext context;
    grpc::Status status = stub_->isAlive(&context, tokenMsg, &reply);

    if (status.ok()) {
        resp.extra = reply.extra();
        resp.msg = reply.msg();
        account_djinni::TokenMsg tokenMsgReply(reply.token().token(),
                                               reply.token().expiration_time_sec(),
                                               reply.token().username());
        resp.token = tokenMsgReply;
        resp.code = reply.code();
    } else {
        resp.code = global::AccountRespCode::ReqErr;
        resp.msg = status.error_message();
        resp.extra = status.error_details();
    }
}
