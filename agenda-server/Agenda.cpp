// Estratto da Agenda di K. Delugan

#include "Agenda.hpp"

#include <string>
#include <fstream>

using namespace std;

bool same_day(impegno agenda1[], int pos1, bool inizio_fine1,
              impegno agenda2[], int pos2, bool inizio_fine2);
bool same_hour(impegno agenda1[], int pos1, bool inizio_fine1,
               impegno agenda2[], int pos2, bool inizio_fine2);
void show_day(impegno agenda[], int pos, bool inizio_fine, ostringstream & oss);
void show_hour(impegno agenda[], int pos, bool inizio_fine, ostringstream & oss);

enum { AGENDA_N_ELEMENTI = 32 };

impegno agenda[AGENDA_N_ELEMENTI];
const int n_elementi = AGENDA_N_ELEMENTI;

void init(impegno agenda[], int n_elementi){
    // Initialize
    for(int i=0;i<n_elementi;i++){
        agenda[i].impegnato=false;
    }
}

void load(impegno agenda[], int n_elementi){
    string stringa;
    ifstream myfile;
    myfile.open (".database.txt");
    for(int i=0;i<n_elementi;i++){
        myfile>>agenda[i].impegnato;
        if (agenda[i].impegnato==true){
            myfile>>agenda[i].nome;
            myfile>>agenda[i].giorno_inizio.dd;
            myfile>>agenda[i].giorno_inizio.mm;
            myfile>>agenda[i].giorno_inizio.aaaa;
            myfile>>agenda[i].giorno_fine.dd;
            myfile>>agenda[i].giorno_fine.mm;
            myfile>>agenda[i].giorno_fine.aaaa;
            myfile>>agenda[i].orario_inizio.h;
            myfile>>agenda[i].orario_inizio.m;
            myfile>>agenda[i].orario_fine.h;
            myfile>>agenda[i].orario_fine.m;
        }
        myfile>>stringa;
    }
    myfile.close();
}

int conta_impegni(impegno agenda[], int n_elementi){
    int conta=0;
    for(int i=0;i<n_elementi;i++){
        if (agenda[i].impegnato==true) conta++;
    }
    return conta;
}

void show(impegno agenda[], int pos, ostringstream & oss){
    oss<<agenda[pos].nome<<endl;
    if(same_day(agenda,pos,false,agenda,pos,true)){
        oss<<"Il giorno ";
        show_day(agenda,pos,false,oss);
        if(same_hour(agenda,pos,false,agenda,pos,true)){
            oss<<" alle ore ";
            show_hour(agenda,pos,false,oss);
            oss<<'.'<<endl;
        } else {
            oss<<" dalle ore ";
            show_hour(agenda,pos,false,oss);
            oss<<" alle ore ";
            show_hour(agenda,pos,true,oss);
            oss<<'.'<<endl;
        }
    } else {
        oss<<"Dal giorno ";
        show_day(agenda,pos,false,oss);
        oss<<" alle ore ";
        show_hour(agenda,pos,false,oss);
        oss<<endl<<"al giorno ";
        show_day(agenda,pos,true,oss);
        oss<<" alle ore ";
        show_hour(agenda,pos,true,oss);
        oss<<'.'<<endl;
    }
}

// TESTFOR-FUNZIONI:
bool same_day(impegno agenda1[], int pos1, bool inizio_fine1, impegno agenda2[], int pos2, bool inizio_fine2){
    bool uguali=true;
    if (inizio_fine1==false&&inizio_fine2==false){
        if (agenda1[pos1].giorno_inizio.aaaa!=agenda2[pos2].giorno_inizio.aaaa) uguali=false;
        else if (agenda1[pos1].giorno_inizio.mm!=agenda2[pos2].giorno_inizio.mm) uguali=false;
        else if (agenda1[pos1].giorno_inizio.dd!=agenda2[pos2].giorno_inizio.dd) uguali=false;
    } else if (inizio_fine1==true&&inizio_fine2==false){
        if (agenda1[pos1].giorno_fine.aaaa!=agenda2[pos2].giorno_inizio.aaaa) uguali=false;
        else if (agenda1[pos1].giorno_fine.mm!=agenda2[pos2].giorno_inizio.mm) uguali=false;
        else if (agenda1[pos1].giorno_fine.dd!=agenda2[pos2].giorno_inizio.dd) uguali=false;
    } else if (inizio_fine1==false&&inizio_fine2==true){
        if (agenda1[pos1].giorno_inizio.aaaa!=agenda2[pos2].giorno_fine.aaaa) uguali=false;
        else if (agenda1[pos1].giorno_inizio.mm!=agenda2[pos2].giorno_fine.mm) uguali=false;
        else if (agenda1[pos1].giorno_inizio.dd!=agenda2[pos2].giorno_fine.dd) uguali=false;
    } else {
        if (agenda1[pos1].giorno_fine.aaaa!=agenda2[pos2].giorno_fine.aaaa) uguali=false;
        else if (agenda1[pos1].giorno_fine.mm!=agenda2[pos2].giorno_fine.mm) uguali=false;
        else if (agenda1[pos1].giorno_fine.dd!=agenda2[pos2].giorno_fine.dd) uguali=false;
    }
    return uguali;
}

