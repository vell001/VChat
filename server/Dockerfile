# vchat-server
FROM ubuntu:16.04

# 安装bazel
RUN apt update && apt install g++ wget lsb-release -y && \
wget https://dev.mysql.com/get/mysql-apt-config_0.8.15-1_all.deb && \
echo -e "4\n" | dpkg -i mysql-apt-config_0.8.15-1_all.deb && \
apt update && apt install libmysql++-dev libcrypto++ libmysqlclient-dev libmysqlclient21 -y

ENV WORKSPACE /usr/src/app

COPY docker_workspace $WORKSPACE

ENV PORT 50051
EXPOSE 50051

# 测试
RUN cd $WORKSPACE && ./account_server_linux_amd64