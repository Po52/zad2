#pragma once
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

class Gracz {
    static int nextId;
    static int currentPlayer;
    std::string imie;
    int kasa = 0;
    int portfel = 0;

public:
    static std::unordered_map<int, Gracz> playerList;

    int getKasa() {
        return this->kasa;
    }

    int getPortfel() {
        return this->portfel;
    }

    std::string& getImie() {
        return this->imie;
    }

    void setKasa(int kasa) {
        this->kasa = kasa;
    }

    void setPortfel(int portfel) {
        this->portfel = portfel;
    }

    /**
     * Wypisywanie statusu graczy
     */
    static void printPlayers() {
        std::cout << std::endl;
        for (auto& player : Gracz::playerList) {
            if (player.first == currentPlayer) {
                std::cout << "\033[1;34m";
            }
            std::cout << player.second.getImie() << "\t" << player.second.getKasa() << std::endl;
            std::cout << "\033[0m";
        }
        std::cout << std::endl;
    }

    /**
     * Zwraca gracza identyfikowanego po id
     */
    static Gracz& getPlayerById(int id) {
        return playerList.at(id);
    }

    /**
     * Zwraca gracza, którego aktualnie jest kolej
     */
    static Gracz& getCurrentPlayer() {
        return getPlayerById(currentPlayer);
    }

    /**
     * Ustawianie id nastepnego gracza
     */
    static void nextPlayer() {
        currentPlayer = (Gracz::currentPlayer + 1) % 3;
    }

    /**
     * Tworzenie nowego obiektu gracza i dodawanie go do mapy z własnym unikalnym id
     */
    static Gracz& create(const std::string& imie) {
        playerList.emplace(nextId++, imie);
    }

    explicit Gracz(const std::string& imie) : imie(imie) {
    }
};
