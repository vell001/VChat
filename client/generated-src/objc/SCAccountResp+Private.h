// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from account.djinni

#import "SCAccountResp.h"
#include "account_resp.hpp"

static_assert(__has_feature(objc_arc), "Djinni requires ARC to be enabled for this file");

@class SCAccountResp;

namespace djinni_generated {

struct AccountResp
{
    using CppType = ::account::AccountResp;
    using ObjcType = SCAccountResp*;

    using Boxed = AccountResp;

    static CppType toCpp(ObjcType objc);
    static ObjcType fromCpp(const CppType& cpp);
};

}  // namespace djinni_generated
