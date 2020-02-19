//
// Created by vellhe on 2020/2/11.
//

#include "AccountModel.h"

int AccountModel::getId() const {
    return id;
}

void AccountModel::setId(int id) {
    AccountModel::id = id;
}

const std::string &AccountModel::getUsername() const {
    return username;
}

void AccountModel::setUsername(const std::string &username) {
    AccountModel::username = username;
}

const std::string &AccountModel::getPhoneNumber() const {
    return phoneNumber;
}

void AccountModel::setPhoneNumber(const std::string &phoneNumber) {
    AccountModel::phoneNumber = phoneNumber;
}

const std::string &AccountModel::getEmail() const {
    return email;
}

void AccountModel::setEmail(const std::string &email) {
    AccountModel::email = email;
}

const std::string &AccountModel::getExtra() const {
    return extra;
}

void AccountModel::setExtra(const std::string &extra) {
    AccountModel::extra = extra;
}

const std::string &AccountModel::getPassword() const {
    return password;
}

void AccountModel::setPassword(const std::string &password) {
    AccountModel::password = password;
}

const std::string &AccountModel::getPasswordSalt() const {
    return password_salt;
}

void AccountModel::setPasswordSalt(const std::string &passwordSalt) {
    password_salt = passwordSalt;
}

AccountModel::AccountModel(int id, const std::string &username, const std::string &password,
                           const std::string &passwordSalt, const std::string &phoneNumber, const std::string &email,
                           const std::string &extra) : id(id), username(username), password(password),
                                                       password_salt(passwordSalt), phoneNumber(phoneNumber),
                                                       email(email), extra(extra) {}

AccountModel::AccountModel() {}
