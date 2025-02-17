// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: account.proto

#include "account.pb.h"
#include "account.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace account {

static const char* Account_method_names[] = {
  "/account.Account/signup",
  "/account.Account/login",
  "/account.Account/logout",
  "/account.Account/isAlive",
  "/account.Account/refreshToken",
};

std::unique_ptr< Account::Stub> Account::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Account::Stub> stub(new Account::Stub(channel));
  return stub;
}

Account::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_signup_(Account_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_login_(Account_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_logout_(Account_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_isAlive_(Account_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_refreshToken_(Account_method_names[4], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Account::Stub::signup(::grpc::ClientContext* context, const ::account::SignupMsg& request, ::account::AccountRespWithInfo* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_signup_, context, request, response);
}

void Account::Stub::experimental_async::signup(::grpc::ClientContext* context, const ::account::SignupMsg* request, ::account::AccountRespWithInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_signup_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::signup(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountRespWithInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_signup_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::signup(::grpc::ClientContext* context, const ::account::SignupMsg* request, ::account::AccountRespWithInfo* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_signup_, context, request, response, reactor);
}

void Account::Stub::experimental_async::signup(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountRespWithInfo* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_signup_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::account::AccountRespWithInfo>* Account::Stub::AsyncsignupRaw(::grpc::ClientContext* context, const ::account::SignupMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountRespWithInfo>::Create(channel_.get(), cq, rpcmethod_signup_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::account::AccountRespWithInfo>* Account::Stub::PrepareAsyncsignupRaw(::grpc::ClientContext* context, const ::account::SignupMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountRespWithInfo>::Create(channel_.get(), cq, rpcmethod_signup_, context, request, false);
}

::grpc::Status Account::Stub::login(::grpc::ClientContext* context, const ::account::LoginMsg& request, ::account::AccountRespWithInfo* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_login_, context, request, response);
}

void Account::Stub::experimental_async::login(::grpc::ClientContext* context, const ::account::LoginMsg* request, ::account::AccountRespWithInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_login_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountRespWithInfo* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_login_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::login(::grpc::ClientContext* context, const ::account::LoginMsg* request, ::account::AccountRespWithInfo* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_login_, context, request, response, reactor);
}

void Account::Stub::experimental_async::login(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountRespWithInfo* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_login_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::account::AccountRespWithInfo>* Account::Stub::AsyncloginRaw(::grpc::ClientContext* context, const ::account::LoginMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountRespWithInfo>::Create(channel_.get(), cq, rpcmethod_login_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::account::AccountRespWithInfo>* Account::Stub::PrepareAsyncloginRaw(::grpc::ClientContext* context, const ::account::LoginMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountRespWithInfo>::Create(channel_.get(), cq, rpcmethod_login_, context, request, false);
}

::grpc::Status Account::Stub::logout(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::account::AccountResp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_logout_, context, request, response);
}

void Account::Stub::experimental_async::logout(::grpc::ClientContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_logout_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::logout(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_logout_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::logout(::grpc::ClientContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_logout_, context, request, response, reactor);
}

void Account::Stub::experimental_async::logout(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_logout_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::AsynclogoutRaw(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_logout_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::PrepareAsynclogoutRaw(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_logout_, context, request, false);
}

::grpc::Status Account::Stub::isAlive(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::account::AccountResp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_isAlive_, context, request, response);
}

void Account::Stub::experimental_async::isAlive(::grpc::ClientContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_isAlive_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::isAlive(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_isAlive_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::isAlive(::grpc::ClientContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_isAlive_, context, request, response, reactor);
}

void Account::Stub::experimental_async::isAlive(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_isAlive_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::AsyncisAliveRaw(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_isAlive_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::PrepareAsyncisAliveRaw(::grpc::ClientContext* context, const ::account::TokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_isAlive_, context, request, false);
}

::grpc::Status Account::Stub::refreshToken(::grpc::ClientContext* context, const ::account::RefreshTokenMsg& request, ::account::AccountResp* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_refreshToken_, context, request, response);
}

void Account::Stub::experimental_async::refreshToken(::grpc::ClientContext* context, const ::account::RefreshTokenMsg* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_refreshToken_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::refreshToken(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_refreshToken_, context, request, response, std::move(f));
}

void Account::Stub::experimental_async::refreshToken(::grpc::ClientContext* context, const ::account::RefreshTokenMsg* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_refreshToken_, context, request, response, reactor);
}

void Account::Stub::experimental_async::refreshToken(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::account::AccountResp* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_refreshToken_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::AsyncrefreshTokenRaw(::grpc::ClientContext* context, const ::account::RefreshTokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_refreshToken_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::account::AccountResp>* Account::Stub::PrepareAsyncrefreshTokenRaw(::grpc::ClientContext* context, const ::account::RefreshTokenMsg& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::account::AccountResp>::Create(channel_.get(), cq, rpcmethod_refreshToken_, context, request, false);
}

Account::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Account_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Account::Service, ::account::SignupMsg, ::account::AccountRespWithInfo>(
          std::mem_fn(&Account::Service::signup), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Account_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Account::Service, ::account::LoginMsg, ::account::AccountRespWithInfo>(
          std::mem_fn(&Account::Service::login), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Account_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Account::Service, ::account::TokenMsg, ::account::AccountResp>(
          std::mem_fn(&Account::Service::logout), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Account_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Account::Service, ::account::TokenMsg, ::account::AccountResp>(
          std::mem_fn(&Account::Service::isAlive), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Account_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Account::Service, ::account::RefreshTokenMsg, ::account::AccountResp>(
          std::mem_fn(&Account::Service::refreshToken), this)));
}

Account::Service::~Service() {
}

::grpc::Status Account::Service::signup(::grpc::ServerContext* context, const ::account::SignupMsg* request, ::account::AccountRespWithInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Account::Service::login(::grpc::ServerContext* context, const ::account::LoginMsg* request, ::account::AccountRespWithInfo* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Account::Service::logout(::grpc::ServerContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Account::Service::isAlive(::grpc::ServerContext* context, const ::account::TokenMsg* request, ::account::AccountResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Account::Service::refreshToken(::grpc::ServerContext* context, const ::account::RefreshTokenMsg* request, ::account::AccountResp* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace account

