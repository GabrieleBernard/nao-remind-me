// TESTATO SU WINDOWS 10
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
    string nome;
};

// SAVE FUNCTION
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
void save(impegno agenda[], int n_elementi){
    ofstream myfile;
    myfile.open (".database.txt");
    for(int i=0;i<n_elementi;i++){
        myfile<<agenda[i].impegnato<<"\n";
        if (agenda[i].impegnato){
            myfile<<agenda[i].nome<<"\n";
            myfile<<agenda[i].giorno_inizio.dd<<"\n";
            myfile<<agenda[i].giorno_inizio.mm<<"\n";
            myfile<<agenda[i].giorno_inizio.aaaa<<"\n";
            myfile<<agenda[i].giorno_fine.dd<<"\n";
            myfile<<agenda[i].giorno_fine.mm<<"\n";
            myfile<<agenda[i].giorno_fine.aaaa<<"\n";
            myfile<<agenda[i].orario_inizio.h<<"\n";
            myfile<<agenda[i].orario_inizio.m<<"\n";
            myfile<<agenda[i].orario_fine.h<<"\n";
            myfile<<agenda[i].orario_fine.m<<"\n";
        }
        myfile<<"---\n";
    }
    myfile.close();
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
int conta_impegni(impegno agenda[], int n_elementi){
    int conta=0;
    for(int i=0;i<n_elementi;i++){
        if (agenda[i].impegnato==true) conta++;
    }
    return conta;
}
bool bisestile(unsigned short aaaa){
    return (!(aaaa%4)&&(aaaa%100)||!(aaaa%400));
}
bool date_validator(unsigned short anno, unsigned short mese, unsigned short giorno){
	unsigned short mesi[]={31,28,31,30,31,30,31,31,30,31,30,31};
	if (mese==0||giorno==0||mese>12)
		return false;
	if (bisestile(anno)&&mese==2)
		mesi[1]++;
	if (giorno>mesi[mese-1])
		return false;
	return true;
}
bool day_validator(impegno agenda[], int pos, bool inizio_fine){
    bool valido=true;
    if (inizio_fine==false) return date_validator((unsigned short)agenda[pos].giorno_inizio.aaaa,(unsigned short)agenda[pos].giorno_inizio.mm,(unsigned short)agenda[pos].giorno_inizio.dd);
    return date_validator((unsigned short)agenda[pos].giorno_fine.aaaa,(unsigned short)agenda[pos].giorno_fine.mm,(unsigned short)agenda[pos].giorno_fine.dd);
}
bool time_validator(unsigned short ora, unsigned short minuto){
    if (ora>23||minuto>59) return false;
    return true;
}
bool hour_validator(impegno agenda[], int pos, bool inizio_fine){
    if (inizio_fine==false) return time_validator((unsigned short)agenda[pos].orario_inizio.h,(unsigned short)agenda[pos].orario_inizio.m);
    return time_validator((unsigned short)agenda[pos].orario_fine.h,(unsigned short)agenda[pos].orario_fine.m);
}
bool need_swap (impegno agenda[], int pos, bool giorno_orario){
    bool need_swap=false;
    if (giorno_orario=false){
        if (agenda[pos].giorno_fine.aaaa<agenda[pos].giorno_inizio.aaaa) need_swap=true;
        else if (agenda[pos].giorno_fine.aaaa==agenda[pos].giorno_inizio.aaaa) {
            if (agenda[pos].giorno_fine.mm<agenda[pos].giorno_inizio.mm) need_swap=true;
            else if (agenda[pos].giorno_fine.mm==agenda[pos].giorno_inizio.mm) {
                if (agenda[pos].giorno_fine.dd<agenda[pos].giorno_inizio.dd) need_swap=true;
            }
        }
    } else {
        if (agenda[pos].orario_fine.h<agenda[pos].orario_inizio.h) need_swap=true;
        else if (agenda[pos].orario_fine.h==agenda[pos].orario_inizio.h) {
            if (agenda[pos].orario_fine.m<agenda[pos].orario_inizio.m) need_swap=true;
        }
    }
    return need_swap;
}
bool compreso(impegno agenda[], int pos, giorno cerca){
    if (agenda[pos].giorno_inizio.aaaa>cerca.aaaa) return false;
    else if (agenda[pos].giorno_inizio.aaaa==cerca.aaaa) {
        if (agenda[pos].giorno_inizio.mm>cerca.mm) return false;
        else if (agenda[pos].giorno_inizio.mm==cerca.mm) {
            if (agenda[pos].giorno_inizio.dd>cerca.dd) return false;
        }
    }
    if (agenda[pos].giorno_fine.aaaa<cerca.aaaa) return false;
    else if (agenda[pos].giorno_fine.aaaa==cerca.aaaa) {
        if (agenda[pos].giorno_fine.mm<cerca.mm) return false;
        else if (agenda[pos].giorno_fine.mm==cerca.mm) {
            if (agenda[pos].giorno_fine.dd<cerca.dd) return false;
        }
    }
    return true;
}

// FUNZIONI:
void change_color(unsigned short color){
	/* TODO: Windows only
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut,color);
	*/
}
void header(){
    change_color(7);
    cout<<"  Agenda di K. Delugan"<<endl<<endl;
    change_color(15);
}
void menu(){
    change_color(14);
    cout<<"Che azione vuoi esegure?"<<endl;
    change_color(15);
    cout<<" L -> Lista di tutti gli impegni"<<endl;
    cout<<" A -> Aggiungi un impegno"<<endl;
    cout<<" D -> Rimuovi un impegno"<<endl;
    cout<<" S -> Cerca un impegno"<<endl;
    cout<<" E -> Esci dall'agenda"<<endl<<endl;
}
void swap_giorno(impegno agenda[], int pos, bool giorno_orario){
    if (need_swap(agenda,pos,giorno_orario)==true){
        if (giorno_orario==false){
            giorno sw=agenda[pos].giorno_inizio;
            agenda[pos].giorno_inizio=agenda[pos].giorno_fine;
            agenda[pos].giorno_fine=sw;
            orario swp=agenda[pos].orario_inizio;
            agenda[pos].orario_inizio=agenda[pos].orario_fine;
            agenda[pos].orario_fine=swp;
        } else {
            orario sw=agenda[pos].orario_inizio;
            agenda[pos].orario_inizio=agenda[pos].orario_fine;
            agenda[pos].orario_fine=sw;
        }
    }
}
void show_day(impegno agenda[], int pos, bool inizio_fine){
    if (inizio_fine==false){
        if (agenda[pos].giorno_inizio.dd>=10) cout<<agenda[pos].giorno_inizio.dd<<'/';
        else cout<<'0'<<agenda[pos].giorno_inizio.dd<<'/';
        if (agenda[pos].giorno_inizio.mm>=10) cout<<agenda[pos].giorno_inizio.mm<<'/';
        else cout<<'0'<<agenda[pos].giorno_inizio.mm<<'/';
        if (agenda[pos].giorno_inizio.aaaa>=1000) cout<<agenda[pos].giorno_inizio.aaaa;
        else if (agenda[pos].giorno_inizio.aaaa>=100) cout<<'0'<<agenda[pos].giorno_inizio.aaaa;
        else if (agenda[pos].giorno_inizio.aaaa>=10) cout<<"00"<<agenda[pos].giorno_inizio.aaaa;
        else cout<<"000"<<agenda[pos].giorno_inizio.aaaa;
    } else {
        cout<<agenda[pos].giorno_fine.dd<<'/';
        cout<<agenda[pos].giorno_fine.mm<<'/';
        cout<<agenda[pos].giorno_fine.aaaa;
    }
}
void show_hour(impegno agenda[], int pos, bool inizio_fine){
    if (inizio_fine==false){
        if (agenda[pos].orario_inizio.h>=10) cout<<agenda[pos].orario_inizio.h<<':';
        else cout<<'0'<<agenda[pos].orario_inizio.h<<':';
        if (agenda[pos].orario_inizio.m>=10) cout<<agenda[pos].orario_inizio.m;
        else cout<<'0'<<agenda[pos].orario_inizio.m;
    } else {
        if (agenda[pos].orario_fine.h>=10) cout<<agenda[pos].orario_fine.h<<':';
        else cout<<'0'<<agenda[pos].orario_fine.h<<':';
        if (agenda[pos].orario_fine.m>=10) cout<<agenda[pos].orario_fine.m;
        else cout<<'0'<<agenda[pos].orario_fine.m;
    }
}
void show(impegno agenda[], int pos){
    cout<<agenda[pos].nome<<endl;
    if(same_day(agenda,pos,false,agenda,pos,true)){
        cout<<"Il giorno ";
        show_day(agenda,pos,false);
        if(same_hour(agenda,pos,false,agenda,pos,true)){
            cout<<" alle ore ";
            show_hour(agenda,pos,false);
            cout<<'.'<<endl;
        } else {
            cout<<" dalle ore ";
            show_hour(agenda,pos,false);
            cout<<" alle ore ";
            show_hour(agenda,pos,true);
            cout<<'.'<<endl;
        }
    } else {
        cout<<"Dal giorno ";
        show_day(agenda,pos,false);
        cout<<" alle ore ";
        show_hour(agenda,pos,false);
        cout<<endl<<"al giorno ";
        show_day(agenda,pos,true);
        cout<<" alle ore ";
        show_hour(agenda,pos,true);
        cout<<'.'<<endl;
    }
}
void add_impegno(impegno agenda[],int n_elementi){
    bool coincide=false;
    for(int i=0;i<n_elementi;i++){
        if(agenda[i].impegnato==false){
            cout<<"Immetti il nome dell'impegno. (Una parola)"<<endl;
            cin>>agenda[i].nome;
            do {
                cout<<endl<<"Immetti il giorno di inizio. (DD MM AAAA)"<<endl;
                cin>>agenda[i].giorno_inizio.dd>>agenda[i].giorno_inizio.mm>>agenda[i].giorno_inizio.aaaa;
                change_color(12);
                if (day_validator(agenda,i,false)==false) cout<<endl<<"La data inserita non e' valida."<<endl;
                change_color(15);
            } while (day_validator(agenda,i,false)==false);
            do {
                cout<<endl<<"Immetti l'orario di inizio. (HH MM)"<<endl;
                cin>>agenda[i].orario_inizio.h>>agenda[i].orario_inizio.m;
                change_color(12);
                if (hour_validator(agenda,i,false)==false) cout<<endl<<"L'orario inserito non e' valido."<<endl;
                change_color(15);
            } while (hour_validator(agenda,i,false)==false);
            cout<<endl<<endl<<"Il giorno di inizio coincide con quello di fine? (1|0)"<<endl;
            cin>>coincide;
            if(coincide==false){
                do {
                    cout<<endl<<endl<<"Immetti il giorno di fine. (DD MM AAAA)"<<endl;
                    cin>>agenda[i].giorno_fine.dd>>agenda[i].giorno_fine.mm>>agenda[i].giorno_fine.aaaa;
                    change_color(12);
                    if (day_validator(agenda,i,true)==false) cout<<endl<<"La data inserita non e' valida."<<endl;
                    change_color(15);
                } while (day_validator(agenda,i,true)==false);
                do {
                    cout<<endl<<"Immetti l'orario di fine. (HH MM)"<<endl;
                    cin>>agenda[i].orario_fine.h>>agenda[i].orario_fine.m;
                    change_color(12);
                    if (hour_validator(agenda,i,true)==false) cout<<endl<<"L'orario inserito non e' valido."<<endl;
                    change_color(15);
                } while (hour_validator(agenda,i,true)==false);
            } else {
                agenda[i].giorno_fine.dd=agenda[i].giorno_inizio.dd;
                agenda[i].giorno_fine.mm=agenda[i].giorno_inizio.mm;
                agenda[i].giorno_fine.aaaa=agenda[i].giorno_inizio.aaaa;

                cout<<endl<<"I'orario di inizio coincide con quello di fine? (1|0)"<<endl;
                cin>>coincide;
                if(coincide==false){
                    do {
                        cout<<endl<<"Immetti l'orario di fine. (HH MM)"<<endl;
                        cin>>agenda[i].orario_fine.h>>agenda[i].orario_fine.m;
                        change_color(12);
                        if (hour_validator(agenda,i,true)==false) cout<<endl<<"L'orario inserito non e' valido."<<endl;
                        change_color(15);
                    } while (hour_validator(agenda,i,true)==false);
                    swap_giorno(agenda,i,true);
                } else {
                    agenda[i].orario_fine.m=agenda[i].orario_inizio.m;
                    agenda[i].orario_fine.h=agenda[i].orario_inizio.h;
                }
            }
            swap_giorno(agenda,i,false);
            agenda[i].impegnato=true;

            system("cls");
            header();
            change_color(14);
            cout<<"AGGIUNGI UN IMPEGNO:"<<endl<<endl;
            change_color(15);
            show(agenda,i);
            change_color(10);
            cout<<endl<<"Impegno aggiunto."<<endl<<endl;
            change_color(15);
            break;
        }
    }
}

void delete_impegno(impegno agenda[],int n_elementi){
    int intvar;
    bool done=false;
    do {
        system("cls");
        header();
        change_color(14);
        cout<<"RIMUOVI UN IMPEGNO:"<<endl<<endl;
        change_color(15);
        for(int i=0;i<n_elementi;i++){
            if(agenda[i].impegnato==true) {
                cout<<i+1<<") ";
                show(agenda,i);
                cout<<endl;
            }
        }
        cout<<endl<<"Quale impegno vuoi rimuovere? (N)"<<endl;
        cin>>intvar;
        if (agenda[intvar-1].impegnato==true) {
            cout<<"Sei sicuro di voler rimuovere l'impegno \""<<agenda[intvar-1].nome<<"\"? (1|0)"<<endl;
            cin>>done;
        } else {
            change_color(12);
            cout<<"L'impegno numero "<<intvar<<" non e' stato trovato."<<endl;
            change_color(15);
        }
    } while (done==false);
    system("cls");
    header();
    change_color(14);
    cout<<"RIMUOVI UN IMPEGNO:"<<endl<<endl;
    change_color(15);
    agenda[intvar-1].impegnato=false;
    change_color(10);
    cout<<"L'impegno \""<<agenda[intvar-1].nome<<"\" e' stato rimosso con successo."<<endl<<endl;
    change_color(15);
}
void cerca_impegno(impegno agenda[],int n_elementi){// DA FINIRE!
    string ricerca;
    bool trovato=false;
    giorno cerca;
    system("cls");
    header();
    change_color(14);
    cout<<"CERCA UN IMPEGNO:"<<endl<<endl;
    change_color(15);
    cout<<"In base a cosa vuoi cercare? (NOME|DATA)"<<endl;
    cin>>ricerca;
    if(ricerca=="NOME"){
        cout<<"Immetti il nome dell'impegno che vuoi cercare. (Una parola)"<<endl;
        cin>>ricerca;
        for(int i=0;i<n_elementi;i++){
            if(agenda[i].impegnato==true&&agenda[i].nome==ricerca) {
                trovato=true;
            }
        }
        if (trovato=true) {
            change_color(14);
            cout<<endl<<"Risultati trovati:"<<endl<<endl;
            change_color(15);
            for(int i=0;i<n_elementi;i++){
                if(agenda[i].impegnato==true&&agenda[i].nome==ricerca) {
                    show(agenda,i);
                    cout<<endl;
                }
            }
        }
    } else if(ricerca=="DATA"){
        cout<<"Immetti la data dell'impegno che vuoi cercare. (DD MM AAAA)"<<endl;
        cin>>cerca.dd>>cerca.mm>>cerca.aaaa;
        for(int i=0;i<n_elementi;i++){
            if(agenda[i].impegnato==true&&compreso(agenda,i,cerca)==true) {
                trovato=true;
            }
        }
        if (trovato=true) {
            change_color(14);
            cout<<endl<<"Risultati trovati:"<<endl<<endl;
            change_color(15);
            for(int i=0;i<n_elementi;i++){
                if(agenda[i].impegnato==true&&compreso(agenda,i,cerca)==true) {
                    show(agenda,i);
                    cout<<endl;
                }
            }
        }
    }
    if (trovato==false){
            change_color(12);
            cout<<endl<<"Non e' stata trovata nessuna corrispondenza."<<endl<<endl;
            change_color(15);
        }
}

// MAIN
int main(){
    // Add Score
    impegno agenda[32];
    char azione;
    const int n_elementi=32;
    bool exit;

    // Initialize
    for(int i=0;i<n_elementi;i++){
        agenda[i].impegnato=false;
    }
    load(agenda,n_elementi);

    // Basic Loop
    do {
        header();
        menu();
        cin>>azione;
        system("cls");
        header();

        if(azione=='L'){ // LIST
            change_color(14);
            cout<<"LISTA DEGLI IMPEGNI:"<<endl<<endl;
            change_color(15);
            if (conta_impegni(agenda,n_elementi)==0){
                change_color(12);
                cout<<"Non ci sono impegni in agenda."<<endl<<endl;
                change_color(15);
            } else {
                for(int i=0;i<n_elementi;i++){
                    if(agenda[i].impegnato==true) {
                        show(agenda,i);
                        cout<<endl;
                    }
                }
            }
            system("pause");
        } else if(azione=='A'){ // ADD
            change_color(14);
            cout<<"AGGIUNGI UN IMPEGNO:"<<endl<<endl;
            change_color(15);
            if (conta_impegni(agenda,n_elementi)==n_elementi) {
                change_color(12);
                cout<<"Hai raggiunto il numero massimo di impegni."<<endl<<endl;
                change_color(15);
            } else {
                add_impegno(agenda,n_elementi);
            }
            system("pause");
        } else if(azione=='D'){ // DELETE
            change_color(14);
            cout<<"RIMUOVI UN IMPEGNO:"<<endl<<endl;
            change_color(15);
            if (conta_impegni(agenda,n_elementi)==0){
                change_color(12);
                cout<<"Non ci sono impegni in agenda."<<endl<<endl;
                change_color(15);
            } else {
                delete_impegno(agenda,n_elementi);
            }
            system("pause");
        } else if(azione=='S') { // SEARCH
            change_color(14);
            cout<<"CERCA UN IMPEGNO:"<<endl<<endl;
            change_color(15);
            if (conta_impegni(agenda,n_elementi)==0){
                change_color(12);
                cout<<"Non ci sono impegni in agenda."<<endl<<endl;
                change_color(15);
            } else {
                cerca_impegno(agenda,n_elementi);
            }
            system("pause");
        } else if(azione=='E'){ // END
            change_color(14);
            cout<<"ESCI DALL'AGENDA:"<<endl<<endl;
            change_color(15);
            cout<<"Sei sicuro di voler uscire? (0|1)"<<endl;
            cin>>exit;
            if (exit==0) {
                azione='0';
                cout<<endl<<"Uscita annullata."<<endl;
            }
        }
        system("cls");
    } while(azione!='E');
    save(agenda,n_elementi);
    return 0;
}


