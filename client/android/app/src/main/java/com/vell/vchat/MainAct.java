package com.vell.vchat;

import android.Manifest;
import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.vell.chat.account.AccountInterface;
import com.vell.chat.account.AccountListener;
import com.vell.chat.account.AccountResp;
import com.vell.chat.account.SignupMsg;
import com.vell.vchat.utils.PermissionsUtils;

public class MainAct extends Activity {
    static {
        System.loadLibrary("vchat");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main_act);
        // 请求权限
        PermissionsUtils.getInstance().checkPermissions(this, new String[]{
                        Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.READ_EXTERNAL_STORAGE},
                new PermissionsUtils.IPermissionsResult() {
                    @Override
                    public void passPermissions() {

                    }

                    @Override
                    public void forbidPermissions() {
                        finish(); // 退出应用
                    }
                });

        AccountInterface.getInstance().addListener(new AccountListener() {
            @Override
            public void onSignupCallback(AccountResp callback) {
                Toast.makeText(MainAct.this, "onSignupCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onLoginCallback(AccountResp callback) {

            }

            @Override
            public void onLogoutCallback(AccountResp callback) {

            }

            @Override
            public void onIsAliveCallback(AccountResp callback) {

            }
        });

        findViewById(R.id.btn_login).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                AccountInterface.getInstance().signup(new SignupMsg("user", "pwd", "123456", "v@qq.com", "extra"));
            }
        });
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        PermissionsUtils.getInstance().onRequestPermissionsResult(this, requestCode, permissions, grantResults);
    }
}
