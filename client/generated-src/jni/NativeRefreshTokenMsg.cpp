// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#include "NativeRefreshTokenMsg.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeRefreshTokenMsg::NativeRefreshTokenMsg() = default;

NativeRefreshTokenMsg::~NativeRefreshTokenMsg() = default;

auto NativeRefreshTokenMsg::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeRefreshTokenMsg>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c.refresh_token)),
                                                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c.expiration_time_sec)),
                                                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c.username)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeRefreshTokenMsg::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 4);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeRefreshTokenMsg>::get();
    return {::djinni::String::toCpp(jniEnv, (jstring)jniEnv->GetObjectField(j, data.field_mRefreshToken)),
            ::djinni::I32::toCpp(jniEnv, jniEnv->GetIntField(j, data.field_mExpirationTimeSec)),
            ::djinni::String::toCpp(jniEnv, (jstring)jniEnv->GetObjectField(j, data.field_mUsername))};
}

}  // namespace djinni_generated
