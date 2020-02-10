//
// Created by vellhe on 2020-02-10.
//

#pragma once

namespace global {
    class AccountVariable {
    public:
        static int heartbeatIntervalSec; // 心跳间隔时间
    };

    // 常量
    class AccountRespCode {
    public:
        const static int OK;

        static const int ReqErr; // 请求错误

        const static int Login_AccountNotExist;
        const static int Login_PasswordErr;
        const static int Login_CreateTokenFail;

        const static int IsAlive_TokenNotExist;
        const static int IsAlive_TokenExpired;
        const static int IsAlive_TokenUpdate;
    };
}



