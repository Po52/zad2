// Kolory.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
#include <cctype>
#include <thread>

#include "Gracz.h"
#include "PassManager.h"

int Kolo[] = {-1, 0, 100, 200, 100, 200, 100, 200, 500, 500, 1000, 1000, 1500, 2000, 3000, 5000};
// -1 bankrut
// 0 strata kolejki

std::string proba;
char literka;
int i;
int maska[100];
int suma = 0;
int zgadl = 0;
int sa_spolgloski = 0;
int kwota = 0;
std::string rezultat;

int jestSamogloska(char c) {
    c = std::tolower(c);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y')
        return 1;
    return 0;
}

char WczytajZnak() {
    std::string letter;
    std::cin >> letter;

    while (letter.length() != 1) {
        std::cout << std::endl << "Type a single letter and press <enter>: ";
        std::cin >> letter;
    }

    for (auto& c : letter) // & zapamietuje modyfikacje w petli & - referencja
        c = toupper(c);

    return letter[0];
}

char WczytajWybor() {
    char wybor;
    wybor = WczytajZnak();

    while (wybor != '1' && wybor != '2') {
        std::cout << std::endl << "Wybierz [1-2]: ";
        std::cin >> wybor;
    }

    return wybor;
}

/**
 * Tworzenie nowych graczy
 **/
void initPlayers() {
    Gracz::create("Bryanusz");
    Gracz::create("Jessica ");
    Gracz::create("Nepomucen");
}

void firstChoice() {
    std::cout << "Podaj haslo" << std::endl;
    getline(std::cin >> std::ws, proba); // wczytanie z klawiatury string z uwzgl. whitespa
    for (auto& c : proba) // & zapamietuje modyfikacje w petli & - referencja
        c = toupper(c);
    if (PassManager::getPassword() == proba) {
        Gracz& player = Gracz::getCurrentPlayer();
        std::cout << std::endl << "!!!!!!!!!!!!! ======== WYGRANA ======== !!!!!!!!!!!!!" << std::endl;
        player.setPortfel(player.getPortfel() + player.getKasa());
        return;
    }
    Gracz::nextPlayer();
    suma = 1;
    std::cout << std::endl << "!!!!!!!!!!!!! ========== ZLE ========== !!!!!!!!!!!!!" << std::endl;
    std::cout << std::endl << "=================================================" << std::endl;
}

void secondChoice() {
    rezultat = "";
    i = rand() % 15;
    if (Kolo[i] == 0)
        rezultat = "Strata kolejki";
    if (Kolo[i] == -1)
        rezultat = "Bankrut";
    if (rezultat != "")
        std::cout << "\033[1;31m" << rezultat << "\033[0m" << std::endl;
    else {
        std::cout << "\033[1;34m" << Kolo[i] << "\033[0m" << std::endl;
        kwota = Kolo[i];
    }

    // Strata kolejki i bankrut
    if ((Kolo[i] == 0) || (Kolo[i] == -1)) {
        if (Kolo[i] == -1) // bankrut
            Gracz::getCurrentPlayer().setKasa(0);

        Gracz::nextPlayer();
        suma = 1;
        std::cout << std::endl << "=================================================" << std::endl;

        // TODO
        // sleep for
        // kupowanie samoglosek

        return;
    }

    std::cout << Gracz::getCurrentPlayer().getImie() << ": Podaj litere" << std::endl;
    literka = WczytajZnak();
    zgadl = 0;

    if (jestSamogloska(literka))
        std::cout << "samogloska";
    else
        std::cout << "spolgloska";
    std::cout << std::endl;

    for (i = 0; i < PassManager::getPassword().size(); i++) {
        if ((PassManager::getPassword()[i] == literka) && (maska[i] == 1)) {
            maska[i] = 0;
            zgadl++;
        }
    }

    if (zgadl) {
        std::cout << "OK";
        Gracz::getCurrentPlayer().setKasa(kwota * zgadl);

        std::cout << std::endl << Gracz::getCurrentPlayer().getImie() << "\033[1;32m " << Gracz::getCurrentPlayer()
            .getKasa() << "\033[0m";
    }
    else {
        std::cout << "Zle!";
        // strata kolejki
        Gracz::nextPlayer();
        std::cout << std::endl << "=================================================" << std::endl;
        suma = 1;
        return;
    }

    std::cout << std::endl;
    suma = 0;

    for (i = 0; i < PassManager::getPassword().size(); i++) {
        suma += maska[i];
    }
}

/**
 * Menu wyboru opcji
 **/
char menu() {
    system("cls");
    std::cout << "\033[47m" << "\033[31m";
    for (i = 0; i < PassManager::getPassword().size(); i++) {
        if (maska[i] == 1)
            std::cout << ".";
        else
            std::cout << PassManager::getPassword()[i];
    }

    std::cout << "\033[0m" << std::endl;

    sa_spolgloski = 0;
    kwota = 0;

    for (i = 0; i < PassManager::getPassword().size(); i++)
        if ((!jestSamogloska(PassManager::getPassword()[i])) && (maska[i])) {
            sa_spolgloski = 1;
            break;
        }

    if (sa_spolgloski)
        std::cout << " -- Spolgloski sa --" << std::endl;

    Gracz::printPlayers();

    std::cout << "1. zgaduj haslo" << std::endl;
    std::cout << "2. krecenie kolem" << std::endl;

    return WczytajWybor();
}

int main() {
    srand(time(NULL));

    // Ładowanie haseł z pliku
    PassManager::loadPassswords();
    for (std::string item : PassManager::getPasswords())
        std::cout << item << std::endl;
    std::cout << std::endl << std::endl;

    initPlayers();

    for (i = 0; i < PassManager::getPassword().size(); i++) {
        if (PassManager::getPassword()[i] == ' ')
            maska[i] = 0;
        else
            maska[i] = 1;
    }

    do {
        char wybor = menu();

        if (wybor == '1')
            firstChoice();
        else if (wybor == '2')
            secondChoice();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2s);
    }
    while (suma);
    std::cout << "BRAWO!";
    std::cin.get();
    return 0;
    //
    // textPlayers();
    // Beep(523, 500);
}
