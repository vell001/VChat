package com.vell.vchat;

import android.os.Bundle;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;

import com.tencent.mars.xlog.Log;
import com.vell.chat.account.AccountInterface;
import com.vell.chat.account.AccountListener;
import com.vell.chat.account.AccountResp;
import com.vell.vchat.fragment.BaseFragment;
import com.vell.vchat.fragment.LoginFragment;

public class AccountAct extends FragmentActivity {
    private static final String TAG = AccountAct.class.getSimpleName();

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.act_account);

        AccountInterface.getInstance().addListener(new AccountListener() {
            @Override
            public void onSignupCallback(AccountResp callback) {
                Log.d(TAG, "onIsAliveCallback: " + callback.toString());
                Toast.makeText(AccountAct.this, "onSignupCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onLoginCallback(AccountResp callback) {
                Log.d(TAG, "onLoginCallback: " + callback.toString());
                Toast.makeText(AccountAct.this, "onLoginCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onLogoutCallback(AccountResp callback) {
                Log.d(TAG, "onLogoutCallback: " + callback.toString());
                Toast.makeText(AccountAct.this, "onLogoutCallback: " + callback.toString(), Toast.LENGTH_LONG).show();
            }

            @Override
            public void onIsAliveCallback(AccountResp callback) {
                Log.d(TAG, "onIsAliveCallback: " + callback.toString());
            }
        });

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
}
