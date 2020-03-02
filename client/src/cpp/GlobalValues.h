//
// Created by vellhe on 2020-02-10.
//

#pragma once

#include <string>
namespace global {
    class AccountVariable {
    public:
        static int heartbeatIntervalSec; // 心跳间隔时间
        const static std::string vchatSDCardBasePath; // 账号信息保存文件
        const static std::string accountInfoSavePath; // 账号信息保存文件
    };

    // 常量
    class AccountRespCode {
    public:
        const static int OK;

        static const int ReqErr; // 请求错误

        const static int Login_AccountNotExist;
        const static int Login_PasswordErr;
        const static int Login_CreateTokenFail;
        const static int Login_ParamErr;
        const static int Login_GetUserErr;
        const static int Login_CreateRefreshTokenFail;

        const static int Signup_ParamErr;
        const static int Signup_UserExist;
        const static int Signup_AddUserErr;

        const static int Logout_TokenNotExist;
        const static int Logout_TokenDeleteErr;
        const static int Logout_TokenIncorrect;

        const static int IsAlive_TokenNotExist;
        const static int IsAlive_TokenExpired;
        const static int IsAlive_TokenUpdate;
        const static int IsAlive_TokenIncorrect;

        const static int RefreshToken_RefreshTokenNotExist;
        const static int RefreshToken_RefreshTokenExpired;
        const static int RefreshToken_RefreshTokenIncorrect;
        const static int RefreshToken_GetUserErr;
        const static int RefreshToken_AccountNotExist;
        const static int RefreshToken_CreateTokenFail;
    };
}



