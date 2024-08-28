# 使用官方的Ubuntu基础镜像
FROM ubuntu:20.04
# 设置环境变量，防止交互式安装
ENV DEBIAN_FRONTEND=noninteractive
# 更新包列表并安装必要的软件包
RUN apt-get update && apt-get install -y \
build-essential \
cmake \
wget \
git \
libprotobuf-dev \
protobuf-compiler \
libzmq3-dev \
&& rm -rf /var/lib/apt/lists/*
# 创建工作目录
WORKDIR /app
# 将项目的源代码复制到工作目录
COPY . /app
# 运行CMake配置和构建项目
RUN mkdir -p build && cd build && \
cmake .. && \
make
# 设置容器启动时的默认命令
CMD ["./bin/client"]