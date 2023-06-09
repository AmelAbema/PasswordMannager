#include <iostream>
#include <fstream>
#include <ctime>
#include <fmt/ranges.h>
#include "Login.hpp"
#include "Cipher.hpp"

namespace login {
    auto loginIn(const std::string &filePath) -> bool {
        std::fstream file = std::fstream(filePath);
        std::string pass;
        file.open(filePath);
        file.clear();
        file.seekg(0, std::ios::beg);


        std::getline(file, pass);

        std::string userPassword;

        fmt::print("Password: \n");
        std::cin >> userPassword;

        std::string globalPass;

        globalPass = cipher::decrypt(pass);


        if (userPassword == globalPass) {
            fmt::print("Correct password \n");
            file.close();
            return true;
        } else {
            fmt::print("Incorrect password, try again (remember you have 3 attempts) \n");
            return false;
        }

    }

    auto saveTime(time_t time, const std::string &filePath, const bool &isSuccess) -> void {

        std::fstream loginsOut;
        loginsOut.open("..\\files\\logList.txt", std::ios::out | std::ios::app);

        char *dt = std::ctime(&time);

        if (isSuccess) {
            loginsOut << filePath << " <--- SUCCESSFUL login time -- " << dt << "\n";
        } else {
            loginsOut << filePath << " <--- NOT SUCCESSFUL login time -- " << dt << "\n";
        }
        loginsOut.close();
    }
}


