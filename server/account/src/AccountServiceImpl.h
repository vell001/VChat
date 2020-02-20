//
// Created by vellhe on 2020/2/4.
//

#pragma once

#include "account/protos/account.grpc.pb.h"
#include <glog/logging.h>
#include <glog/stl_logging.h>
#include <manager/DBManager.h>
#include <utils/StringUtils.h>
#include <utils/CryptUtils.h>
#include <utils/TimeUtils.h>
#include <config/GlobalConfig.h>
#include <manager/CacheManager.h>

class AccountServiceImpl final : public account::Account::Service {
public:
    ~AccountServiceImpl() override;

    grpc::Status signup(::grpc::ServerContext *context, const ::account::SignupMsg *request,
                        ::account::AccountRespWithInfo *response) override;

    grpc::Status login(::grpc::ServerContext *context, const ::account::LoginMsg *request,
                       ::account::AccountRespWithInfo *response) override;

    grpc::Status logout(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                        ::account::AccountResp *response) override;

    grpc::Status isAlive(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                         ::account::AccountResp *response) override;

private:
    bool isUsernameValid(const std::string &username);
    bool isPasswordValid(const std::string &password);
    std::string encodePassword(const std::string &password, const std::string &passwordSalt);
    std::string genToken(const std::string &baseInfo, double expirationTimeSec);
};

