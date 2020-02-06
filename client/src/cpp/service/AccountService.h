//
// Created by vellhe on 2020-02-06.
//

#pragma once

#include <grpc++/grpc++.h>
#include "account.grpc.pb.h"

using namespace std;

class AccountService {
public:
    AccountService(){
        auto channel = grpc::CreateChannel("192.168.1.5:50051", grpc::InsecureChannelCredentials());
        stub_ = account::Account::NewStub(channel);
    }

    string signup(const string &username,const string &password);
    static std::shared_ptr<AccountService> getInstance();
private:
    std::unique_ptr<account::Account::Stub> stub_;
    static std::shared_ptr<AccountService> _instance;
};

