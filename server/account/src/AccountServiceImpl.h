//
// Created by vellhe on 2020/2/4.
//

#pragma once

#include "account/protos/account.grpc.pb.h"
#include <glog/logging.h>
#include <glog/stl_logging.h>
#include <data_manager/DBManager.h>
#include <utils/StringUtils.h>
#include <utils/CryptUtils.h>
#include <utils/TimeUtils.h>
#include <config/GlobalConfig.h>
#include <data_manager/CacheManager.h>

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

    grpc::Status refreshToken(::grpc::ServerContext *context, const ::account::RefreshTokenMsg *request,
                              ::account::AccountResp *response) override;

private:
    /**
     * 用户名是否有效
     * @param username
     * @return
     */
    bool isUsernameValid(const std::string &username);

    /**
     * 密码是否有效
     * @param password
     * @return
     */
    bool isPasswordValid(const std::string &password);

    /**
     * 加盐哈希编码用户密码
     *
     * @param password 原始密码
     * @param passwordSalt 随机盐
     * @return 编码后的密码
     */
    std::string encodePassword(const std::string &password, const std::string &passwordSalt);

    /**
     * 生成token
     * @param baseInfo 基础参考信息
     * @param expirationTimeSec 过期时间
     * @return token
     */
    std::string genToken(const std::string &baseInfo, double expirationTimeSec);
};

