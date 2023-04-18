#include "Gracz.h"

int Gracz::currentPlayer = 0;
int Gracz::nextId = 0;
std::unordered_map<int, Gracz> Gracz::playerList;
