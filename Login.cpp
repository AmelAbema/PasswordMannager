#include <iostream>
#include <fstream>
#include <ctime>
#include "Login.hpp"
#include "Cipher.hpp"

namespace login {
    auto loginIn(const std::string& filePath) -> bool {
        std::fstream file = std::fstream(filePath);
        std::string pass;
        file.open(filePath);
        file.clear();
        file.seekg(0, std::ios::beg);


        std::getline(file, pass);

        std::string userPassword;
        int key;

        std::cout << "Password: " << std::endl;
        std::cin >> userPassword;

        std::cout << "Key: " << std::endl;
        std::cin >> key;

        std::string globalPass;

        globalPass = cipher::dcrypt(pass, key);


        if (userPassword == globalPass) {
            std::cout << "Correct password \n" << std::endl;
            file.close();
            time_t timeNow = time(nullptr);
            login::saveTime(timeNow, filePath, true);
            return true;
        } else {
            std::cout << "Incorrect password, try again (remember you have 3 attempts) \n" << "\n";
            return false;
        }

    }

    auto saveTime(time_t time, const std::string& filePath, const bool& isSuccess) -> void {

        std::fstream loginsOut;
        loginsOut.open("..\\files\\logList.txt", std::ios::out | std::ios::app);

        char *dt = std::ctime(&time);
        loginsOut << filePath << " <--- Last login time -- " << dt << "\n";
        loginsOut.close();


    }
}


