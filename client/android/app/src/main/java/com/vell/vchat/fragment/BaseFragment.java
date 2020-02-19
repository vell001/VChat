package com.vell.vchat.fragment;

import android.app.Activity;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import com.vell.chat.account.LoginMsg;
import com.vell.chat.account.SignupMsg;
import com.vell.vchat.AccountAct;

public class BaseFragment extends Fragment {
    public void showFragment(Class fragClass, Bundle args) {
        Activity activity = getActivity();
        if (!(activity instanceof AccountAct)) {
            return;
        }
        ((AccountAct) activity).showFragment(fragClass, args);
    }

    public void actionSignup(SignupMsg info) {
        Activity activity = getActivity();
        if (!(activity instanceof AccountAct)) {
            return;
        }
        ((AccountAct) activity).actionSignup(info);
    }

    public void actionLogin(LoginMsg info) {
        Activity activity = getActivity();
        if (!(activity instanceof AccountAct)) {
            return;
        }
        ((AccountAct) activity).actionLogin(info);
    }

    public void updateArguments(Bundle args) {
    }
}
