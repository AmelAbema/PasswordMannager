#include <iostream>
#include "Cipher.hpp"
#include <ranges>


namespace cipher{
    auto encrypt(const std::string& message, const std::uint32_t key) -> std::string {
        std::string encryptedMessage;
        encryptedMessage.reserve(message.size());

        for (auto ch : message | std::views::transform([] (char ch) { return (unsigned char)(ch); })) {
            encryptedMessage+=(ch+key);
        }
        return encryptedMessage;
    }

    auto dcrypt(const std::string& message, const std::uint32_t key) -> std::string {
        std::string decryptedMessage;
        decryptedMessage.reserve(message.size());

        for (auto ch : message | std::views::transform([] (char ch) { return (unsigned char)(ch); })) {
            decryptedMessage+=(ch-key);
        }
        return decryptedMessage;
    }
}