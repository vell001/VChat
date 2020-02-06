// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#pragma once

#include "djinni_support.hpp"
#include "signup_msg.hpp"

namespace djinni_generated {

class NativeSignupMsg final {
public:
    using CppType = ::account_djinni::SignupMsg;
    using JniType = jobject;

    using Boxed = NativeSignupMsg;

    ~NativeSignupMsg();

    static CppType toCpp(JNIEnv* jniEnv, JniType j);
    static ::djinni::LocalRef<JniType> fromCpp(JNIEnv* jniEnv, const CppType& c);

private:
    NativeSignupMsg();
    friend ::djinni::JniClass<NativeSignupMsg>;

    const ::djinni::GlobalRef<jclass> clazz { ::djinni::jniFindClass("com/vell/chat/account/SignupMsg") };
    const jmethodID jconstructor { ::djinni::jniGetMethodID(clazz.get(), "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V") };
    const jfieldID field_mUsername { ::djinni::jniGetFieldID(clazz.get(), "mUsername", "Ljava/lang/String;") };
    const jfieldID field_mPassword { ::djinni::jniGetFieldID(clazz.get(), "mPassword", "Ljava/lang/String;") };
    const jfieldID field_mPhoneNumber { ::djinni::jniGetFieldID(clazz.get(), "mPhoneNumber", "Ljava/lang/String;") };
    const jfieldID field_mEmail { ::djinni::jniGetFieldID(clazz.get(), "mEmail", "Ljava/lang/String;") };
    const jfieldID field_mExtra { ::djinni::jniGetFieldID(clazz.get(), "mExtra", "Ljava/lang/String;") };
};

}  // namespace djinni_generated
