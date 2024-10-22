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

    // 配置ssl
    grpc::SslServerCredentialsOptions ssl_opts;

    ssl_opts.pem_root_certs = config->getSslCARootCert();
//    LOG(INFO) << "pem_root_certs: " << ssl_opts.pem_root_certs;
    ssl_opts.pem_key_cert_pairs.push_back({config->getSslServerKey(), config->getSslServerCert()});

    ssl_opts.client_certificate_request = GRPC_SSL_DONT_REQUEST_CLIENT_CERTIFICATE; // 单向校验
    std::shared_ptr<grpc::ServerCredentials> serverCredentials = grpc::SslServerCredentials(ssl_opts);

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, serverCredentials);
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