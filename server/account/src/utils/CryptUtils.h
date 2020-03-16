//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/base64.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"
#include "cryptopp/config.h"
#include "cryptopp/cryptlib.h"
#include "cryptopp/randpool.h"
#include "cryptopp/osrng.h"
#include <string>

/**
 * 加解密工具类
 */
namespace CryptUtils {
    /**
     * 获取随机字符串
     *
     * @param size 随机字符串大小
     * @return 随机字符串
     */
    std::string genRandStr(int size);

    /**
     * base64编码
     *
     * @param data 输入数据，存储在string内
     * @return 输出base64编码后字符串
     */
    std::string base64Encode(const std::string &data);

    /**
     * 16进制编码
     *
     * @param data 输入数据，存储在string内
     * @return 输出16进制编码后字符串
     */
    std::string hexEncode(const std::string &data);

    /**
     * 16进制解码
     *
     * @param data 输入数据，16进制字符串
     * @return 输出16进制解码后字节码，存储在string内
     */
    std::string hexDecode(const std::string &hexStr);

    /**
     * 哈希编码，sha256
     *
     * @param message 输入数据，存储在string内
     * @return 输出哈希编码后字符串
     */
    std::string hashEncode(const std::string &message);

    /**
     * AES编码，CBC_Mode
     *
     * @param str_in 输入数据，存储在string内
     * @param key AES 密钥
     * @param iv AES 初始向量
     * @return 输出base64编码后的AES编码后字节码
     */
    std::string aesEncrypt(const std::string &str_in, const std::string &key, const std::string &iv);

    /**
     * AES解码
     * @param str_in 输入数据，base64编码后字符串
     * @param key AES 密钥
     * @param iv AES 初始向量
     * @return 解码后字节码，存储在string内
     */
    std::string aesDecrypt(const std::string &str_in, const std::string &key, const std::string &iv);
}
