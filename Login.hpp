#pragma once
#include <iostream>

namespace login {
    auto loginIn(const std::string& filePath) -> bool;

    /**
     * @brief Used to login in the program
     * @param userPassword, kay
     * @return true if the password is correct, false if not
     */

    auto saveTime(time_t time, const std::string& filePath, const bool& isSuccess) -> void;

    /**
     * @brief Saves the time of the last login
     * @param time
     */
}
