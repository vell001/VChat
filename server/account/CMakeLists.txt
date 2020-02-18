cmake_minimum_required(VERSION 3.2.1)
set(CMAKE_CXX_STANDARD 11)


include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

file(GLOB_RECURSE CPP_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp")

set(TARGET_NAME account_server)
add_library(${TARGET_NAME} STATIC ${CPP_SRCS})
target_link_libraries(
        ${TARGET_NAME}
        glog
        grpc++
)

target_include_directories(${TARGET_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")