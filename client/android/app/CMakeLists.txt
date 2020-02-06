# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.2.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)

# grpc 编译
set(PROTOBUF_PROTOC_EXECUTABLE "/usr/local/bin/protoc" CACHE STRING "Protoc binary on host")
set(GRPC_CPP_PLUGIN_EXECUTABLE "/usr/local/bin/grpc_cpp_plugin" CACHE STRING "gRPC CPP plugin binary on host")

set(GRPC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/grpc)
set(GRPC_BUILD_DIR ${CMAKE_BINARY_DIR}/grpc/outputs/${ANDROID_ABI})

file(MAKE_DIRECTORY ${GRPC_BUILD_DIR})

add_subdirectory(${GRPC_SRC_DIR} ${GRPC_BUILD_DIR})

set(GRPC_PROTO_GENS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../generated-protos)
file(MAKE_DIRECTORY ${GRPC_PROTO_GENS_DIR})
include_directories(${GRPC_PROTO_GENS_DIR})

function(android_protobuf_grpc_generate_cpp SRC_FILES HDR_FILES INCLUDE_ROOT)
  if(NOT ARGN)
    message(SEND_ERROR "Error: android_protobuf_grpc_generate_cpp() called without any proto files")
    return()
  endif()

  set(${SRC_FILES})
  set(${HDR_FILES})
  set(PROTOBUF_INCLUDE_PATH -I ${INCLUDE_ROOT})
  foreach(FIL ${ARGN})
    get_filename_component(ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component(FIL_WE ${FIL} NAME_WE)
    file(RELATIVE_PATH REL_FIL ${CMAKE_CURRENT_SOURCE_DIR}/${INCLUDE_ROOT} ${ABS_FIL})
    get_filename_component(REL_DIR ${REL_FIL} DIRECTORY)
    set(RELFIL_WE "${REL_DIR}/${FIL_WE}")

    list(APPEND ${SRC_FILES} "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.cc")
    list(APPEND ${HDR_FILES} "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.h")
    list(APPEND ${SRC_FILES} "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.cc")
    list(APPEND ${HDR_FILES} "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.h")

    add_custom_command(
      OUTPUT "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.cc"
             "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.grpc.pb.h"
             "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.cc"
             "${GRPC_PROTO_GENS_DIR}/${RELFIL_WE}.pb.h"
      COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
      ARGS --grpc_out=${GRPC_PROTO_GENS_DIR}
        --cpp_out=${GRPC_PROTO_GENS_DIR}
        --plugin=protoc-gen-grpc=${GRPC_CPP_PLUGIN_EXECUTABLE}
        ${PROTOBUF_INCLUDE_PATH}
        ${REL_FIL}
      WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
      DEPENDS ${PROTOBUF_PROTOC_EXECUTABLE} ${GRPC_CPP_PLUGIN_EXECUTABLE} ${ABS_FIL} )
  endforeach()

  set_source_files_properties(${${SRC_FILES}} ${${HDR_FILES}} PROPERTIES GENERATED TRUE)
  set(${SRC_FILES} ${${SRC_FILES}} PARENT_SCOPE)
  set(${HDR_FILES} ${${HDR_FILES}} PARENT_SCOPE)
endfunction()

set(PROTO_BASE_DIR ../../../server/account/protos/)

android_protobuf_grpc_generate_cpp(
  ACCOUNT_PROTO_SRCS ACCOUNT_PROTO_HDRS ${PROTO_BASE_DIR} ${PROTO_BASE_DIR}/account.proto)
include_directories(${ACCOUNT_PROTO_HDRS})

add_library(account_proto_lib
  SHARED ${ACCOUNT_PROTO_HDRS} ${ACCOUNT_PROTO_SRCS})

target_link_libraries(account_proto_lib
  grpc++
  libprotobuf
  android
  log)

#文件目录
set(LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/src/main/jniLibs)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src/cpp)
set(GEN_CPP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../generated-src/cpp)
set(GEN_JNI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../generated-src/jni)
set(DJINNI_SUPPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/djinni/support-lib/)
set(DJINNI_SUPPORT_JNI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../deps/djinni/support-lib/jni)


#包含头文件目录
include_directories(${GEN_CPP_DIR})
include_directories(${GEN_JNI_DIR})
include_directories(${DJINNI_SUPPORT_DIR})
include_directories(${DJINNI_SUPPORT_JNI_DIR})


file(GLOB_RECURSE CPP_SRCS "${SRC_DIR}/*.cpp"
        "${GEN_CPP_DIR}/*.hpp" "${GEN_JNI_DIR}/*.cpp"
        "${DJINNI_SUPPORT_JNI_DIR}/*.cpp")

find_library(log-lib log)

set(TARGET_NAME vchat)
add_library(${TARGET_NAME} SHARED ${CPP_SRCS})
target_link_libraries(
        ${TARGET_NAME}
        ${log-lib}
        account_proto_lib
)