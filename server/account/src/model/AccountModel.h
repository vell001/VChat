//
// Created by vellhe on 2020/2/11.
//

#pragma once

#include <string>

class AccountModel {
public:
    int getId() const;

    void setId(int id);

    const std::string &getUsername() const;

    void setUsername(const std::string &username);

    const std::string &getPhoneNumber() const;

    void setPhoneNumber(const std::string &phoneNumber);

    const std::string &getEmail() const;

    void setEmail(const std::string &email);

    const std::string &getExtra() const;

    void setExtra(const std::string &extra);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    const std::string &getPasswordSalt() const;

    void setPasswordSalt(const std::string &passwordSalt);

    AccountModel(int id, const std::string &username, const std::string &password, const std::string &passwordSalt,
                 const std::string &phoneNumber, const std::string &email, const std::string &extra);

    AccountModel();

private:
    int id; // 数据库唯一id
    std::string username; // 用户名
    std::string password; // 加密后的密码
    std::string password_salt; // 密码随机盐
    std::string phoneNumber; // 电话，TODO 加密存储
    std::string email; // 邮箱，TODO 加密存储
    std::string extra; // 附加信息
};



