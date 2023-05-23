#pragma once
#include <iostream>


namespace cipher {
    auto encrypt(const std::string& message) -> std::string;

    /**
     * @brief Decrypts a message using a key
     * @param message
     */

    auto decrypt(const std::string& message) -> std::string;

    /**
     * @brief Encrypts a message using a key
     * @param message
     */
}
