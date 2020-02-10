//
// Created by vellhe on 2020-02-10.
//

#include "GlobalValues.h"
namespace global{

    int AccountVariable::heartbeatIntervalSec = 3; // 心跳间隔时间

    const int AccountRespCode::OK = 0;

    const int AccountRespCode::ReqErr = -1000; // 请求错误

    const int AccountRespCode::Login_AccountNotExist = 1001;
    const int AccountRespCode::Login_PasswordErr =1002;
    const int AccountRespCode::Login_CreateTokenFail = 1003;

    const int AccountRespCode::IsAlive_TokenNotExist = 4001;
    const int AccountRespCode::IsAlive_TokenExpired = 4002;
    const int AccountRespCode::IsAlive_TokenUpdate = 4003;
}