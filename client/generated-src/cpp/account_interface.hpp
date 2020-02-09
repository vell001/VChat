// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include <memory>

namespace account_djinni {

class AccountListener;
struct LoginMsg;
struct SignupMsg;

class AccountInterface {
public:
    virtual ~AccountInterface() {}

    /** 单例 */
    static std::shared_ptr<AccountInterface> get_instance();

    /** 初始化 */
    virtual void init() = 0;

    virtual void add_listener(const std::shared_ptr<AccountListener> & listener) = 0;

    virtual void remove_listener(const std::shared_ptr<AccountListener> & listener) = 0;

    virtual void signup(const SignupMsg & info) = 0;

    virtual void login(const LoginMsg & info) = 0;

    virtual void logout() = 0;

    /** 手动发起服务器是否在线检查，会异步定时检查 */
    virtual void is_alive() = 0;

    /** 是否已经登录 */
    virtual bool has_login() = 0;
};

}  // namespace account_djinni
