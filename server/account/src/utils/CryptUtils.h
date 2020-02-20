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

namespace CryptUtils {
    std::string genRandStr(int size);

    std::string base64Encode(const std::string &data);

    std::string hexEncode(const std::string &data);

    std::string hexDecode(const std::string &hexStr);

    std::string hashEncode(const std::string &message);

    std::string aesEncrypt(const std::string &str_in, const std::string &key, const std::string &iv);

    std::string aesDecrypt(const std::string &str_in, const std::string &key, const std::string &iv);
}
