// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include "account_listener.hpp"
#include "djinni_support.hpp"

namespace djinni_generated {

class NativeAccountListener final : ::djinni::JniInterface<::account_djinni::AccountListener, NativeAccountListener> {
public:
    using CppType = std::shared_ptr<::account_djinni::AccountListener>;
    using CppOptType = std::shared_ptr<::account_djinni::AccountListener>;
    using JniType = jobject;

    using Boxed = NativeAccountListener;

    ~NativeAccountListener();

    static CppType toCpp(JNIEnv* jniEnv, JniType j) { return ::djinni::JniClass<NativeAccountListener>::get()._fromJava(jniEnv, j); }
    static ::djinni::LocalRef<JniType> fromCppOpt(JNIEnv* jniEnv, const CppOptType& c) { return {jniEnv, ::djinni::JniClass<NativeAccountListener>::get()._toJava(jniEnv, c)}; }
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c) { return fromCppOpt(jniEnv, c); }

private:
    NativeAccountListener();
    friend ::djinni::JniClass<NativeAccountListener>;
    friend ::djinni::JniInterface<::account_djinni::AccountListener, NativeAccountListener>;

    class JavaProxy final : ::djinni::JavaProxyHandle<JavaProxy>, public ::account_djinni::AccountListener
    {
    public:
        JavaProxy(JniType j);
        ~JavaProxy();

        void on_signup_callback(const ::account_djinni::AccountResp & callback, int32_t seqId, const ::account_djinni::AccountInfo & info) override;
        void on_login_callback(const ::account_djinni::AccountResp & callback, int32_t seqId, const ::account_djinni::AccountInfo & info) override;
        void on_logout_callback(const ::account_djinni::AccountResp & callback, int32_t seqId) override;
        void on_is_alive_callback(const ::account_djinni::AccountResp & callback) override;

    private:
        friend ::djinni::JniInterface<::account_djinni::AccountListener, ::djinni_generated::NativeAccountListener>;
    };

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("com/vell/chat/account/AccountListener") };
    const jmethodID method_onSignupCallback { ::djinni::jniGetMethodID(clazz.get(), "onSignupCallback", "(Lcom/vell/chat/account/AccountResp;ILcom/vell/chat/account/AccountInfo;)V") };
    const jmethodID method_onLoginCallback { ::djinni::jniGetMethodID(clazz.get(), "onLoginCallback", "(Lcom/vell/chat/account/AccountResp;ILcom/vell/chat/account/AccountInfo;)V") };
    const jmethodID method_onLogoutCallback { ::djinni::jniGetMethodID(clazz.get(), "onLogoutCallback", "(Lcom/vell/chat/account/AccountResp;I)V") };
    const jmethodID method_onIsAliveCallback { ::djinni::jniGetMethodID(clazz.get(), "onIsAliveCallback", "(Lcom/vell/chat/account/AccountResp;)V") };
};

}  // namespace djinni_generated
