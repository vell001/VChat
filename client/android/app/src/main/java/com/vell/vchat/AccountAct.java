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
import com.vell.chat.account.SignupMsg;
import com.vell.vchat.fragment.BaseFragment;
import com.vell.vchat.fragment.LoginFragment;

import java.util.concurrent.atomic.AtomicInteger;

public class AccountAct extends FragmentActivity {
    private static final String TAG = AccountAct.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_account);

        AccountInterface.getInstance().addListener(accountListener);

        showFragment(LoginFragment.class, null);
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

    private AccountListener accountListener = new AccountListener() {
        @Override
        public void onSignupCallback(final AccountResp callback, int seqId, AccountInfo info) {
            Log.d(TAG, "onSignupCallback: " + callback.toString());
            if (seqId != signupSeqId) {
                return;
            }
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(AccountAct.this, "onSignupCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
                }
            });
        }

        @Override
        public void onLoginCallback(AccountResp callback, int seqId, AccountInfo info) {
            if (seqId != loginSeqId) {
                return;
            }
            Log.d(TAG, "onLoginCallback: " + callback.toString());
            Toast.makeText(AccountAct.this, "onLoginCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
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
