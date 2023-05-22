#include <iostream>
#include <vector>
#include <ctime>
#include <dirent.h>
#include "Operations.hpp"
#include "Login.hpp"


auto main() -> int{
    bool isLogIn = false;
    bool quit = false;
    int choiceOption;
    std::string filePath;
    int logAttempts = 0;


    while(!isLogIn){
        std::cout << " ___                                                     \n"
                     " /__)  _   _   _         _  _/   /|/|  _     _   _  _  _ \n"
                     "/     (/ _)  _)  ((/ () /  (/   /   | (/ /) (/  (/ (- /  \n"
                     "                                               _/        " << std::endl;
        filePath = operations::openFile();

        std::cout << "LOG IN" << std::endl;
        isLogIn = login::loginIn(filePath);
        logAttempts++;
        if(logAttempts > 3){
            std::cout << "You have exceeded the number of attempts" << std::endl;
            exit(0);
        }
    }


    if(isLogIn) {

        time_t timeNow = time(0);
        login::saveTime(timeNow, filePath);

        while(!quit)
        {
            std::cout << "Available operations: " << std::endl;;
            std::cout << "1: search password    7: remove category" << std::endl;
            std::cout << "2: sort passwords     8: show file" << std::endl;
            std::cout << "3: add password       9: remove file" << std::endl;
            std::cout << "4: edit password      10: help menu" << std::endl;
            std::cout << "5: remove password    11: quit program" << std::endl;
            std::cout << "6: add category \n" << std::endl;
            std::cout << "Enter operation: \n";


            std::cin >> choiceOption;


            switch(choiceOption)
            {
                case 1:
                    std::cout << "You chose 'search password'" << std::endl;
                    operations::searchPassword(filePath);
                    break;
                case 2:
                    std::cout << "You chose 'sort passwords'" << std::endl;
                    operations::sortPasswords(filePath);
                    break;
                case 3:
                    std::cout << "You chose 'add password'" << std::endl;
                    operations::addPassword(filePath);
                    break;
                case 4:
                    std::cout << "You chose 'edit password'" << std::endl;
                    operations::editPassword(filePath);
                    break;
                case 5:
                    std::cout << "You chose 'remove password'" << std::endl;
                    operations::removePassword(filePath);
                    break;
                case 6:
                    std::cout << "You chose 'add category'" << std::endl;
                    operations::addCategory();
                    break;
                case 7:
                    std::cout << "You chose 'remove category'" << std::endl;
                    operations::removeCategory(filePath);
                    break;
                case 8:
                    std::cout << "You chose 'show file'" << std::endl;
                    operations::show(filePath);
                    break;
                case 9:
                    std::cout << "You chose 'remove file'" << std::endl;
                    operations::deleteFile(filePath);
                    break;
                case 10:
                    std::cout << "You chose 'help menu'" << std::endl;
                    operations::help();
                    break;
                case 11:
                    std::cout << "You chose 'quit program'" << std::endl;
                    quit = true;
                    operations::quit();
                    break;
                default:
                    std::cout<<"Operation not recognized, try again." << std::endl;
                    break;
            }
        }
    }
}

