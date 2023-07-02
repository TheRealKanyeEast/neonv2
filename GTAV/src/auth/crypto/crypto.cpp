#include "pch.h"
#include "crypto.h"
#include "../../includes/openssl/evp.h"
#include "../../includes/openssl/rand.h"
#include "../../includes/openssl/aes.h"

namespace auth {
    std::string crypto::aes256cbc_encrypt(std::string plaintext, unsigned char* key, unsigned char* iv)
    {
        // Allocate memory for ciphertext
        unsigned char* ciphertext = new unsigned char[plaintext.length() + AES_BLOCK_SIZE];

        // Set up the AES cipher context
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

        // Encrypt the plaintext
        int len;
        EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char*)plaintext.c_str(), plaintext.length());
        int ciphertext_len = len;

        // Finalize the encryption
        EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
        ciphertext_len += len;

        // Clean up the AES cipher context
        EVP_CIPHER_CTX_free(ctx);

        // Convert the ciphertext to a string
        std::string ciphertext_str((char*)ciphertext, ciphertext_len);

        // Deallocate memory
        delete[] ciphertext;

        // Return the ciphertext as a string
        return ciphertext_str;
    }
    std::string crypto::aes256cbc_decrypt(std::string ciphertext, unsigned char* key, unsigned char* iv)
    {
        // Allocate memory for plaintext
        unsigned char* plaintext = new unsigned char[ciphertext.length() + AES_BLOCK_SIZE];

        // Set up the AES cipher context
        EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
        EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

        // Decrypt the ciphertext
        int len;
        EVP_DecryptUpdate(ctx, plaintext, &len, (unsigned char*)ciphertext.c_str(), ciphertext.length());
        int plaintext_len = len;

        // Finalize the decryption
        EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
        plaintext_len += len;

        // Clean up the AES cipher context
        EVP_CIPHER_CTX_free(ctx);

        // Convert plaintext to string
        std::string result((char*)plaintext, plaintext_len);

        // Deallocate memory
        delete[] plaintext;

        return result;
    }

    std::string crypto::bin2hex(const std::string& input)
    {
        std::stringstream ss;
        ss << std::hex << std::setfill('0');
        for (int i = 0; i < input.length(); i++)
        {
            ss << std::setw(2) << (int)(unsigned char)input[i];
        }
        return ss.str();
    }
}