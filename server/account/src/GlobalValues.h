//
// Created by vellhe on 2020-02-10.
//

#pragma once

namespace global {
    class DBCode {
    public:
        const static int OK;
        const static int ERR;

        const static int QUERY_ERR;

        const static int CONN_INIT_ERR;
        const static int CONN_ERR;
        const static int CONN_CHARSET_ERR;
    };

    class CacheCode {
    public:
        const static int OK;
        const static int ERR;

        const static int CONN_ERR;

        const static int GET_ERR;
        const static int GET_NIL; // 空

        const static int SET_ERR;
        const static int DEL_ERR;
    };

    class AccountRespCode {
    public:
        const static int OK;

        static const int ReqErr; // 请求错误

        const static int Login_AccountNotExist;
        const static int Login_PasswordErr;
        const static int Login_CreateTokenFail;
        const static int Login_ParamErr;
        const static int Login_GetUserErr;

        const static int Signup_ParamErr;
        const static int Signup_UserExist;
        const static int Signup_AddUserErr;

        const static int Logout_TokenNotExist;
        const static int Logout_TokenDeleteErr;

        const static int IsAlive_TokenNotExist;
        const static int IsAlive_TokenExpired;
        const static int IsAlive_TokenUpdate;
    };
}



