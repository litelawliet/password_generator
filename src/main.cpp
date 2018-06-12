/**
*   @file
*   @brief Main file
*/
#include <iostream>
#include <cstdlib>
#include <string>
#include <random>
#include <vector>
#include <limits>

void usage(const char* programName);
std::string generate_password(const std::string MODEL, const int length);
void show_passwords(const std::vector<std::string> list);

int main(int argc, char** argv) {
    
    const std::string CHARACTERS_MODEL = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,?;.:/!*=}+])\\_|-[({'#\"&";

    std::string password = "";
    std::vector<std::string> listOfPassword;
    int nbPassword(0), sizePassword(0);
    
    if(argc == 3) {
        nbPassword = atoi(argv[1]);
        sizePassword = atoi(argv[2]);
    }
    else if (argc == 2) {
        nbPassword = atoi(argv[1]);
        std::cout << "Password size ? ";
        std::cin >> sizePassword;
    }
    else if(argc == 1) {
        std::cout << "How many passwords would you like to generate ? ";
        std::cin >> nbPassword;
        std::cout << "Password size ? ";
        std::cin >> sizePassword;
    }
    else {
        usage(argv[0]);
    }

    // Add the passwords
    for(int i = 0; i < nbPassword; i++) {
        listOfPassword.push_back(generate_password(CHARACTERS_MODEL, sizePassword));
    }

    // Show the passwords
    show_passwords(listOfPassword);

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getchar();

    return EXIT_SUCCESS;
}

/**
* @brief Program usage.
*
* @param[in] programName Name of the program.
*
* @author Thibaut PONCHON
* @version 1.1
* @date 2018 June 12
*/
void usage(const char* programName) {
    std::cout << "\nUsage: " << programName << " <number_of_password> <size_of_a_password>\n";
    getchar();
    exit(0);
}

/**
* @brief Generate a password based on a model with a given size.
*
* @param[in] MODEL The list of usable characters.
* @param[in] length The size of the password.
*
* @return The generated password.
*
* @author Thibaut PONCHON
* @version 1.1
* @date 2018 June 12
*/
std::string generate_password(const std::string MODEL, const int length ) {
    std::string password = "";

    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, MODEL.size());

    for(int i = 0; i < length; i++) {
        password += MODEL[dist(rd)];
    }

    return password;
}


/**
* @brief Show the list of passwords.
*
* @param[in] list The list of passwords.
*
* @author Thibaut PONCHON
* @version 1.1
* @date 2018 June 12
*/
void show_passwords(const std::vector<std::string> list) {
    for(auto it : list) {
        std::cout << "\n" << it;
    }
    std::cout << "\n";
}
