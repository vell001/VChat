// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include "token_msg.hpp"
#include <string>
#include <utility>

namespace account_djinni {

/** 所有账号相关信息 */
struct AccountInfo final {
    std::string username;
    /** 用户名，唯一存在 */
    std::string phoneNumber;
    std::string email;
    std::string extra;
    TokenMsg token;

    AccountInfo(std::string username_,
                std::string phoneNumber_,
                std::string email_,
                std::string extra_,
                TokenMsg token_)
    : username(std::move(username_))
    , phoneNumber(std::move(phoneNumber_))
    , email(std::move(email_))
    , extra(std::move(extra_))
    , token(std::move(token_))
    {}
};

}  // namespace account_djinni