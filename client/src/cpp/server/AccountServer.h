//
// Created by vellhe on 2020-02-06.
//

#pragma once

#include <grpc++/grpc++.h>
#include "account.grpc.pb.h"
#include "login_msg.hpp"
#include "signup_msg.hpp"
#include "token_msg.hpp"
#include "account_resp.hpp"
#include "account_info.hpp"
#include "../Platform.h"
using namespace std;

class AccountServer {
public:
    AccountServer(){
        auto channel = grpc::CreateChannel("192.168.1.3:50051", grpc::InsecureChannelCredentials());
        stub_ = account::Account::NewStub(channel);
    }

    void signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp, account_djinni::AccountInfo &accountInfo);

    void login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp, account_djinni::AccountInfo &accountInfo);

    void logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp);

    void is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp);

    static std::shared_ptr<AccountServer> getInstance();
private:
    std::unique_ptr<account::Account::Stub> stub_;
};

