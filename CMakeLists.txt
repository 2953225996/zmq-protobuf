cmake_minimum_required(VERSION 3.16.3)
project(zmq&protobuf)

# 指定可执行文件生成目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 指定头文件目录
# include_directories(${PROJECT_SOURCE_DIR})

# 生成可执行文件
add_executable(server server.cpp stu.pb.cc)
add_executable(client client.cpp stu.pb.cc)

# 为可执行文件链接库文件
target_link_libraries(server zmq protobuf pthread)
target_link_libraries(client zmq protobuf pthread)