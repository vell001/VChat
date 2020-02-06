//
// Created by vellhe on 2020-02-06.
//

#include "AccountService.h"

string AccountService::signup(const string &username, const string &password) {
    account::SignupMsg signupMsg;
    signupMsg.set_username(username);
    signupMsg.set_password(password);

    account::AccountResp resp;
    grpc::ClientContext context;
    grpc::Status status = stub_->signup(&context, signupMsg, &resp);

    if (status.ok()) {
        return resp.msg();
    } else {
        return "RPC failed";
    }
}

std::shared_ptr<AccountService> AccountService::getInstance() {
    if(_instance == nullptr) {
        _instance = std::shared_ptr<AccountService>(new AccountService());
    }
    return _instance;
}

std::shared_ptr<AccountService> AccountService::_instance = nullptr;