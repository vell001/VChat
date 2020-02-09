package com.vell.vchat.fragment;

import android.app.Activity;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import com.vell.vchat.AccountAct;

public class BaseFragment extends Fragment {
    public void showFragment(Class fragClass, Bundle args) {
        Activity activity = getActivity();
        if (!(activity instanceof AccountAct)) {
            return;
        }
        ((AccountAct) activity).showFragment(fragClass, args);
    }

    public void updateArguments(Bundle args) {

    }
}
