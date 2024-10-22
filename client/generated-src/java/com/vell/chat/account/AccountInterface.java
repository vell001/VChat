// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

package com.vell.chat.account;

import java.util.concurrent.atomic.AtomicBoolean;

public abstract class AccountInterface {
    /** 初始化 */
    public abstract void init();

    /** 全局事件监听 */
    public abstract void addListener(AccountListener listener);

    public abstract void removeListener(AccountListener listener);

    public abstract void signup(SignupMsg info, int seqId);

    /** seqId 函数请求id，在account_listener里callback */
    public abstract void login(LoginMsg info, int seqId);

    public abstract void logout(int seqId);

    public abstract AccountInfo getAccountInfo();

    /** 手动发起服务器是否在线检查，会异步定时检查 */
    public abstract void isAlive();

    /** 是否已经登录 */
    public abstract boolean hasLogin();

    /** 单例 */
    public static AccountInterface getInstance()
    {
        return CppProxy.getInstance();
    }

    private static final class CppProxy extends AccountInterface
    {
        private final long nativeRef;
        private final AtomicBoolean destroyed = new AtomicBoolean(false);

        private CppProxy(long nativeRef)
        {
            if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
            this.nativeRef = nativeRef;
        }

        private native void nativeDestroy(long nativeRef);
        public void _djinni_private_destroy()
        {
            boolean destroyed = this.destroyed.getAndSet(true);
            if (!destroyed) nativeDestroy(this.nativeRef);
        }
        protected void finalize() throws java.lang.Throwable
        {
            _djinni_private_destroy();
            super.finalize();
        }

        @Override
        public void init()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_init(this.nativeRef);
        }
        private native void native_init(long _nativeRef);

        @Override
        public void addListener(AccountListener listener)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_addListener(this.nativeRef, listener);
        }
        private native void native_addListener(long _nativeRef, AccountListener listener);

        @Override
        public void removeListener(AccountListener listener)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_removeListener(this.nativeRef, listener);
        }
        private native void native_removeListener(long _nativeRef, AccountListener listener);

        @Override
        public void signup(SignupMsg info, int seqId)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_signup(this.nativeRef, info, seqId);
        }
        private native void native_signup(long _nativeRef, SignupMsg info, int seqId);

        @Override
        public void login(LoginMsg info, int seqId)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_login(this.nativeRef, info, seqId);
        }
        private native void native_login(long _nativeRef, LoginMsg info, int seqId);

        @Override
        public void logout(int seqId)
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_logout(this.nativeRef, seqId);
        }
        private native void native_logout(long _nativeRef, int seqId);

        @Override
        public AccountInfo getAccountInfo()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_getAccountInfo(this.nativeRef);
        }
        private native AccountInfo native_getAccountInfo(long _nativeRef);

        @Override
        public void isAlive()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            native_isAlive(this.nativeRef);
        }
        private native void native_isAlive(long _nativeRef);

        @Override
        public boolean hasLogin()
        {
            assert !this.destroyed.get() : "trying to use a destroyed object";
            return native_hasLogin(this.nativeRef);
        }
        private native boolean native_hasLogin(long _nativeRef);

        public static native AccountInterface getInstance();
    }
}
