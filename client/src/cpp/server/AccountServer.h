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
                                  "MIIErjCCA5agAwIBAgIQBYAmfwbylVM0jhwYWl7uLjANBgkqhkiG9w0BAQsFADBh\n"
                                  "MQswCQYDVQQGEwJVUzEVMBMGA1UEChMMRGlnaUNlcnQgSW5jMRkwFwYDVQQLExB3\n"
                                  "d3cuZGlnaWNlcnQuY29tMSAwHgYDVQQDExdEaWdpQ2VydCBHbG9iYWwgUm9vdCBD\n"
                                  "QTAeFw0xNzEyMDgxMjI4MjZaFw0yNzEyMDgxMjI4MjZaMHIxCzAJBgNVBAYTAkNO\n"
                                  "MSUwIwYDVQQKExxUcnVzdEFzaWEgVGVjaG5vbG9naWVzLCBJbmMuMR0wGwYDVQQL\n"
                                  "ExREb21haW4gVmFsaWRhdGVkIFNTTDEdMBsGA1UEAxMUVHJ1c3RBc2lhIFRMUyBS\n"
                                  "U0EgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQCgWa9X+ph+wAm8\n"
                                  "Yh1Fk1MjKbQ5QwBOOKVaZR/OfCh+F6f93u7vZHGcUU/lvVGgUQnbzJhR1UV2epJa\n"
                                  "e+m7cxnXIKdD0/VS9btAgwJszGFvwoqXeaCqFoP71wPmXjjUwLT70+qvX4hdyYfO\n"
                                  "JcjeTz5QKtg8zQwxaK9x4JT9CoOmoVdVhEBAiD3DwR5fFgOHDwwGxdJWVBvktnoA\n"
                                  "zjdTLXDdbSVC5jZ0u8oq9BiTDv7jAlsB5F8aZgvSZDOQeFrwaOTbKWSEInEhnchK\n"
                                  "ZTD1dz6aBlk1xGEI5PZWAnVAba/ofH33ktymaTDsE6xRDnW97pDkimCRak6CEbfe\n"
                                  "3dXw6OV5AgMBAAGjggFPMIIBSzAdBgNVHQ4EFgQUf9OZ86BHDjEAVlYijrfMnt3K\n"
                                  "AYowHwYDVR0jBBgwFoAUA95QNVbRTLtm8KPiGxvDl7I90VUwDgYDVR0PAQH/BAQD\n"
                                  "AgGGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjASBgNVHRMBAf8ECDAG\n"
                                  "AQH/AgEAMDQGCCsGAQUFBwEBBCgwJjAkBggrBgEFBQcwAYYYaHR0cDovL29jc3Au\n"
                                  "ZGlnaWNlcnQuY29tMEIGA1UdHwQ7MDkwN6A1oDOGMWh0dHA6Ly9jcmwzLmRpZ2lj\n"
                                  "ZXJ0LmNvbS9EaWdpQ2VydEdsb2JhbFJvb3RDQS5jcmwwTAYDVR0gBEUwQzA3Bglg\n"
                                  "hkgBhv1sAQIwKjAoBggrBgEFBQcCARYcaHR0cHM6Ly93d3cuZGlnaWNlcnQuY29t\n"
                                  "L0NQUzAIBgZngQwBAgEwDQYJKoZIhvcNAQELBQADggEBAK3dVOj5dlv4MzK2i233\n"
                                  "lDYvyJ3slFY2X2HKTYGte8nbK6i5/fsDImMYihAkp6VaNY/en8WZ5qcrQPVLuJrJ\n"
                                  "DSXT04NnMeZOQDUoj/NHAmdfCBB/h1bZ5OGK6Sf1h5Yx/5wR4f3TUoPgGlnU7EuP\n"
                                  "ISLNdMRiDrXntcImDAiRvkh5GJuH4YCVE6XEntqaNIgGkRwxKSgnU3Id3iuFbW9F\n"
                                  "UQ9Qqtb1GX91AJ7i4153TikGgYCdwYkBURD8gSVe8OAco6IfZOYt/TEwii1Ivi1C\n"
                                  "qnuUlWpsF1LdQNIdfbW3TSe0BhQa7ifbVIfvPWHYOu3rkg1ZeMo6XRU9B4n5VyJY\n"
                                  "RmE=\n"
                                  "-----END CERTIFICATE-----";

        ssl_opts.pem_private_key = "";
        ssl_opts.pem_cert_chain = "";
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

