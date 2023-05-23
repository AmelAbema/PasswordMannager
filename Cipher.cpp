#include "Cipher.hpp"
#include <ranges>


namespace cipher{
    auto encrypt(const std::string& message) -> std::string {
        std::string encryptedMessage;
        encryptedMessage.reserve(message.size());

        // ABC -> A + 1  B + 2  C + 3  -> BDF
        for (int i = 0, j = 1; i < message.length(); i++, j++) {
            encryptedMessage += char(message[i] + j);
        }

        return encryptedMessage;
    }

    auto decrypt(const std::string& message) -> std::string {
        std::string decryptedMessage;
        decryptedMessage.reserve(message.size());

        // BDF -> B - 1  D - 2  F - 3  -> ABC
        for (int i = 0, j = 1; i < message.length(); i++, j++) {
            decryptedMessage += char(message[i] - j);
        }

        return decryptedMessage;
    }
}