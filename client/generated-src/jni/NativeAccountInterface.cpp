// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#include "NativeAccountInterface.hpp"  // my header
#include "Marshal.hpp"
#include "NativeAccountInfo.hpp"
#include "NativeAccountListener.hpp"
#include "NativeLoginMsg.hpp"
#include "NativeSignupMsg.hpp"

namespace djinni_generated {

NativeAccountInterface::NativeAccountInterface() : ::djinni::JniInterface<::account_djinni::AccountInterface, NativeAccountInterface>("com/vell/chat/account/AccountInterface$CppProxy") {}

NativeAccountInterface::~NativeAccountInterface() = default;


CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_nativeDestroy(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        delete reinterpret_cast<::djinni::CppProxyHandle<::account_djinni::AccountInterface>*>(nativeRef);
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_getInstance(JNIEnv* jniEnv, jobject /*this*/)
{
    try {
        DJINNI_FUNCTION_PROLOGUE0(jniEnv);
        auto r = ::account_djinni::AccountInterface::get_instance();
        return ::djinni::release(::djinni_generated::NativeAccountInterface::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1init(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->init();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1addListener(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_listener)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->add_listener(::djinni_generated::NativeAccountListener::toCpp(jniEnv, j_listener));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1removeListener(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_listener)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->remove_listener(::djinni_generated::NativeAccountListener::toCpp(jniEnv, j_listener));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1signup(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_info, jint j_seqId)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->signup(::djinni_generated::NativeSignupMsg::toCpp(jniEnv, j_info),
                    ::djinni::I32::toCpp(jniEnv, j_seqId));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1login(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jobject j_info, jint j_seqId)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->login(::djinni_generated::NativeLoginMsg::toCpp(jniEnv, j_info),
                   ::djinni::I32::toCpp(jniEnv, j_seqId));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1logout(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef, jint j_seqId)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->logout(::djinni::I32::toCpp(jniEnv, j_seqId));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jobject JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1getAccountInfo(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        auto r = ref->getAccountInfo();
        return ::djinni::release(::djinni_generated::NativeAccountInfo::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

CJNIEXPORT void JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1isAlive(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        ref->is_alive();
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, )
}

CJNIEXPORT jboolean JNICALL Java_com_vell_chat_account_AccountInterface_00024CppProxy_native_1hasLogin(JNIEnv* jniEnv, jobject /*this*/, jlong nativeRef)
{
    try {
        DJINNI_FUNCTION_PROLOGUE1(jniEnv, nativeRef);
        const auto& ref = ::djinni::objectFromHandleAddress<::account_djinni::AccountInterface>(nativeRef);
        auto r = ref->has_login();
        return ::djinni::release(::djinni::Bool::fromCpp(jniEnv, r));
    } JNI_TRANSLATE_EXCEPTIONS_RETURN(jniEnv, 0 /* value doesn't matter */)
}

}  // namespace djinni_generated
