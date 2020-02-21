//
// Created by vellhe on 2020-02-10.
//

#include "GlobalValues.h"

namespace global {

    int AccountVariable::heartbeatIntervalSec = 3; // 心跳间隔时间
    const std::string AccountVariable::vchatSDCardBasePath = "/sdcard/vchat"; // sd卡保存基础目录
    const std::string AccountVariable::accountInfoSavePath =
            AccountVariable::vchatSDCardBasePath + "/account_info.json"; // 账户信息文件

    const int AccountRespCode::OK = 0;

    const int AccountRespCode::ReqErr = -1000; // 请求错误

    const int AccountRespCode::Login_AccountNotExist = 1001;
    const int AccountRespCode::Login_PasswordErr = 1002;
    const int AccountRespCode::Login_CreateTokenFail = 1003;
    const int AccountRespCode::Login_ParamErr = 1004;
    const int AccountRespCode::Login_GetUserErr = 1005;

    const int AccountRespCode::Signup_ParamErr = 2001;
    const int AccountRespCode::Signup_UserExist = 2001;
    const int AccountRespCode::Signup_AddUserErr = 2002;

    const int AccountRespCode::Logout_TokenNotExist = 3001;
    const int AccountRespCode::Logout_TokenDeleteErr = 3002;
    const int AccountRespCode::Logout_TokenIncorrect = 3003;

    const int AccountRespCode::IsAlive_TokenNotExist = 4001;
    const int AccountRespCode::IsAlive_TokenExpired = 4002;
    const int AccountRespCode::IsAlive_TokenUpdate = 4003;
    const int AccountRespCode::IsAlive_TokenIncorrect = 4004;
}