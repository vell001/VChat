package com.vell.vchat;

public class GlobalValues {
    public static String KEY_account = "account";
    public static String KEY_username = "username";
    public static String KEY_account_info = "account_info";
    public static String KEY_token_info = "token_info";

    public static int CODE_AccountResp_OK = 0;
    public static int CODE_AccountResp_ReqErr = -1000;

    public static int CODE_AccountResp_Login_AccountNotExist = 1001;
    public static int CODE_AccountResp_Login_PasswordErr =1002;
    public static int CODE_AccountResp_Login_CreateTokenFail = 1003;
    public static int CODE_AccountResp_Login_ParamErr = 1004;
    public static int CODE_AccountResp_Login_GetUserErr = 1005;

    public static int CODE_AccountResp_Signup_ParamErr = 2001;
    public static int CODE_AccountResp_Signup_UserExist = 2001;
    public static int CODE_AccountResp_Signup_AddUserErr = 2002;

    public static int CODE_AccountResp_Logout_TokenNotExist = 3001;
    public static int CODE_AccountResp_Logout_TokenDeleteErr = 3002;
    public static int CODE_AccountResp_Logout_TokenIncorrect = 3003;

    public static int CODE_AccountResp_IsAlive_TokenNotExist = 4001;
    public static int CODE_AccountResp_IsAlive_TokenExpired = 4002;
    public static int CODE_AccountResp_IsAlive_TokenUpdate = 4003;
    public static int CODE_AccountResp_IsAlive_TokenIncorrect = 4004;
}
