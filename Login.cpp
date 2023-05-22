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
        int kay;

        std::cout << "Password: " << std::endl;
        std::cin >> userPassword;

        std::cout << "Key: " << std::endl;
        std::cin >> kay;

        std::string globalPass;

        globalPass = cipher::dcrypt(pass, kay);


        if (userPassword == globalPass) {
            std::cout << "Correct password \n" << std::endl;
            file.close();
            return true;
        } else {
            std::cout << "Incorrect password, try again (remember you have 3 attempts) \n" << std::endl;
            return false;
        }

    }

    auto saveTime(time_t time, const std::string& filePath) -> void {

        std::fstream loginsOut;
        loginsOut.open("..\\files\\logList.txt", std::ios::out | std::ios::app);

        char *dt = std::ctime(&time);
        loginsOut << filePath << " <--- Last login time -- " << dt << std::endl;
        loginsOut.close();


    }
}


