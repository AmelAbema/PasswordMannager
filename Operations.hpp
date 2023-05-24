#pragma once
#include <iostream>
#include <fstream>

namespace operations {

    auto openFile() -> std::string;

    /**
     * @brief Function opens file or creates new one
     * @return filePath
     */

    auto quit() -> void;

    /**
     * @brief quit program
     */

    auto addPassword(const std::string& filePath) -> void;

    /**
    * @brief Function adds new password to file by user input or random password grenated by program
    * @param filePath Path to file
    */

    auto show(const std::string& filePath) -> void;

    /**
     * @brief Function shows all passwords in file
     * @param filePath Path to file
     *
     */

    auto editPassword(const std::string& filePath) -> void;

    /**
     * @brief Function edits password by user input
     * @param filePath Path to file
     */

    auto removePassword(const std::string& filePath) -> void;

    /**
    * @brief Function removes password from file
    * @param filePath
    */

    auto sortPasswords(const std::string& filePath) -> void;

    /**
     * @brief Function searches password by user input
     * @param filePath Path to file
     */

    auto searchPassword(const std::string& filePath) -> void;

    /**
     * @brief Function sorts passwords by category, login, email or website
     * @param filePath Path to file
     * @return Passwords sorted by category, login, email or website
     */

    auto addCategory() -> void;

    /**
     * @brief Function adds category to file
     * @param filePath Path to file
     *
     */

    auto removeCategory(const std::string& filePath) -> void;

    /**
     * @brief Function removes category from file
     * @param filePath Path to file
     *
     */

    auto generatePassword(int passwordLength, char specialSymbols, char lowercaseLetters, char uppercaseLetters, char numbers) -> std::string;

    /**
     * @brief Generates a random password
     * @param passwordLength, specialSymbols, lowercaseLetters, uppercaseLetters, numbers
     * @return password
     */

}
