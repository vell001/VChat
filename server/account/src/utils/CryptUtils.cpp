//
// Created by vellhe on 2020/2/19.
//

#include "CryptUtils.h"

std::string CryptUtils::genRandStr(int size) {
    CryptoPP::SecByteBlock scratch(size);
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(scratch, scratch.size());
    std::string str(reinterpret_cast<const char *>(&scratch[0]), scratch.size());
    return base64Encode(str);
}

std::string CryptUtils::base64Encode(const std::string &data) {
    std::string encoded;
    CryptoPP::StringSource encode(data, true,
                                  new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded), false));
    return encoded;
}

std::string CryptUtils::hexEncode(const std::string &data) {
    std::string encoded;
    CryptoPP::StringSource encode(data, true,
                                  new CryptoPP::HexEncoder(new CryptoPP::StringSink(encoded)));
    return encoded;
}

std::string CryptUtils::hexDecode(const std::string &hexStr) {
    std::string decoded;
    CryptoPP::StringSource decode(hexStr, true,
                                  new CryptoPP::HexDecoder(new CryptoPP::StringSink(decoded)));
    return decoded;
}

std::string CryptUtils::hashEncode(const std::string &message) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(message, true,
                             new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(
                                     new CryptoPP::StringSink(digest))));
    return digest;
}

std::string CryptUtils::aesEncrypt(const std::string &str_in, const std::string &key, const std::string &iv) {
    std::string str_out;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption((unsigned char *) key.c_str(), key.length(),
                                                             (unsigned char *) iv.c_str());

    CryptoPP::StringSource encryptor(str_in, true,
                                     new CryptoPP::StreamTransformationFilter(encryption, new CryptoPP::Base64Encoder(
                                             new CryptoPP::StringSink(str_out), false)));
    return str_out;
}

std::string CryptUtils::aesDecrypt(const std::string &str_in, const std::string &key, const std::string &iv) {
    std::string str_out;
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption((unsigned char *) key.c_str(), key.length(),
                                                             (unsigned char *) iv.c_str());

    CryptoPP::StringSource decryptor(str_in, true, new CryptoPP::Base64Decoder(
            new CryptoPP::StreamTransformationFilter(decryption, new CryptoPP::StringSink(str_out))));
    return str_out;
}

