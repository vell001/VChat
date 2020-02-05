# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.2.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_VERBOSE_MAKEFILE on)

#设置库目录
set(LIBRARY_DIRS ${CMAKE_SOURCE_DIR}/src/main/jniLibs)

#文件目录
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
)