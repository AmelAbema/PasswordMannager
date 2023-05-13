#include <iostream>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <vector>
#include <string>
#include <ctime>

class Password;

bool isEmptyFile(std::ifstream&);
std::string encryptPassword(std::string);
std::string decryptPassword(std::string);
void search(std::vector<Password*>);
std::vector<Password *> addPassword(std::vector<Password>, std::vector<std::string>);
void deletePassword(std::vector<Password*>);
std::vector<Password *> editPassword(std::vector<Password>, std::vector<std::string>);
std::string addCategory(std::vector<std::string>);
void deleteCategory(std::vector<std::string>, std::vector<Password*>);
std::vector<Password *> sortPasswords(std::vector<Password>*);
int menu();

class Password {
private:
    std::string name;                //!< Mandatory parameter - password name
    std::string password;            //!< Mandatory parameter - password
    std::string category;            //!< Mandatory parameter - category of the password
    std::string website;             //!< Optional parameter - website for the password
    std::string username;            //!< Optional parameter - username for the password

public:
    Password() {
        this->name = "";
        this->password = "";
        this->category = "";
        this->website = "";
        this->username = "";
    }

    Password(std::string name, std::string category, std::string website, std::string username) {
        this->name = std::move(name);
        this->password = generatePassword();
        this->category = std::move(category);
        this->website = std::move(website);
        this->username = std::move(username);
    }

    Password(std::string name, std::string password, std::string category, std::string website, std::string username) {
        this->name = std::move(name);
        this->password = std::move(password);
        this->category = std::move(category);
        this->website = std::move(website);
        this->username = std::move(username);
    }

    std::string getName() {
        return this->name;
    }

    void setName(std::string s) {
        this->name = std::move(s);
    }

    std::string getPassword() {
        return this->password;
    }

    void setPassword(std::string s) {
        this->password = std::move(s);
    }

    void setRandomPassword() {
        this->password = generatePassword();
    }

    std::string getCategory() {
        return this->category;
    }

    void setCategory(std::string s) {
        this->category = std::move(s);
    }

    std::string getWebsite() {
        return this->website;
    }

    void setWebsite(std::string s) {
        this->website = std::move(s);
    }

    std::string getUsername() {
        return this->username;
    }

    void setUsername(std::string s) {
        this->username = std::move(s);
    }

    /*! \fn string generatePassword()
        \brief Generates a new password based on user preferences
    */
    static std::string generatePassword() {
        int length, n;
        std::string characters = "abcdefghijklmnopqrstuvwxyz";
        std::string password;
        srand(time(nullptr));  //random characters

        std::cout << "Enter password length: ";
        std::cin >> length;
        while (length < 6) {
            std::cout << "Password should contain at least 6 characters.\nEnter password length: ";
            std::cin >> length;
        }

        std::cout << "Can the password contain uppercase letters?\n1. Yes\n2. No\nEnter number (1|2): ";
        std::cin >> n;
        if (n == 1) {
            characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        }

        std::cout << "Can the password contain special characters?\n1. Yes\n2. No\nEnter number (1|2): ";
        std::cin >> n;
        if (n == 1) {
            characters += "?!@&#^+=-$*";
        }


        for (int i = 0; i < length; i++) {
            password += characters[rand() % characters.length()];
        }
        return password;
    }

    std::string to_string() {
        return name + "\n" + password + "\n" + category + "\n" + website + "\n" + username + "\n";
    }

    std::string toEncryptedString() {
        return encryptPassword(name) + "\n" + encryptPassword(password) + "\n" + encryptPassword(category) + "\n" +
                encryptPassword(website) + "\n" + encryptPassword(username);
    };
};

int main() {
    bool first_run;
    auto *passwords = new std::vector<Password *>();
    auto *categories = new std::vector<std::string>();
    std::string file_name, password, row;
    std::cout << "Enter file name to decrypt: ";
    std::cin >> file_name;
    std::cout << "Enter password to decrypt the file: ";
    std::cin >> password;

    std::ifstream input_file(file_name);
    if (!input_file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }

    getline(input_file, row);
    if (encryptPassword(password) != row && !isEmptyFile(input_file)) {
        std::cout << "Incorrect password." << std::endl;
        return -1;
    } else {
        while (getline(input_file, row)) {
            passwords->push_back(new Password());
            passwords->at(passwords->size() - 1)->setName(decryptPassword(row));
            getline(input_file, row);
            passwords->at(passwords->size() - 1)->setPassword(decryptPassword(row));
            getline(input_file, row);
            passwords->at(passwords->size() - 1)->setCategory(decryptPassword(row));
            categories->push_back(decryptPassword(row));
            getline(input_file, row);
            passwords->at(passwords->size() - 1)->setWebsite(decryptPassword(row));
            getline(input_file, row);
            passwords->at(passwords->size() - 1)->setUsername(decryptPassword(row));
        }
    }

    bool flag = true;
    while (flag) {
        switch (menu()) {
            case 1:
                search(*passwords);
                break;
            case 2:
                sortPasswords(passwords);
                break;
            case 3:
                addPassword(passwords, categories);
                break;
            case 4:
                editPassword(*passwords, *categories);
                break;
            case 5:
                deletePassword(*passwords);
                break;
            case 6:
                addCategory(*categories);
                break;
            case 7:
                deleteCategory(*categories, *passwords);
                break;
            case 8:
            default:
                flag = false;
                break;
        }
    }

    if (isEmptyFile(input_file)) {
        first_run = true;
    } else {
        first_run = false;
    }
    input_file.close();

    std::ofstream output_file(file_name);
    if (!output_file.is_open()) {
        std::cout << "Failed to open file." << std::endl;
        return -1;
    }

    if (first_run) {
        output_file << encryptPassword(password) << "\n";
    }

    for (auto & password : *passwords) {
        output_file << password->toEncryptedString();
    }

    output_file.close();
    return 0;
}

