package com.vell.vchat;

import android.app.Dialog;
import android.os.Bundle;
import android.os.Environment;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.tencent.mars.xlog.Log;
import com.vell.chat.account.AccountInfo;
import com.vell.chat.account.AccountInterface;
import com.vell.chat.account.AccountListener;
import com.vell.chat.account.AccountResp;
import com.vell.chat.account.LoginMsg;
import com.vell.chat.account.SignupMsg;
import com.vell.vchat.fragment.AccountInfoFragment;
import com.vell.vchat.fragment.BaseFragment;
import com.vell.vchat.fragment.LoginFragment;

import java.io.File;
import java.util.concurrent.atomic.AtomicInteger;

import static com.vell.vchat.GlobalValues.KEY_account;
import static com.vell.vchat.GlobalValues.KEY_username;

public class AccountAct extends FragmentActivity {
    private static final String TAG = AccountAct.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_account);

        File baseSDCardDir = new File(Environment.getExternalStorageDirectory(), "vchat");
        if (!baseSDCardDir.exists() && !baseSDCardDir.mkdirs()) {
            Log.e(TAG, "sd卡无法访问");
            Toast.makeText(this, "sd卡无法访问", Toast.LENGTH_LONG).show();
        }

        AccountInterface.getInstance().init();
        AccountInterface.getInstance().addListener(accountListener);

        // 判断登陆状态
        if (AccountInterface.getInstance().hasLogin()) {
            // 显示用户信息
            showFragment(AccountInfoFragment.class, null);
        } else {
            // 显示登陆页
            showFragment(LoginFragment.class, null);
        }
    }

    private BaseFragment mLastShowFragment = null;

    public void showFragment(Class fragClass, Bundle args) {
        FragmentManager fm = getSupportFragmentManager();
        FragmentTransaction ft = fm.beginTransaction();

        String name = fragClass.getName();
        BaseFragment fragment = (BaseFragment) fm.findFragmentByTag(name);
        if (fragment == null) {
            fragment = (BaseFragment) Fragment.instantiate(this, name);
            fragment.setArguments(args);
            ft.add(R.id.fl_container, fragment, name);
            ft.show(fragment);
            fragment.actionShow();
        } else {
            fragment.updateArguments(args);
            ft.show(fragment);
            fragment.actionShow();
        }

        if (mLastShowFragment != null && mLastShowFragment != fragment) {
            ft.hide(mLastShowFragment);
            mLastShowFragment.actionHide();
        }

        mLastShowFragment = fragment;
        ft.commitAllowingStateLoss();
    }

    private Dialog loadingDialog = null;

    private void showLoadingDialog(String msg) {
        // 先关闭之前的loading页
        closeLoadingDialog();

        LayoutInflater inflater = LayoutInflater.from(this);
        View v = inflater.inflate(R.layout.dialog_loading, null);// 得到加载view
        LinearLayout layout = v.findViewById(R.id.dialog_loading_view);// 加载布局
        TextView tvTips = v.findViewById(R.id.tv_tips);// 提示文字
        tvTips.setText(msg);// 设置加载信息

        loadingDialog = new Dialog(this, R.style.Theme_AppCompat_Dialog_Alert);// 创建自定义样式dialog
        loadingDialog.setCancelable(false); // 是否可以按“返回键”消失
        loadingDialog.setCanceledOnTouchOutside(false); // 点击加载框以外的区域
        loadingDialog.setContentView(layout, new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.MATCH_PARENT));// 设置布局
        Window window = loadingDialog.getWindow();
        WindowManager.LayoutParams lp = window.getAttributes();
        lp.width = WindowManager.LayoutParams.WRAP_CONTENT;
        lp.height = WindowManager.LayoutParams.WRAP_CONTENT;
        window.setGravity(Gravity.CENTER);
        window.setAttributes(lp);
        window.setWindowAnimations(R.style.Theme_AppCompat_Dialog_Alert);
        loadingDialog.show();

