package com.vell.vchat;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.vell.vchat.utils.PermissionsUtils;

public class MainAct extends Activity {
    static {
        System.loadLibrary("vchat");
    }

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_main);
        // 请求权限
        PermissionsUtils.getInstance().checkPermissions(this, new String[]{
                        Manifest.permission.WRITE_EXTERNAL_STORAGE,
                        Manifest.permission.READ_EXTERNAL_STORAGE},
                new PermissionsUtils.IPermissionsResult() {
                    @Override
                    public void passPermissions() {
                        // 打开AccountAct
                        startActivity(new Intent(MainAct.this, AccountAct.class));
                        finish();
                    }

                    @Override
                    public void forbidPermissions() {
                        // 退出应用
                        finish();
                    }
                });
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        PermissionsUtils.getInstance().onRequestPermissionsResult(this, requestCode, permissions, grantResults);
    }
}
