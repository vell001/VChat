//
// Created by vellhe on 2020/2/19.
//

#pragma once

#include "cryptopp/sha.h"
#include "cryptopp/hex.h"
#include "cryptopp/base64.h"
#include <string>

namespace CryptUtils {
    std::string genRandStr(int size);

    std::string base64Encode(const unsigned char *byteArray);
    std::string hexEncode(const unsigned char *byteArray);
    std::string hashEncode(const std::string &message);
}
