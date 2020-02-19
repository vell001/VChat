//
// Created by vellhe on 2020/2/4.
//

#include "AccountServiceImpl.h"

AccountServiceImpl::~AccountServiceImpl() {

}

grpc::Status AccountServiceImpl::signup(::grpc::ServerContext *context, const ::account::SignupMsg *request,
                                        ::account::AccountRespWithInfo *response) {
    grpc::Status status(grpc::StatusCode::OK, "");

    const std::string &username = request->username();
    const std::string &password = request->password();
    LOG(INFO) << "signup username: " << username;

    // 检测用户信息正确性
    if (!isUsernameValid(username)) {
        response->set_code(global::AccountRespCode::Signup_ParamErr);
        response->set_msg("用户名无效");
        return status;
    }

    if (!isPasswordValid(password)) {
        response->set_code(global::AccountRespCode::Signup_ParamErr);
        response->set_msg("密码无效");
        return status;
    }

    // 检测用户是否已存在
    int existAccountCode;
    auto existAccount = DBManager::getInstance()->getAccountByUsername(username, existAccountCode);
    if (existAccount) {
        response->set_code(global::AccountRespCode::Signup_UserExist);
        response->set_msg("用户已存在");
        return status;
    }

    LOG(INFO) << "create passwordSalt";
    auto accountModel = std::shared_ptr<AccountModel>(new AccountModel);
    // 生成随机盐
    std::string passwordSalt = randStr(32);
//    std::string passwordSalt = CryptUtils::genRandStr(32);
    LOG(INFO) << "passwordSalt: " << passwordSalt;
    // 计算加密后的密码
    std::string encodedPassword = encodePassword(password, passwordSalt);
    LOG(INFO) << "encodedPassword: " << encodedPassword;

    accountModel->setUsername(username);
    accountModel->setPassword(encodedPassword);
    accountModel->setPasswordSalt(passwordSalt);
    accountModel->setPhoneNumber(request->phonenumber());
    accountModel->setEmail(request->email());
    accountModel->setExtra(request->extra());

    // 添加到数据库
    int addAccountCode = DBManager::getInstance()->addAccount(accountModel);
    if (addAccountCode != global::DBCode::OK) {
        LOG(ERROR) << "add account error: " << addAccountCode;
        response->set_code(global::AccountRespCode::Signup_AddUserErr);
        response->set_msg("用户添加失败");
        return status;
    }

    // 从数据库拉取完整用户信息
    int getAccountCode;
    auto dbAccountModel = DBManager::getInstance()->getAccountByUsername(username, getAccountCode);
    if (dbAccountModel == nullptr) {
        LOG(ERROR) << "get db account error: " << getAccountCode;
        response->set_code(global::AccountRespCode::Signup_AddUserErr);
        response->set_msg("用户添加失败");
        return status;
    }
    auto accountInfo = new account::AccountInfo();
    accountInfo->set_username(dbAccountModel->getUsername());
    accountInfo->set_phonenumber(dbAccountModel->getPhoneNumber());
    accountInfo->set_email(dbAccountModel->getEmail());
    accountInfo->set_extra(dbAccountModel->getExtra());

    response->set_code(global::AccountRespCode::OK);
    response->set_msg("用户注册成功");
    response->set_allocated_info(accountInfo);
    return status;
}

grpc::Status AccountServiceImpl::login(::grpc::ServerContext *context, const ::account::LoginMsg *request,
                                       ::account::AccountRespWithInfo *response) {
    grpc::Status status(grpc::StatusCode::OK, "");

    // TODO 登录名目前只支持username，后续再增加电话、邮箱登录
    const std::string &username = request->account();
    const std::string &password = request->password();

    // 检测用户信息正确性
    if (!isUsernameValid(username)) {
        response->set_code(global::AccountRespCode::Login_ParamErr);
        response->set_msg("用户名无效");
        return status;
    }

    if (!isPasswordValid(password)) {
        response->set_code(global::AccountRespCode::Login_ParamErr);
        response->set_msg("密码无效");
        return status;
    }

    // 获取用户
    int getAccountCode;
    auto dbAccountModel = DBManager::getInstance()->getAccountByUsername(username, getAccountCode);
    if (getAccountCode != global::DBCode::OK) {
        LOG(ERROR) << "get db account error: " << getAccountCode;
        response->set_code(global::AccountRespCode::Login_GetUserErr);
        response->set_msg("用户查询失败");
        return status;
    }
    if (dbAccountModel == nullptr) {
        response->set_code(global::AccountRespCode::Login_AccountNotExist);
        response->set_msg("用户不存在");
        return status;
    }

    // 根据数据库账号的盐信息生成加密密码
    std::string encodedPassword = encodePassword(password, dbAccountModel->getPasswordSalt());
    LOG(INFO) << "encodedPassword: " << encodedPassword;
    if (encodedPassword != dbAccountModel->getPassword()) {
        // 密码错误
        LOG(ERROR) << "password error: " << encodedPassword << " != " << dbAccountModel->getPassword();
        response->set_code(global::AccountRespCode::Login_PasswordErr);
        response->set_msg("密码错误");
        return status;
    }

    // 登录成功
    auto accountInfo = new account::AccountInfo();
    accountInfo->set_username(dbAccountModel->getUsername());
    accountInfo->set_phonenumber(dbAccountModel->getPhoneNumber());
    accountInfo->set_email(dbAccountModel->getEmail());
    accountInfo->set_extra(dbAccountModel->getExtra());

    response->set_code(global::AccountRespCode::OK);
    response->set_msg("登录成功");
    response->set_allocated_info(accountInfo);
    return status;
}

grpc::Status AccountServiceImpl::logout(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                                        ::account::AccountResp *response) {
    return Service::logout(context, request, response);
}

grpc::Status AccountServiceImpl::isAlive(::grpc::ServerContext *context, const ::account::TokenMsg *request,
                                         ::account::AccountResp *response) {
    return Service::isAlive(context, request, response);
}

bool AccountServiceImpl::isUsernameValid(const std::string &username) {
    if (username.empty() || username.size() > 64) {
        return false;
    }
    std::string pattern = "^\\w+$"; // 只能有字母数字下划线
    return regMatch(pattern, username);
}

bool AccountServiceImpl::isPasswordValid(const std::string &password) {
    if (password.empty()) {
        return false;
    }
    std::string pattern = "^[a-z0-9A-Z]{6,18}$"; // 6-18位, 由任意数字或字母组成
    return regMatch(pattern, password);
}

std::string AccountServiceImpl::encodePassword(const std::string &password, const std::string &passwordSalt) {
    return CryptUtils::hashEncode(password + passwordSalt);
}
