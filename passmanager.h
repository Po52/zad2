#pragma once
#include <cassert>
#include <fstream>
#include <string>
#include <vector>

class PassManager {
    static std::vector<std::string> passwords;
    static std::string randPass;

public:
    /**
     * Wcztytywanie haseł do listy z pliku
     */
    static void loadPassswords() {
        std::ifstream file("dane.txt");
        setlocale(LC_CTYPE, "Polish");

        while (!file.eof()) {
            std::string s;
            getline(file, s);
            passwords.push_back(s);
        }

        file.close();
        assert(hasla.size() > 0);
        randPass = getRandomPass();
    }

    /**
     * Wybiera losowe hasło z ich listy
     */
    static const std::string& getRandomPass() {
        return passwords[std::rand() % passwords.size()];
    }

    /**
     * Zwraca wybrane na samym początku losowe hasło
     */
    static const std::string& getPassword() {
        return randPass;
    }

    /**
     * Zwraca listę z hasłami z pliku
     */
    static auto& getPasswords() {
        return passwords;
    }
};
