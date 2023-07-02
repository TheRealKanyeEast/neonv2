#include "pch.h"
#include "socket.h"
#include "util/util.h"
#include "../hardware/hardware.h"
#include "util/log.h"
#include "security/xor.h"
namespace auth {

    std::size_t write_callback(void* contents, std::size_t size, std::size_t nmemb, void* userp) {
        ((std::string*)userp)->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string socket::send_request(std::string url, std::string username, std::string password, std::string auth_key, std::string pattern, std::string iv, std::string hwid) {
        CURL* curl = curl_easy_init();
        if (curl) {

            // Encode the values (except for iv) in the post_fields string
            std::string encoded_username = curl_easy_escape(curl, username.c_str(), username.length());
            std::string encoded_password = curl_easy_escape(curl, password.c_str(), password.length());
            std::string encoded_auth_key = curl_easy_escape(curl, auth_key.c_str(), auth_key.length());
            std::string encoded_pattern = curl_easy_escape(curl, pattern.c_str(), pattern.length());
            std::string encoded_hwid = curl_easy_escape(curl, hwid.c_str(), hwid.length());
            std::string encoded_iv = curl_easy_escape(curl, iv.c_str(), iv.length());
            // Concatenate the encoded POST parameters
            std::string post_fields = XOR("username=") + encoded_username + XOR("&password=") + encoded_password + XOR("&auth_key=") + encoded_auth_key + XOR("&pattern=") + encoded_pattern + XOR("&iv=") + encoded_iv + XOR("&hwid=") + encoded_hwid;

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

            // Set the write callback function to receive the response
            std::string response;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            CURLcode res = curl_easy_perform(curl);
            if (res != CURLE_OK) {
                LOG_ERROR(std::format("{}", curl_easy_strerror(res)).c_str());
            }
            else {
                return response;
            }

            curl_easy_cleanup(curl);
        }
        return XOR("NULL");
    }

}