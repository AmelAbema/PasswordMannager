#include <iostream>
#include <fstream>
#include <ctime>
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
        int key;

        std::cout << "Password: " << "\n";
        std::cin >> userPassword;

        std::cout << "Key: " << "\n";
        std::cin >> key;

        std::string globalPass;

        globalPass = cipher::dcrypt(pass, key);


        if (userPassword == globalPass) {
            std::cout << "Correct password \n";
            file.close();
            return true;
        } else {
            std::cout << "Incorrect password, try again (remember you have 3 attempts) \n";
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


