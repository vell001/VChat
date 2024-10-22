// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include "djinni_support.hpp"
#include "login_msg.hpp"

namespace djinni_generated {

class NativeLoginMsg final {
public:
    using CppType = ::account_djinni::LoginMsg;
    using JniType = jobject;

    using Boxed = NativeLoginMsg;

    ~NativeLoginMsg();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    NativeLoginMsg();
    friend ::djinni::JniClass<NativeLoginMsg>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("com/vell/chat/account/LoginMsg") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;)V") };
    const jfieldID field_mAccount { ::djinni::jniGetFieldID(clazz.get(), "mAccount", "Ljava/lang/String;") };
    const jfieldID field_mPassword { ::djinni::jniGetFieldID(clazz.get(), "mPassword", "Ljava/lang/String;") };
};

}  // namespace djinni_generated