int menu() {
    int option;
    std::cout << "MAIN MENU" << std::endl;

    std::cout << "1. Search Password" << std::endl;
    std::cout << "2. Sort Passwords" << std::endl;
    std::cout << "3. Add New Password" << std::endl;
    std::cout << "4. Edit Password" << std::endl;
    std::cout << "5. Delete Password" << std::endl;
    std::cout << "6. Add New Category" << std::endl;
    std::cout << "7. Delete Category" << std::endl;
    std::cout << "8. Exit" << std::endl;

    std::cout << "Choose an option: ";
    std::cin >> option;
    while (option < 1 || option > 8) {
        std::cout << "Invalid option...\nChoose an option: ";
        std::cin >> option;
    }
    return option;
}

bool empty_file(std::ifstream &file) {
    return file.peek() == std::ifstream::traits_type::eof();
}

std::string encryptPassword(std::string message) {
    std::string result;
    // ABC -> A + 1  B + 2  C + 3  -> BDF
    for (int i = 0, j = 1; i < message.length(); i++, j++) {
        result += char(message[i] + j);
    }
    return result;
}

std::string decryptPassword(std::string message) {
    std::string result;
    // BDF -> B - 1  D - 2  F - 3  -> ABC
    for (int i = 0, j = 1; i < message.length(); i++, j++) {
        result += char(message[i] - j);
    }
    return result;
}

void search(const std::vector<Password *> *passwords) {
    int option;
    std::string choice;

    std::cout << std::endl;

    std::cout << "Choose what to search by:\n1. Name\n2. Category\n3. Website\n4. Username\nChoose an option: ";
    std::cin >> option;
    while (option < 1 || option > 4) {
        std::cout << "Choose what to search by:\n1. Name\n2. Category\n3. Website\n4. Username\nChoose an option: ";
        std::cin >> option;
    }
    std::cout << "Enter the value of the selected parameter: ";
    std::cin >> choice;

    for (auto password: *passwords) {
        switch (option) {
            case 1:
                if (password->getName() == choice)
                    std::cout << password->to_string();
                break;
            case 2:
                if (password->getCategory() == choice)
                    std::cout << password->to_string();
                break;
            case 3:
                if (password->getWebsite() == choice)
                    std::cout << password->to_string();
                break;
            case 4:
                if (password->getUsername() == choice)
                    std::cout << password->to_string();
                break;
            default:
                std::cout << "No such operation(";
        }
    }
}

void addPassword(std::vector<Password *> *passwords, std::vector<std::string> *categories) {
    std::string name, new_password, category, website, username;
    int choice;
    std::cout << "Enter a name for the new password: " << std::endl;
    std::cin >> name;

    std::cout << "1. Generate a random password" << std::endl;
    std::cout << "2. Enter a password manually" << std::endl;
    std::cout << "Your choice: ";
    std::cin >> choice;
    while (choice != 1 and choice != 2) {
        std::cout << "Choose an option again (1|2)\nYour choice: ";
        std::cin >> choice;
    }

    auto *password = new Password();
    password->setName(name);
    if (choice == 1) {
        password->setRandomPassword();
    } else {
        std::cout << "Enter a password: ";
        std::cin >> new_password;
        while (new_password.length() < 4) {
            std::cout << "Password is too short.\nEnter a password: ";
            std::cin >> new_password;
        }

        if (new_password.length() < 8) {
            std::cout << "Password is weak." << std::endl;
        } else if (new_password.length() < 12) {
            std::cout << "Password is medium strength." << std::endl;
        } else {
            std::cout << "Password is strong." << std::endl;
        }
        password->setPassword(new_password);
    }

    if (categories->empty()) {
        category = addCategory(*categories);
    } else {
        for (int i = 0; i < categories->size(); i++) {
            std::cout << i + 1 << ". " << categories->at(i) << std::endl;
        }
        std::cout << "Your choice: ";
        std::cin >> choice;
        while (choice < 1 || choice > categories->size()) {
            std::cout << "Choose a category [1-" << categories->size() << "]: ";
            std::cin >> choice;
        }
        category = categories->at(choice - 1);
    }
    password->setCategory(category);

    int option;
    std::cout << "Add website:\n1. Yes\n2. No\nYour choice: ";
    std::cin >> option;
    if (option == 1) {
        std::cout << "Enter website: ";
        std::cin >> website;
    } else {
        website = "";
    }
    password->setWebsite(website);

    std::cout << "Add username:\n1. Yes\n2. No\nYour choice: ";
    std::cin >> option;
    if (option == 1) {
        std::cout << "Enter username: ";
        std::cin >> username;
    } else {
        username = "";
    }
    password->setUsername(username);

    passwords->push_back(password);
}

