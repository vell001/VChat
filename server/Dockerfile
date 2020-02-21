# vchat-server
FROM ubuntu:16.04

# 安装bazel
RUN apt update && apt install g++ libmysql++-dev libcrypto++ -y

ENV WORKSPACE /usr/src/app

COPY docker_workspace $WORKSPACE

ENV PORT 50051
EXPOSE 50051