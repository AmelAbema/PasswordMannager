#include <iostream>
#include <ctime>
#include "Operations.hpp"
#include "Login.hpp"


auto main() -> int {
    bool isLogIn = false;
    bool quit = false;
    int choiceOption;
    std::string filePath;
    int logAttempts = 0;


    while (!isLogIn) {
        filePath = operations::openFile();

        std::cout << "LOG IN" << "\n";
        isLogIn = login::loginIn(filePath);
        logAttempts++;

        time_t timeNow = time(nullptr);

        if (isLogIn)
            login::saveTime(timeNow, filePath, true);
        else
            login::saveTime(timeNow, filePath, false);

        if (logAttempts > 3) {
            std::cout << "You have exceeded the number of attempts" << "\n";
            exit(0);
        }
    }

    while (!quit) {
        std::cout << "Available operations: " << "\n";
        std::cout << "1: search password    7: remove category" << "\n";
        std::cout << "2: sort passwords     8: show file" << "\n";
        std::cout << "3: add password       9: remove file" << "\n";
        std::cout << "4: edit password      10: quit program" << "\n";
        std::cout << "5: remove password" << "\n";
        std::cout << "6: add category \n" << "\n";
        std::cout << "Enter operation: \n";


        std::cin >> choiceOption;


        switch (choiceOption) {
            case 1:
                std::cout << "You chose 'search password'" << "\n";
                operations::searchPassword(filePath);
                break;
            case 2:
                std::cout << "You chose 'sort passwords'" << "\n";
                operations::sortPasswords(filePath);
                break;
            case 3:
                std::cout << "You chose 'add password'" << "\n";
                operations::addPassword(filePath);
                break;
            case 4:
                std::cout << "You chose 'edit password'" << "\n";
                operations::editPassword(filePath);
                break;
            case 5:
                std::cout << "You chose 'remove password'" << "\n";
                operations::removePassword(filePath);
                break;
            case 6:
                std::cout << "You chose 'add category'" << "\n";
                operations::addCategory();
                break;
            case 7:
                std::cout << "You chose 'remove category'" << "\n";
                operations::removeCategory(filePath);
                break;
            case 8:
                std::cout << "You chose 'show file'" << "\n";
                operations::show(filePath);
                break;
            case 9:
                std::cout << "You chose 'remove file'" << "\n";
                operations::deleteFile(filePath);
                break;
            case 10:
                std::cout << "You chose 'quit program'" << "\n";
                quit = true;
                operations::quit();
                break;
            default:
                std::cout << "Operation not recognized, try again." << "\n";
                break;
        }
    }
}

