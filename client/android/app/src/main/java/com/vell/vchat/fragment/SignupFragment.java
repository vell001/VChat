package com.vell.vchat.fragment;

import android.os.Bundle;
import android.text.method.HideReturnsTransformationMethod;
import android.text.method.PasswordTransformationMethod;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.vell.chat.account.AccountInfo;
import com.vell.chat.account.AccountInterface;
import com.vell.chat.account.SignupMsg;
import com.vell.vchat.R;

import static com.vell.vchat.GlobalValues.KEY_account;

public class SignupFragment extends BaseFragment {
    private EditText mEtUsername;
    private EditText mEtPhoneNum;
    private EditText mEtEmail;
    private EditText mEtPassword;
    private Button mBtnSignup;
    private TextView mTvLogin;
    private CheckBox mCbShowPassword;
    private View rootView;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        rootView = inflater.inflate(R.layout.frag_signup, container, false);
        initView(rootView);
        return rootView;
    }


    @Override
    public void actionHide() {
        if (rootView == null) {
            return;
        }
        mEtPassword.setText("");
    }

    @Override
    public void actionShow() {
        if (rootView == null) {
            return;
        }
        mEtPassword.setText("");
        AccountInfo accountInfo = AccountInterface.getInstance().getAccountInfo();
        mEtUsername.setText(accountInfo.getUsername());
    }

    private void initView(View root) {
        mEtUsername = root.findViewById(R.id.et_username);
        mEtPhoneNum = root.findViewById(R.id.et_phone_num);
        mEtEmail = root.findViewById(R.id.et_email);
        mEtPassword = root.findViewById(R.id.et_password);
        mBtnSignup = root.findViewById(R.id.btn_signup);
        mTvLogin = root.findViewById(R.id.tv_login);
        mCbShowPassword = root.findViewById(R.id.cb_show_password);

        mBtnSignup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                actionSignup(new SignupMsg(mEtUsername.getText().toString(),
                        mEtPassword.getText().toString(),
                        mEtPhoneNum.getText().toString(),
                        mEtEmail.getText().toString(), ""));
            }
        });

        mTvLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Bundle bundle = new Bundle();
                bundle.putString(KEY_account, mEtUsername.getText().toString());
                showFragment(LoginFragment.class, bundle);
            }
        });

        // 显示和隐藏密码
        mCbShowPassword.setChecked(false);
        mEtPassword.setTransformationMethod(PasswordTransformationMethod.getInstance());
        mCbShowPassword.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                if (isChecked) {
                    mEtPassword.setTransformationMethod(HideReturnsTransformationMethod.getInstance());
                    mEtPassword.setSelection(mEtPassword.getText().length());
                } else {
                    mEtPassword.setTransformationMethod(PasswordTransformationMethod.getInstance());
                    mEtPassword.setSelection(mEtPassword.getText().length());
                }
            }
        });
    }
}