//        AlertDialog.Builder builder = new AlertDialog.Builder(this);
//        builder.setTitle("title")
//                .setMessage("message")
//                .setPositiveButton("确定", new DialogInterface.OnClickListener() {
//                    public void onClick(DialogInterface dialog, int id) {
//
//                    }
//                })
//                .setNegativeButton("取消", new DialogInterface.OnClickListener() {
//                    public void onClick(DialogInterface dialog, int id) {
//
//                    }
//                });
//        loadingDialog = builder.create();
    }

    private void closeLoadingDialog() {
        if (loadingDialog != null) {
            loadingDialog.dismiss();
            loadingDialog = null;
        }
    }

    private int signupSeqId = -1;

    public void actionSignup(SignupMsg info) {
        showLoadingDialog("注册中...");
        signupSeqId = genSeqId();
        AccountInterface.getInstance().signup(info, signupSeqId);
    }

    public int loginSeqId = -1;

    public void actionLogin(LoginMsg info) {
        showLoadingDialog("登录中...");
        loginSeqId = genSeqId();
        AccountInterface.getInstance().login(info, loginSeqId);
    }

    public int logoutSeqId = -1;

    public void actionLogout() {
        showLoadingDialog("退出中...");
        logoutSeqId = genSeqId();
        AccountInterface.getInstance().logout(logoutSeqId);
    }

    private AccountListener accountListener = new AccountListener() {
        @Override
        public void onSignupCallback(final AccountResp callback, int seqId, AccountInfo info) {
            Log.d(TAG, "onSignupCallback: " + callback.toString());
            if (seqId != signupSeqId) {
                return;
            }
            if (callback.getCode() == GlobalValues.CODE_AccountResp_OK) {
                // 注册成功，跳转到登录页
                Bundle bundle = new Bundle();
                bundle.putString(KEY_account, info.getUsername());
                showFragment(LoginFragment.class, bundle);
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, callback.getMsg(), Toast.LENGTH_LONG).show();
//                    Toast.makeText(AccountAct.this, "onSignupCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
            closeLoadingDialog();
        }

        @Override
        public void onLoginCallback(final AccountResp callback, int seqId, AccountInfo info) {
            if (seqId != loginSeqId) {
                return;
            }
            if (callback.getCode() == GlobalValues.CODE_AccountResp_OK) {
                // 注册成功，跳转到账号信息页
                Bundle bundle = new Bundle();
                bundle.putString(KEY_username, info.getUsername());
                showFragment(AccountInfoFragment.class, bundle);
            }
            Log.d(TAG, "onLoginCallback: " + callback.toString());
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, callback.getMsg(), Toast.LENGTH_LONG).show();
//                    Toast.makeText(AccountAct.this, "onLoginCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
            closeLoadingDialog();
        }

        @Override
        public void onLogoutCallback(final AccountResp callback, int seqId) {
            if (seqId != logoutSeqId) {
                return;
            }
            if (callback.getCode() == GlobalValues.CODE_AccountResp_OK) {
                // 登出成功，跳转到登录页
                showFragment(LoginFragment.class, null);
            }
            Log.d(TAG, "onLogoutCallback: " + callback.toString());
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, callback.getMsg(), Toast.LENGTH_LONG).show();
//                    Toast.makeText(AccountAct.this, "onLogoutCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
            closeLoadingDialog();
        }

        @Override
        public void onIsAliveCallback(final AccountResp callback) {
            Log.d(TAG, "onIsAliveCallback: " + callback.toString());
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    if (callback.getCode() == GlobalValues.CODE_AccountResp_RefreshToken_RefreshTokenNotExist ||
                            callback.getCode() == GlobalValues.CODE_AccountResp_RefreshToken_RefreshTokenExpired ||
                            callback.getCode() == GlobalValues.CODE_AccountResp_RefreshToken_AccountNotExist
                    ) {
                        Toast.makeText(AccountAct.this, "登录信息已过期，请重新登录", Toast.LENGTH_LONG).show();
                    } else if (callback.getCode() == GlobalValues.CODE_AccountResp_RefreshToken_RefreshTokenIncorrect) {
                        Toast.makeText(AccountAct.this, "你已在其他终端登录", Toast.LENGTH_LONG).show();
                    }
                }
            });

            if (mLastShowFragment instanceof AccountInfoFragment) {
                AccountInfoFragment accountInfoFragment = (AccountInfoFragment) mLastShowFragment;
                accountInfoFragment.updateAccountInfo();
            }

            // 判断登陆状态
            if (!(mLastShowFragment instanceof LoginFragment) && !AccountInterface.getInstance().hasLogin()) {
                // 显示登陆页
                showFragment(LoginFragment.class, null);
            }
        }
    };

    private synchronized int genSeqId() {
        int id = mSeqId.get();
        if (id >= Integer.MAX_VALUE) {
            mSeqId.set(0);
        }
        mSeqId.incrementAndGet();
        return id;
    }

    private static AtomicInteger mSeqId = new AtomicInteger(0);
}
