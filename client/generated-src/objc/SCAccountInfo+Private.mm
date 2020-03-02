// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#import "SCAccountInfo+Private.h"
#import "DJIMarshal+Private.h"
#import "SCRefreshTokenMsg+Private.h"
#import "SCTokenMsg+Private.h"
#include <cassert>

namespace djinni_generated {

auto AccountInfo::toCpp(ObjcType obj) -> CppType
{
    assert(obj);
    return {::djinni::String::toCpp(obj.username),
            ::djinni::String::toCpp(obj.phoneNumber),
            ::djinni::String::toCpp(obj.email),
            ::djinni::String::toCpp(obj.extra),
            ::djinni_generated::TokenMsg::toCpp(obj.token),
            ::djinni_generated::RefreshTokenMsg::toCpp(obj.refreshToken)};
}

auto AccountInfo::fromCpp(const CppType& cpp) -> ObjcType
{
    return [[SCAccountInfo alloc] initWithUsername:(::djinni::String::fromCpp(cpp.username))
                                       phoneNumber:(::djinni::String::fromCpp(cpp.phoneNumber))
                                             email:(::djinni::String::fromCpp(cpp.email))
                                             extra:(::djinni::String::fromCpp(cpp.extra))
                                             token:(::djinni_generated::TokenMsg::fromCpp(cpp.token))
                                      refreshToken:(::djinni_generated::RefreshTokenMsg::fromCpp(cpp.refreshToken))];
}

}  // namespace djinni_generated
