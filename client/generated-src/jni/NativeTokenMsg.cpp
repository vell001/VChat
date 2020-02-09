// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#include "NativeTokenMsg.hpp"  // my header
#include "Marshal.hpp"

namespace djinni_generated {

NativeTokenMsg::NativeTokenMsg() = default;

NativeTokenMsg::~NativeTokenMsg() = default;

auto NativeTokenMsg::fromCpp(JNIEnv* jniEnv, const CppType& c) -> ::djinni::LocalRef<JniType> {
    const auto& data = ::djinni::JniClass<NativeTokenMsg>::get();
    auto r = ::djinni::LocalRef<JniType>{jniEnv->NewObject(data.clazz.get(), data.jconstructor,
                                                           ::djinni::get(::djinni::String::fromCpp(jniEnv, c.token)),
                                                           ::djinni::get(::djinni::I32::fromCpp(jniEnv, c.expiration_time_sec)))};
    ::djinni::jniExceptionCheck(jniEnv);
    return r;
}

auto NativeTokenMsg::toCpp(JNIEnv* jniEnv, JniType j) -> CppType {
    ::djinni::JniLocalScope jscope(jniEnv, 3);
    assert(j != nullptr);
    const auto& data = ::djinni::JniClass<NativeTokenMsg>::get();
    return {::djinni::String::toCpp(jniEnv, (jstring)jniEnv->GetObjectField(j, data.field_mToken)),
            ::djinni::I32::toCpp(jniEnv, jniEnv->GetIntField(j, data.field_mExpirationTimeSec))};
}

}  // namespace djinni_generated
