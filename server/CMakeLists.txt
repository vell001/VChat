cmake_minimum_required(VERSION 3.2.1)
set(TARGET_NAME vchat_server)
project(${TARGET_NAME})
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/grpc)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/deps/glog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/account)

file(GLOB_RECURSE CPP_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${TARGET_NAME} ${CPP_SRCS})
target_link_libraries(
        ${TARGET_NAME}
        glog
        grpc++
)