void deletePassword(std::vector<Password *> *passwords) {
    std::string name_to_delete;
    int choice;
    std::cout << "Enter the name of the password you want to delete: ";
    std::cin >> name_to_delete;
    std::cout << "Are you sure?\n1. Yes\n2. No\nYour choice: ";
    std::cin >> choice;
    if (choice == 2) {
        return;
    }
    int size = passwords->size();
    int deleted = 0;
    for (int i = 0; i < size; i++) {
        if (passwords->at(i)->getName() == name_to_delete) {
            passwords->erase(passwords->begin() + i);
            deleted++;
            i--;
            size--;
        }

    }
    if (deleted > 1) {
        std::cout << "Passwords have been deleted." << std::endl;
    } else if (deleted == 1) {
        std::cout << "Password has been deleted." << std::endl;
    } else {
        std::cout << "There is no password with that name." << std::endl;
    }
}

void editPassword(std::vector<Password *> *passwords, std::vector<std::string> *categories) {
    std::string name;
    int choice;
    std::string new_name, new_password, new_website, new_username;
    std::cout << "Name of the password to be edited: ";
    std::cin >> name;
    for (auto & password : *passwords) {
        if (password->getName() == name) {
            std::cout
                    << "Choose what to change:\n1. Name\n2. Password\n3. Category\n4. Website\n5. Username\nYour choice: ";
            std::cin >> choice;
            while (choice < 1 || choice > 5) {
                std::cout
                        << "Choose what to change:\n1. Name\n2. Password\n3. Category\n4. Website\n5. Username\nYour choice: ";
                std::cin >> choice;
            }
            if (choice == 1) {
                std::cout << "Enter new name: ";
                std::cin >> new_name;
                password->setName(new_name);
            } else if (choice == 2) {
                std::string test_password;
                std::cout << "Enter previous password: ";
                std::cin >> test_password;
                if (test_password == password->getPassword()) {
                    std::cout << "Enter new password: ";
                    std::cin >> new_password;
                    password->setPassword(new_password);
                } else {
                    std::cout << "Incorrect password." << std::endl;
                }
            } else if (choice == 3) {
                for (int i = 0; i < categories->size(); i++) {
                    std::cout << i + 1 << ". " << categories->at(i) << std::endl;
                }
                std::cout << " > ";
                std::cin >> choice;
                while (choice < 1 || choice > categories->size()) {
                    std::cout << "Invalid option.\nChoose a category [1-" << categories->size() << "]: ";
                    std::cin >> choice;
                }
                password->setCategory(categories->at(choice - 1));
            } else if (choice == 4) {
                std::cout << "Enter new website: ";
                std::cin >> new_website;
                password->setWebsite(new_website);
            } else {
                std::cout << "Enter new username: ";
                std::cin >> new_username;
                password->setUsername(new_username);
            }
            return;
        }
    }
    std::cout << "No password found with that name." << std::endl;
}


std::string addCategory(std::vector<std::string> *categories) {
    std::string category;
    std::cout << "Enter new category: ";
    std::cin >> category;
    categories->push_back(category);
    return category;
}


void deleteCategory(std::vector<std::string *> categories, std::vector<Password *> *passwords) {
    int choice;
    for (int i = 0; i < categories.size(); i++) {
        std::cout << i + 1 << ". " << categories.at(i) << std::endl;
    }
    std::cout << "Category to delete: ";
    std::cin >> choice;
    while (choice < 1 || choice > categories.size()) {
        std::cout << "Category to delete [1-" << categories.size() << "]: ";
        std::cin >> choice;
    }

    int size = passwords->size();
    for (int i = 0; i < size; i++) {
        if ((passwords->at(i)->getCategory()) == (categories.at(choice - 1))) {
            passwords->erase(passwords->begin() + i);
            i--;
            size--;
        }
    }
    categories.erase(categories.begin() + choice - 1);
}

void sortPasswords(std::vector<Password *> *passwords) {
    for (int i = 0; i < passwords->size() - 1; i++) {
        for (int j = i + 1; j < passwords->size(); j++) {
            if (passwords->at(i)->getName() > passwords->at(j)->getName()) {
                Password *temp = passwords->at(j);
                passwords->at(j) = passwords->at(i);
                passwords->at(i) = temp;
            } else if (passwords->at(i)->getCategory() > passwords->at(j)->getCategory()) {
                Password *temp = passwords->at(j);
                passwords->at(j) = passwords->at(i);
                passwords->at(i) = temp;
            }
        }
    }
}
