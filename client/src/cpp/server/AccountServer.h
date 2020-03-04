//
// Created by vellhe on 2020-02-06.
//

#pragma once

#include <grpc++/grpc++.h>
#include "account.grpc.pb.h"
#include "login_msg.hpp"
#include "signup_msg.hpp"
#include "token_msg.hpp"
#include "account_resp.hpp"
#include "account_info.hpp"
#include "refresh_token_msg.hpp"
#include "../Platform.h"
#include <GlobalValues.h>

using namespace std;

class AccountServer {
public:
    AccountServer() {
        grpc::SslCredentialsOptions ssl_opts;
        ssl_opts.pem_root_certs = "-----BEGIN CERTIFICATE-----\n"
                                  "MIICsjCCAZoCCQCCYZuV5OAGETANBgkqhkiG9w0BAQsFADAbMRkwFwYDVQQDDBB2\n"
                                  "Y2hhdC52ZWxsMDAxLmNmMB4XDTIwMDMwNDEzMzcyMVoXDTM5MTEyMDEzMzcyMVow\n"
                                  "GzEZMBcGA1UEAwwQdmNoYXQudmVsbDAwMS5jZjCCASIwDQYJKoZIhvcNAQEBBQAD\n"
                                  "ggEPADCCAQoCggEBALoAMuWJa/lIukniUhIiA1FXDvvYaqAvlI/cv0CsusAsna8c\n"
                                  "AwzWmowDGVDRgDiCKLrfXZxG5205EcU82/XPpq1H+H/+YGaECsU91QRsqVbKI0mz\n"
                                  "HmVuG+RnEl9pCOI1hD/ZOY0iws7WXvUpFol05GysTcYballwI4rOQBnDKpqEiLAs\n"
                                  "nEdWa4L5JK5eCf2LS244K9DNgogj4QLCNhnJW7bXbI4SpJRgoW8KHXZM4lJYlonR\n"
                                  "k5clpK1GOlUj6COtFEn6Y9OS+JsXzanmGTxu74CQsRTU7vWu/8Beb/TLmKicfDZ9\n"
                                  "wgtNHgSenD+tYjutOMwSS7RnTTpy0ZrpIo4FV/8CAwEAATANBgkqhkiG9w0BAQsF\n"
                                  "AAOCAQEAcSiDrOB4IYX+hplEjf5LTO5Pmc1JVHcYvVbJspWVGHyNtJDZ3KAxyyRP\n"
                                  "yZRelMBtwvHr3RNwog6xUsAjEdTjDyi1FE8TUZ+osVCNzJcMnwgO2R1LhJiMyq/H\n"
                                  "iEkhgd2aR2ulngiBMd7Jwbih5uxf1tPgk84pyNRPtkFI4F5Pwlirg9q3XIHjnMgM\n"
                                  "8wP2WdJYii5P4zlk/EZIT0lDtzipNgLrO/5S+FZjFKPwmKKmqfLEcRrmL+VyK46S\n"
                                  "IUzCK0Tt6o13gpNBRypq6sj4EhMVtEqYRFgi2Qg6FyXdH908DNj//b/2anosaHw1\n"
                                  "30zWgDaHEdkuYVCQeha5csxlScnXkw==\n"
                                  "-----END CERTIFICATE-----";

        ssl_opts.pem_private_key = "-----BEGIN EC PARAMETERS-----\n"
                                   "BgUrgQQAIg==\n"
                                   "-----END EC PARAMETERS-----\n"
                                   "-----BEGIN EC PRIVATE KEY-----\n"
                                   "MIGkAgEBBDA6nBXFljgIeZkOmceHPc5CFVN9MJmHpxnAD8Ea4P27euMq/bef3j2s\n"
                                   "5EE7LSVWThmgBwYFK4EEACKhZANiAARWaetDW+BRhpf/gZdNj7wlAR3kLdyeQFzT\n"
                                   "SQi5/X7DMBh65NnrMFS9Kh05Shzx0rlkWEY5s8g+Doxze73h7ZJyKT4cTgJDfrXs\n"
                                   "qaiozq2TQP46/aFZ/NebFlMrJiqydo0=\n"
                                   "-----END EC PRIVATE KEY-----";

        ssl_opts.pem_cert_chain = "-----BEGIN CERTIFICATE-----\n"
                                  "MIICAzCB7AIJAMr+2YGDGCISMA0GCSqGSIb3DQEBCwUAMBsxGTAXBgNVBAMMEHZj\n"
                                  "aGF0LnZlbGwwMDEuY2YwHhcNMjAwMzA0MTM0MDEyWhcNMzAwMzAyMTM0MDEyWjAb\n"
                                  "MRkwFwYDVQQDDBB2Y2hhdC52ZWxsMDAxLmNmMHYwEAYHKoZIzj0CAQYFK4EEACID\n"
                                  "YgAEVmnrQ1vgUYaX/4GXTY+8JQEd5C3cnkBc00kIuf1+wzAYeuTZ6zBUvSodOUoc\n"
                                  "8dK5ZFhGObPIPg6Mc3u94e2Scik+HE4CQ3617KmoqM6tk0D+Ov2hWfzXmxZTKyYq\n"
                                  "snaNMA0GCSqGSIb3DQEBCwUAA4IBAQA47OiRJqt0OnOpCHKznS9bfw2D8KABkXFb\n"
                                  "QzSdlkqQonC/nnqjCqm7adhQ0N0zjlQ5Gm284Rmd2S6+4omATKKcV/jg+iRIdS/F\n"
                                  "5LXaknGhcKewdag9VL18gdgGySH0809/tBvF+8NZONz6R46+U1tAuoSldZlQzCGz\n"
                                  "lHfAtO+q4ZDFSMBcA/W3biYebZlM5qpDIDyFHf6TKjMaWz+XJGVLUz8naCuYwliK\n"
                                  "PBvpRrJHNsYUrqY6q8WC0CWc6nEVr2uHAhzL587EujiFhEHVyvLaUBCrc2LcA0ju\n"
                                  "BXqvq5c5EwEeysv7y172kn1GKbJiJFyFHUaeHP/rgpvwEWqnAH6x\n"
                                  "-----END CERTIFICATE-----";
        auto channel = grpc::CreateChannel("vchat.vell001.cf:50051", grpc::SslCredentials(ssl_opts));
        stub_ = account::Account::NewStub(channel);
    }

    void signup(const account_djinni::SignupMsg &info, account_djinni::AccountResp &resp,
                account_djinni::AccountInfo &accountInfo);

    void login(const account_djinni::LoginMsg &info, account_djinni::AccountResp &resp,
               account_djinni::AccountInfo &accountInfo);

    void logout(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp);

    void is_alive(const account_djinni::TokenMsg &token, account_djinni::AccountResp &resp);

    void refresh_token(const account_djinni::RefreshTokenMsg &refreshToken,
                       account_djinni::AccountResp &resp);

    static std::shared_ptr<AccountServer> getInstance();

private:
    std::unique_ptr<account::Account::Stub> stub_;
};

