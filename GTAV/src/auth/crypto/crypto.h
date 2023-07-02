#pragma once
#include "pch.h"

namespace auth::crypto {
    std::string aes256cbc_encrypt(std::string plaintext, unsigned char* key, unsigned char* iv);
    std::string aes256cbc_decrypt(std::string ciphertext, unsigned char* key, unsigned char* iv);
    std::string bin2hex(const std::string& input);

}