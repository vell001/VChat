//
// Created by vellhe on 2020-02-05.
//

#include "AccountImpl.h"

std::shared_ptr<account_djinni::AccountInterface> account_djinni::AccountInterface::get_instance() {
    return AccountImpl::getInstance();
}

std::shared_ptr<AccountImpl> AccountImpl::getInstance() {
    static std::shared_ptr<AccountImpl> instance;
    if (instance == nullptr) {
        instance = std::shared_ptr<AccountImpl>(new AccountImpl());
    }
    return instance;
}

void AccountImpl::init() {
    if (inited) {
        return;
    }
    // 加载之前的登录信息
    auto accountInfo = AccountData::getInstance()->getAccountInfo();

    if (!isAccountInfoValid(accountInfo)) {
        // 需要重新登录
        hasLogin = false;
    } else {
        hasLogin = true;
        // 启动心跳
        startHeartbeat();
    }
    inited = true;
}

void AccountImpl::add_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) {
    if (listener && std::find(listeners.begin(), listeners.end(), listener) == listeners.end()) {
        listeners.push_back(listener);
    }
}

void
AccountImpl::remove_listener(const std::shared_ptr<account_djinni::AccountListener> &listener) {
    auto it = std::find(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it);
    }
}

void AccountImpl::signup(const account_djinni::SignupMsg &info, int32_t seqId) {
    serverHandler->post([info, seqId]() {
        account_djinni::AccountResp resp(0, "", "", account_djinni::TokenMsg("", 0), "");
        account_djinni::AccountInfo accountInfo("", "", "", "", account_djinni::TokenMsg("", 0));
        AccountServer::getInstance()->signup(info, resp, accountInfo);

        getInstance()->callbackFunc(&account_djinni::AccountListener::on_signup_callback, resp,
                                    seqId, accountInfo);
    });
}

void AccountImpl::login(const account_djinni::LoginMsg &info, int32_t seqId) {
    serverHandler->post([this, info, seqId]() {
        account_djinni::AccountResp resp(0, "", "", account_djinni::TokenMsg("", 0), "");
        auto accountInfo = std::shared_ptr<account_djinni::AccountInfo>(
                new account_djinni::AccountInfo("", "", "", "", account_djinni::TokenMsg("", 0)));
        AccountServer::getInstance()->login(info, resp, *accountInfo);

        if (resp.code == global::AccountRespCode::OK) {
            // 登录成功，保存用户信息
            AccountData::getInstance()->setAccountInfo(accountInfo);

            // 启动心跳
            this->startHeartbeat();
        }

        getInstance()->callbackFunc(&account_djinni::AccountListener::on_login_callback, resp,
                                    seqId, *accountInfo);
    });
}

void AccountImpl::logout(int32_t seqId) {
    serverHandler->post([this, seqId]() {
        account_djinni::AccountResp resp(0, "", "", account_djinni::TokenMsg("", 0), "");
        auto accountInfo = AccountData::getInstance()->getAccountInfo();
        if (accountInfo == nullptr || accountInfo->token.token.empty()) {
            resp.code = global::AccountRespCode::Logout_TokenNotExist;
            resp.msg = "本地没有账号信息";
        } else {
            AccountServer::getInstance()->logout(accountInfo->token, resp);
        }

        if (resp.code == global::AccountRespCode::OK) {
            // 登出成功，重置用户信息
            this->resetLocalAccountInfo();

            // 停止心跳
            this->stopHeartbeat();
        }

        this->callbackFunc(&account_djinni::AccountListener::on_login_callback, resp,
                           seqId, *accountInfo);
    });
}

