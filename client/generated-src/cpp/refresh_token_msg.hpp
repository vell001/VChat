// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include <cstdint>
#include <string>
#include <utility>

namespace account_djinni {

/** refresh_token信息 */
struct RefreshTokenMsg final {
    std::string refresh_token;
    int32_t expiration_time_sec;
    std::string username;

    RefreshTokenMsg(std::string refresh_token_,
                    int32_t expiration_time_sec_,
                    std::string username_)
    : refresh_token(std::move(refresh_token_))
    , expiration_time_sec(std::move(expiration_time_sec_))
    , username(std::move(username_))
    {}
};

}  // namespace account_djinni
