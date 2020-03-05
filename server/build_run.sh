bazel build //account:account_server
cp -f bazel-bin/account/account_server docker_workspace/account_server_linux_amd64
cd docker_workspace && ./account_server_linux_amd64 --logtostderr=1