bool same_hour(impegno agenda1[], int pos1, bool inizio_fine1, impegno agenda2[], int pos2, bool inizio_fine2){
    bool uguali=true;
    if (inizio_fine1==false&&inizio_fine2==false){
        if (agenda1[pos1].orario_inizio.h!=agenda2[pos2].orario_inizio.h) uguali=false;
        else if (agenda1[pos1].orario_inizio.m!=agenda2[pos2].orario_inizio.m) uguali=false;
    } else if (inizio_fine1==true&&inizio_fine2==false){
        if (agenda1[pos1].orario_fine.h!=agenda2[pos2].orario_inizio.h) uguali=false;
        else if (agenda1[pos1].orario_fine.m!=agenda2[pos2].orario_inizio.m) uguali=false;
    } else if (inizio_fine1==false&&inizio_fine2==true){
        if (agenda1[pos1].orario_inizio.h!=agenda2[pos2].orario_fine.h) uguali=false;
        else if (agenda1[pos1].orario_inizio.m!=agenda2[pos2].orario_fine.m) uguali=false;
    } else {
        if (agenda1[pos1].orario_fine.h!=agenda2[pos2].orario_fine.h) uguali=false;
        else if (agenda1[pos1].orario_fine.m!=agenda2[pos2].orario_fine.m) uguali=false;
    }
    return uguali;
}

void show_day(impegno agenda[], int pos, bool inizio_fine, ostringstream & oss){
    if (inizio_fine==false){
        if (agenda[pos].giorno_inizio.dd>=10) oss<<agenda[pos].giorno_inizio.dd<<'/';
        else oss<<'0'<<agenda[pos].giorno_inizio.dd<<'/';
        if (agenda[pos].giorno_inizio.mm>=10) oss<<agenda[pos].giorno_inizio.mm<<'/';
        else oss<<'0'<<agenda[pos].giorno_inizio.mm<<'/';
        if (agenda[pos].giorno_inizio.aaaa>=1000) oss<<agenda[pos].giorno_inizio.aaaa;
        else if (agenda[pos].giorno_inizio.aaaa>=100) oss<<'0'<<agenda[pos].giorno_inizio.aaaa;
        else if (agenda[pos].giorno_inizio.aaaa>=10) oss<<"00"<<agenda[pos].giorno_inizio.aaaa;
        else oss<<"000"<<agenda[pos].giorno_inizio.aaaa;
    } else {
        oss<<agenda[pos].giorno_fine.dd<<'/';
        oss<<agenda[pos].giorno_fine.mm<<'/';
        oss<<agenda[pos].giorno_fine.aaaa;
    }
}

void show_hour(impegno agenda[], int pos, bool inizio_fine, ostringstream & oss){
    if (inizio_fine==false){
        if (agenda[pos].orario_inizio.h>=10) oss<<agenda[pos].orario_inizio.h<<':';
        else oss<<'0'<<agenda[pos].orario_inizio.h<<':';
        if (agenda[pos].orario_inizio.m>=10) oss<<agenda[pos].orario_inizio.m;
        else oss<<'0'<<agenda[pos].orario_inizio.m;
    } else {
        if (agenda[pos].orario_fine.h>=10) oss<<agenda[pos].orario_fine.h<<':';
        else oss<<'0'<<agenda[pos].orario_fine.h<<':';
        if (agenda[pos].orario_fine.m>=10) oss<<agenda[pos].orario_fine.m;
        else oss<<'0'<<agenda[pos].orario_fine.m;
    }
}
