//
// Created by vellhe on 2020/2/19.
//

#include "CryptUtils.h"

std::string CryptUtils::genRandStr(int size) {
    unsigned char str[size];
    CryptoPP::RandomNumberGenerator generator;
    generator.GenerateBlock(str, size);
    return hexEncode(str);
}

std::string CryptUtils::base64Encode(const unsigned char *byteArray) {
    std::string encoded;

    CryptoPP::Base64Encoder encoder;
    encoder.Put(byteArray, sizeof(byteArray));
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if (size) {
        encoded.resize(size);
        encoder.Get((unsigned char *) (&encoded[0]), encoded.size());
    }
    return encoded;
}

std::string CryptUtils::hexEncode(const unsigned char *byteArray) {
    std::string encoded;

    CryptoPP::HexEncoder encoder;
    encoder.Put(byteArray, sizeof(byteArray));
    encoder.MessageEnd();

    CryptoPP::word64 size = encoder.MaxRetrievable();
    if (size) {
        encoded.resize(size);
        encoder.Get((unsigned char *) (&encoded[0]), encoded.size());
    }
    return encoded;
}

std::string CryptUtils::hashEncode(const std::string &message) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(message, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
            new CryptoPP::StringSink(digest))));
    return digest;
}
