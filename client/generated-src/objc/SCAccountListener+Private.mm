// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#import "SCAccountListener+Private.h"
#import "SCAccountListener.h"
#import "DJIMarshal+Private.h"
#import "DJIObjcWrapperCache+Private.h"
#import "SCAccountInfo+Private.h"
#import "SCAccountResp+Private.h"
#include <stdexcept>

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

namespace djinni_generated {

class AccountListener::ObjcProxy final
: public ::account_djinni::AccountListener
, private ::djinni::ObjcProxyBase<ObjcType>
{
    friend class ::djinni_generated::AccountListener;
public:
    using ObjcProxyBase::ObjcProxyBase;
    void on_signup_callback(const ::account_djinni::AccountResp & c_callback, int32_t c_seqId, const ::account_djinni::AccountInfo & c_info) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() onSignupCallback:(::djinni_generated::AccountResp::fromCpp(c_callback))
                                                                 seqId:(::djinni::I32::fromCpp(c_seqId))
                                                                  info:(::djinni_generated::AccountInfo::fromCpp(c_info))];
        }
    }
    void on_login_callback(const ::account_djinni::AccountResp & c_callback, int32_t c_seqId, const ::account_djinni::AccountInfo & c_info) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() onLoginCallback:(::djinni_generated::AccountResp::fromCpp(c_callback))
                                                                seqId:(::djinni::I32::fromCpp(c_seqId))
                                                                 info:(::djinni_generated::AccountInfo::fromCpp(c_info))];
        }
    }
    void on_logout_callback(const ::account_djinni::AccountResp & c_callback, int32_t c_seqId) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() onLogoutCallback:(::djinni_generated::AccountResp::fromCpp(c_callback))
                                                                 seqId:(::djinni::I32::fromCpp(c_seqId))];
        }
    }
    void on_is_alive_callback(const ::account_djinni::AccountResp & c_callback) override
    {
        @autoreleasepool {
            [djinni_private_get_proxied_objc_object() onIsAliveCallback:(::djinni_generated::AccountResp::fromCpp(c_callback))];
        }
    }
};

}  // namespace djinni_generated

namespace djinni_generated {

auto AccountListener::toCpp(ObjcType objc) -> CppType
{
    if (!objc) {
        return nullptr;
    }
    return ::djinni::get_objc_proxy<ObjcProxy>(objc);
}

auto AccountListener::fromCppOpt(const CppOptType& cpp) -> ObjcType
{
    if (!cpp) {
        return nil;
    }
    return dynamic_cast<ObjcProxy&>(*cpp).djinni_private_get_proxied_objc_object();
}

}  // namespace djinni_generated
