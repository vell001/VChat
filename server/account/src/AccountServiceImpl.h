//
// Created by vellhe on 2020/2/4.
//

#pragma once

#include "account/protos/account.grpc.pb.h"

class AccountServiceImpl final : public account::Account::Service {
public:
    ~AccountServiceImpl() override;

    grpc::Status signup(::grpc::ServerContext *context, const ::account::SignupMsg *request,
                        ::account::AccountResp *response) override;

    grpc::Status login(::grpc::ServerContext *context, const ::account::LoginMsg *request,
                       ::account::AccountResp *response) override;

    grpc::Status logout(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                        ::account::AccountResp *response) override;

    grpc::Status isAlive(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                         ::account::AccountResp *response) override;
};

