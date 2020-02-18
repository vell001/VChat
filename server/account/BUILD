load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load('@com_github_google_glog//:bazel/glog.bzl', 'glog_library')

glog_library()

proto_library(
    name = "account_proto",
    srcs = ["protos/account.proto"],
)

cc_proto_library(
    name = "account_cc_proto",
    deps = [":account_proto"],
)

cc_grpc_library(
    name = "account_cc_grpc",
    srcs = [":account_proto"],
    grpc_only = True,
    deps = [":account_cc_proto"],
)

cc_binary(
    name = 'account_server',
    srcs = glob(["**/*.cc","**/*.cpp","**/*.h","**/*.hpp"]),
    includes = ["src", "include"],
    deps = [
        ':account_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_google_glog//:glog',
        '@com_github_open_source_parsers_jsoncpp//:jsoncpp',
    ],
    linkopts = ['-ldl', "-lmysqlclient"],
)
