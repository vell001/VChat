//
// Created by vellhe on 2020/2/4.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <glog/stl_logging.h>
#include <data_manager/DBManager.h>
#include "AccountServiceImpl.h"
#include "config/GlobalConfig.h"
#include <data_manager/CacheManager.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

void RunServer() {
    // 读取配置文件
    auto config = GlobalConfig::getInstance();
    config->init("./global_config.json");

    // 初始化数据库服务
    int code = DBManager::getInstance()->init(
            config->getDBHost(),
            config->getDBPort(),
            config->getDBName(),
            config->getDBUser(),
            config->getDBPassword(),
            config->getDBCharset()
    );
    if (code != global::DBCode::OK) {
        LOG(ERROR) << "数据库服务初始化失败: " << code << std::endl;
        return;
    }

    // 初始化缓存服务
    code = CacheManager::getInstance()->init(
            config->getRedisHost(),
            config->getRedisPort()
    );
    if (code != global::CacheCode::OK) {
        LOG(ERROR) << "缓存服务初始化失败: " << code << std::endl;
        return;
    }

    std::string server_address("0.0.0.0:50051");
    AccountServiceImpl service;


    grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp;
    pkcp.private_key = "-----BEGIN EC PARAMETERS-----\n"
                       "BgUrgQQAIg==\n"
                       "-----END EC PARAMETERS-----\n"
                       "-----BEGIN EC PRIVATE KEY-----\n"
                       "MIGkAgEBBDBkQDY4GXBsB0Us1shYZ+3vsg5yHzmid2ivwqSAy+i4KhGBiywtd0vs\n"
                       "hIK3JtFZkTagBwYFK4EEACKhZANiAAQujMhibMlK5kwynbODzY8XI61JVjJ0zk8e\n"
                       "QGmVwaAmaHcaMRNDTLUMErHOv6X+TY2AZt5eumWmnMKCSudUaSLlbmlcLB11qiDK\n"
                       "PPXkUa9dasEC/CMnebJwVHx0oCSkDEU=\n"
                       "-----END EC PRIVATE KEY-----";

    pkcp.cert_chain = "-----BEGIN CERTIFICATE-----\n"
                      "MIICAzCB7AIJAMr+2YGDGCIRMA0GCSqGSIb3DQEBCwUAMBsxGTAXBgNVBAMMEHZj\n"
                      "aGF0LnZlbGwwMDEuY2YwHhcNMjAwMzA0MTMzOTQ0WhcNMzAwMzAyMTMzOTQ0WjAb\n"
                      "MRkwFwYDVQQDDBB2Y2hhdC52ZWxsMDAxLmNmMHYwEAYHKoZIzj0CAQYFK4EEACID\n"
                      "YgAELozIYmzJSuZMMp2zg82PFyOtSVYydM5PHkBplcGgJmh3GjETQ0y1DBKxzr+l\n"
                      "/k2NgGbeXrplppzCgkrnVGki5W5pXCwddaogyjz15FGvXWrBAvwjJ3mycFR8dKAk\n"
                      "pAxFMA0GCSqGSIb3DQEBCwUAA4IBAQBvr9+oS3Oqjxa3T6ZZvA02zfTZav+NLgXL\n"
                      "v4rdFHguxSSW2htaZAxTNwyl53heF0b2RrNM6ztMp7M6atj6MWpkOZhvY7ru2q6K\n"
                      "GJnTlK2gbcH3/bj+g0uujXxBwh1Xebawgi9VbWWrEK7eLkiMqziRIHhUHmomklrA\n"
                      "Spu73Ahh2kF/98O8YKFXDek32SUwJeU97ZSnqODxF1/qvAxKlDte1oiuMCVU7dmm\n"
                      "7peim6ukDrkOcgjqZ3acUYm40e4HXgXVSo2qT0+i1Ncm2IKyAZ4Mk71jlQ9t1wmx\n"
                      "rZTTj6kPgXmwU98Pu2IVlsrilVOs4di/HzaklOchdTA6DAfmtywp\n"
                      "-----END CERTIFICATE-----";

    grpc::SslServerCredentialsOptions ssl_opts;
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
    ssl_opts.pem_key_cert_pairs.push_back(pkcp);
    ssl_opts.client_certificate_request = GRPC_SSL_REQUEST_AND_REQUIRE_CLIENT_CERTIFICATE_AND_VERIFY; // 双向校验
    std::shared_ptr<grpc::ServerCredentials> creds = grpc::SslServerCredentials(ssl_opts);

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, creds);
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG(INFO) << "Server listening on " << server_address << std::endl;
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char **argv) {
    // Initialize Google's logging library.
    google::InitGoogleLogging(argv[0]);

    // Optional: parse command line flags
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    RunServer();
    return 0;
}