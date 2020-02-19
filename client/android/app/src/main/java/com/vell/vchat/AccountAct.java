package com.vell.vchat;

import android.os.Bundle;
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

import java.util.concurrent.atomic.AtomicInteger;

import static com.vell.vchat.GlobalValues.KEY_ACCOUNT;

public class AccountAct extends FragmentActivity {
    private static final String TAG = AccountAct.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_account);

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
        } else {
            fragment.updateArguments(args);
            ft.show(fragment);
        }

        if (mLastShowFragment != null) {
            ft.hide(mLastShowFragment);
        }

        mLastShowFragment = fragment;
        ft.commitAllowingStateLoss();
    }

    private int signupSeqId = -1;
    public int logoutSeqId = -1;

    public void actionSignup(SignupMsg info) {
        signupSeqId = genSeqId();
        AccountInterface.getInstance().signup(info, signupSeqId);
    }

    public int loginSeqId = -1;
    public void actionLogin(LoginMsg info) {
        loginSeqId = genSeqId();
        AccountInterface.getInstance().login(info, loginSeqId);
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
                bundle.putString(KEY_ACCOUNT, info.getUsername());
                showFragment(LoginFragment.class, bundle);
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, "onSignupCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onLoginCallback(final AccountResp callback, int seqId, AccountInfo info) {
            if (seqId != loginSeqId) {
                return;
            }
            if (callback.getCode() == GlobalValues.CODE_AccountResp_OK) {
                // 注册成功，跳转到账号信息页
                showFragment(AccountInfoFragment.class, null);
            }
            Log.d(TAG, "onLoginCallback: " + callback.toString());
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, "onLoginCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onLogoutCallback(AccountResp callback, int seqId) {
            Log.d(TAG, "onLogoutCallback: " + callback.toString());
            Toast.makeText(AccountAct.this, "onLogoutCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
        }

        @Override
        public void onIsAliveCallback(AccountResp callback) {
            Log.d(TAG, "onIsAliveCallback: " + callback.toString());
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
