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

    AccountModel(int id, const std::string &username, const std::string &phoneNumber, const std::string &email,
                 const std::string &extra);

private:
    int id;
    /** 用户名，唯一存在 */
    std::string username;
    std::string phoneNumber;
    std::string email;
    std::string extra;
};



