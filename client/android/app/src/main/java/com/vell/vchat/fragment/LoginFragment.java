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

import com.vell.chat.account.LoginMsg;
import com.vell.vchat.R;

import static com.vell.vchat.GlobalValues.KEY_ACCOUNT;

public class LoginFragment extends BaseFragment {
    private EditText mEtAccount;
    private EditText mEtPassword;
    private Button mBtnLogin;
    private TextView mTvSignup;
    private CheckBox mCbShowPassword;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.frag_login, container, false);
        initView(view);
        return view;
    }

    @Override
    public void onActivityCreated(@Nullable Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);
        updateArguments(getArguments());
    }

    @Override
    public void updateArguments(Bundle bundle) {
        if (bundle == null) {
            return;
        }

        mEtAccount.setText(bundle.getString(KEY_ACCOUNT, ""));
    }

    private void initView(View root) {
        mEtAccount = root.findViewById(R.id.et_account);
        mEtPassword = root.findViewById(R.id.et_password);
        mBtnLogin = root.findViewById(R.id.btn_login);
        mTvSignup = root.findViewById(R.id.tv_signup);
        mCbShowPassword = root.findViewById(R.id.cb_show_password);

        mBtnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                actionLogin(new LoginMsg(mEtAccount.getText().toString(), mEtPassword.getText().toString()));
            }
        });

        mTvSignup.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showFragment(SignupFragment.class, null);
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