void AccountImpl::is_alive() {
    serverHandler->post([this]() {
        account_djinni::AccountResp resp(0, "", "", account_djinni::TokenMsg("", 0), "");
        auto accountInfo = AccountData::getInstance()->getAccountInfo();
        if (accountInfo == nullptr || accountInfo->token.token.empty()) {
            resp.code = global::AccountRespCode::IsAlive_TokenNotExist;
            resp.msg = "本地没有账号信息";
        } else {
            AccountServer::getInstance()->is_alive(accountInfo->token, resp);
        }

        LOGI(FILE_TAG, "heartbeat resp: %d,%s%s", resp.code, resp.msg.c_str(),
             resp.extra.c_str());

        if (resp.code == global::AccountRespCode::ReqErr) {
            // 请求失败, TODO 暂时不管，后续区分失败原因
        } else if (resp.code == global::AccountRespCode::IsAlive_TokenNotExist ||
                   resp.code == global::AccountRespCode::IsAlive_TokenExpired) {
            // 服务端登录信息无效，重置本地信息，重新登录
            this->resetLocalAccountInfo();

            // 停止心跳
            stopHeartbeat();

            callbackFunc(&account_djinni::AccountListener::on_is_alive_callback, resp);
        } else if (resp.code == global::AccountRespCode::IsAlive_TokenUpdate) {
            // 更新Token
            accountInfo->token = resp.token;
            AccountData::getInstance()->setAccountInfo(accountInfo);
        }
    });
}

template<typename _FUNC, typename... Args>
void AccountImpl::callbackFunc(_FUNC func, Args... args) {
    for (auto listener:listeners) {
        (listener.get()->*func)(args...);
    }
}

bool AccountImpl::has_login() {
    return false;
}

bool AccountImpl::isAccountInfoValid(std::shared_ptr<account_djinni::AccountInfo> accountInfo) {
    // 检测信息是否完整
    if (accountInfo == nullptr || accountInfo->username.empty() ||
        accountInfo->token.token.empty()) {
        return false;
    }
    // 本地检查token是否过期
    double nowS = nowSec();
    if (accountInfo->token.expiration_time_sec <= nowS) {
        // 已过期
        return false;
    }
    return true;
}

void AccountImpl::heartbeat() {
    // 心跳检测账号信息
    while (heartbeating) {
        LOGI(FILE_TAG, "===== heartbeat =====");
        is_alive();

        double sleepTimeSec = global::AccountVariable::heartbeatIntervalSec;
        if (sleepTimeSec > 0)
        {
            std::chrono::milliseconds sleepTime((long) (sleepTimeSec * 1000));
            std::this_thread::sleep_for(sleepTime);
            TLog("sleep time %f ms ", sleepTimeSec*1000);
        }
    }
//    if (heartbeating) {
//        // 启动下一次心跳
//        double nextTime = (nowSec() + global::AccountVariable::heartbeatIntervalSec) * 1000;
//        heartbeatHandler->postAtTime((Message::Function) std::bind(&AccountImpl::heartbeat, this),
//                                     (long) nextTime);
//        LOGI(FILE_TAG, "===== heartbeat nextTime: %f %f %ld =====", nowSec(), nextTime,
//             (long) nextTime);
//    } else {
//        LOGI(FILE_TAG, "===== heartbeat stopped =====");
//    }
}

void AccountImpl::startHeartbeat() {
    LOGI(FILE_TAG, "startHeartbeat");
    heartbeating = true;
    heartbeatHandler->post((Message::Function) std::bind(&AccountImpl::heartbeat, this));
}

void AccountImpl::stopHeartbeat() {
    LOGI(FILE_TAG, "stopHeartbeat");
    heartbeating = false;
}


void AccountImpl::resetLocalAccountInfo() {
    hasLogin = false;
    auto accountInfo = AccountData::getInstance()->getAccountInfo();
    if (accountInfo == nullptr) {
        accountInfo->token.token = "";
        accountInfo->token.expiration_time_sec = 0;
        AccountData::getInstance()->setAccountInfo(accountInfo);
    }
}

account_djinni::AccountInfo AccountImpl::getAccountInfo() {
    auto accountInfo = AccountData::getInstance()->getAccountInfo();
    if (accountInfo != nullptr) {
        return *accountInfo;
    }
    return account_djinni::AccountInfo("", "", "", "", account_djinni::TokenMsg("", 0));
}



