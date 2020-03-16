//
// Created by vellhe on 2020-02-10.
//

#pragma once

namespace global {
    class DBCode {
    public:
        const static int OK; // 正常
        const static int ERR; // 错误

        const static int QUERY_ERR; // 查询错误
        const static int QUERY_STMT_ERR; // Prepared Statement 错误
        const static int QUERY_STMT_PARAM_ERR; // Prepared Statement 参数错误
        const static int QUERY_STMT_INIT_ERR; // Prepared Statement 初始化时错误
        const static int QUERY_STMT_PREPARED_ERR; // Prepared Statement 准备时错误
        const static int QUERY_STMT_RET_ERR; // Prepared Statement 结果错误

        const static int CONN_INIT_ERR; // 连接时初始化错误
        const static int CONN_ERR; // 连接错误
        const static int CONN_CHARSET_ERR; // 字符编码错误
    };

    class CacheCode {
    public:
        const static int OK; // 正常
        const static int ERR; // 错误

        const static int CONN_ERR; // 连接时错误

        const static int GET_ERR; // 获取时错误
        const static int GET_NIL; // 错误时为空

        const static int SET_ERR; // 设置时错误
        const static int DEL_ERR; // 删除时错误
    };

    class AccountRespCode {
    public:
        const static int OK;

        static const int ReqErr; // 请求错误

        const static int Login_AccountNotExist; // 登录时用户不存在
        const static int Login_PasswordErr; // 登录时密码错误
        const static int Login_CreateTokenFail; // 登录时创建token失败
        const static int Login_ParamErr; // 登录时参数错误
        const static int Login_GetUserErr; // 登录时获取用户出错
        const static int Login_CreateRefreshTokenFail; // 登录时创建refresh token失败

        const static int Signup_ParamErr; // 注册时参数错误
        const static int Signup_UserExist; // 注册时用户已存在
        const static int Signup_AddUserErr; // 注册时添加用户出错

        const static int Logout_TokenNotExist; // 登出时token不存在
        const static int Logout_TokenDeleteErr; // 登出时token删除错误
        const static int Logout_TokenIncorrect; // 登出时token不一致，无效

        const static int IsAlive_TokenNotExist; // 心跳检测时token不存在
        const static int IsAlive_TokenExpired; // 心跳检测时token已过期
        const static int IsAlive_TokenUpdate; // 心跳检测时token需要更新
        const static int IsAlive_TokenIncorrect; // 心跳检测时token不一致，失效

        const static int RefreshToken_RefreshTokenNotExist; // 刷新token时refresh token不存在
        const static int RefreshToken_RefreshTokenExpired; // 刷新token时refresh token已过期
        const static int RefreshToken_RefreshTokenIncorrect; // 刷新token时refresh token不正确
        const static int RefreshToken_GetUserErr; // 刷新token时获取用户信息失败
        const static int RefreshToken_AccountNotExist; // 刷新token时账号不存在
        const static int RefreshToken_CreateTokenFail; // 刷新token时创建token失败
    };
}



