package com.vell.vchat.fragment;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import com.vell.chat.account.AccountInfo;
import com.vell.chat.account.AccountInterface;
import com.vell.chat.account.AccountListener;
import com.vell.chat.account.AccountResp;
import com.vell.vchat.GlobalValues;
import com.vell.vchat.R;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

import static com.vell.vchat.GlobalValues.KEY_account_info;
import static com.vell.vchat.GlobalValues.KEY_token_info;
import static com.vell.vchat.GlobalValues.KEY_username;


public class AccountInfoFragment extends BaseFragment {
    private TextView mTvUsername;
    private TextView mTvAccountInfo;
    private TextView mTvTokenInfo;
    private Button mBtnLogout;
    SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss", Locale.CHINESE);

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.frag_account_info, container, false);
        initView(view);
        return view;
    }

    private void initView(View root) {
        mTvUsername = root.findViewById(R.id.tv_username);
        mTvAccountInfo = root.findViewById(R.id.tv_account_info);
        mTvTokenInfo = root.findViewById(R.id.tv_token_info);
        mBtnLogout = root.findViewById(R.id.btn_logout);

        mBtnLogout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                actionLogout();
            }
        });
    }

    @Override
    public void onResume() {
        super.onResume();
        AccountInterface.getInstance().addListener(accountListener);
    }

    @Override
    public void onPause() {
        AccountInterface.getInstance().removeListener(accountListener);
        super.onPause();
    }

    @Override
    public void updateArguments(Bundle bundle) {
        if (bundle == null) {
            return;
        }
        mTvUsername.setText(bundle.getString(KEY_username, ""));
        mTvAccountInfo.setText(bundle.getString(KEY_account_info, ""));
        mTvTokenInfo.setText(bundle.getString(KEY_token_info, ""));
    }

    private AccountListener accountListener = new AccountListener() {
        @Override
        public void onSignupCallback(AccountResp callback, int seqId, AccountInfo info) {

        }

        @Override
        public void onLoginCallback(AccountResp callback, int seqId, AccountInfo info) {

        }

        @Override
        public void onLogoutCallback(AccountResp callback, int seqId) {

        }

        @Override
        public void onIsAliveCallback(final AccountResp callback) {
            // 更新账号信息
            final AccountInfo accountInfo = AccountInterface.getInstance().getAccountInfo();
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    mTvUsername.setText(accountInfo.getUsername());
                    mTvAccountInfo.setText(String.format("电话: %s\nemail: %s\n其他: %s", accountInfo.getPhoneNumber(), accountInfo.getEmail(), accountInfo.getExtra()));
                    mTvTokenInfo.setText(String.format(Locale.CHINESE, "token: %s\ntoken 过期时间: %s", accountInfo.getToken().getToken(), formatter.format(new Date(((long) accountInfo.getToken().getExpirationTimeSec()) * 1000))));
                    if (callback.getCode() == GlobalValues.CODE_AccountResp_OK) {

                    } else {

                    }
                }
            });
        }
    };
}
