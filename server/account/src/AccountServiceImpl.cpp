//
// Created by vellhe on 2020/2/4.
//

#include "AccountServiceImpl.h"

AccountServiceImpl::~AccountServiceImpl() {

}

grpc::Status AccountServiceImpl::signup(::grpc::ServerContext *context, const ::account::SignupReq *request,
                                        ::account::AccountResp *response) {
    return Service::signup(context, request, response);
}

grpc::Status AccountServiceImpl::login(::grpc::ServerContext *context, const ::account::LoginReq *request,
                                       ::account::AccountResp *response) {
    return Service::login(context, request, response);
}

grpc::Status AccountServiceImpl::logout(::grpc::ServerContext *context, const ::account::TokenReq *request,
                                        ::account::AccountResp *response) {
    return Service::logout(context, request, response);
}

grpc::Status AccountServiceImpl::isAlive(::grpc::ServerContext *context, const ::account::TokenReq *request,
                                         ::account::AccountResp *response) {
    return Service::isAlive(context, request, response);
}
