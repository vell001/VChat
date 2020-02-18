# vchat-server
FROM ubuntu:16.04

# 安装bazel
RUN apt update && apt install g++ unzip zip openjdk-8-jdk curl libmysql++-dev -y \
&& echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list \
&& curl https://bazel.build/bazel-release.pub.gpg | apt-key add - \
&& apt-get update \
&& apt-get install -y bazel

RUN bazel run //account:account_server