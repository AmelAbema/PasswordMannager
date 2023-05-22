#pragma once
#include <iostream>


namespace cipher {
    auto encrypt(const std::string& message, const std::uint32_t key) -> std::string;

    /**
     * @brief Decrypts a message using a key
     * @param message
     * @param key
     */

    auto dcrypt(const std::string& message, const std::uint32_t key) -> std::string;

    /**
     * @brief Encrypts a message using a key
     * @param message
     * @param key
     */
}
