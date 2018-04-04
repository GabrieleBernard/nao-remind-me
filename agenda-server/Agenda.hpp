// Estratto da Agenda di K. Delugan

#pragma once

#include <sstream>

// STRUTTURE:
struct orario{
    int h;
    int m;
};
struct giorno{
    int dd;
    int mm;
    int aaaa;
};
struct impegno{
    bool impegnato;
    giorno giorno_inizio;
    giorno giorno_fine;
    orario orario_inizio;
    orario orario_fine;
    std::string nome;
};

extern impegno agenda[32];
extern const int n_elementi;

void init(impegno agenda[], int n_elementi);
void load(impegno agenda[], int n_elementi);
int conta_impegni(impegno agenda[], int n_elementi);
void show(impegno agenda[], int pos, std::ostringstream & oss);
