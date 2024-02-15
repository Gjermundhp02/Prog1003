#include <string>
#include <iostream>
#include "../LesData2.h"
using namespace std;

void skrivMeny();

class Dyr{
    private:
        string navn;
    public:
        Dyr(){
            lesData();
        };
        Dyr(string navn){
            this->navn = navn;
        };
        void lesData(){
            cout << "Navn: ";
            getline(cin, navn);
        };
        void skrivData(){
            cout << "Navn: " << navn << '\n';
        };
};

class DyrIVann : public Dyr{
    private:
        string vekt;
    public:
        DyrIVann(){
            lesData();
        };
        DyrIVann(string navn) : Dyr(navn){
            lesData();
        };
        void lesData(){
            cout << "Vekt: ";
            getline(cin, vekt);
        };
        void skrivData(){
            Dyr::skrivData();
            cout << "Vekt: " << vekt << '\n';
        };
};

class Fisk : public DyrIVann{
    private:
        string farge;
    public:
        Fisk(){
            lesData();
        };
        Fisk(string navn) : DyrIVann(navn){
            lesData();
        };
        void lesData(){
            cout << "Farge: ";
            getline(cin, farge);
        };
        void skrivData(){
            cout << "Fisk:\n";
            DyrIVann::skrivData();
            cout << "Farge: " << farge << '\n';
        };
};

class Skalldyr : public DyrIVann{
    private:
        string område;
    public:
        Skalldyr(){
            lesData();
        };
        void lesData(){
            cout << "Område: ";
            getline(cin, område);
        };
        void skrivData(){
            cout << "Skalldyr:\n";
            DyrIVann::skrivData();
            cout << "Område" << område << '\n';
        };
};

class DyrILuft : public Dyr{
    private:
        bool migrerer;
    public:
        DyrILuft(){
            lesData();
        };
        void lesData(){
            cout << "Migrerer (y/n): ";
            string temp;
            getline(cin, temp);
            migrerer = (temp == "y");
        };
        void skrivData(){
            Dyr::skrivData();
            cout << "Migerer: " << (migrerer ? "ja" : "nei") << '\n';
        };
};

class Fugl : public DyrILuft{
    private:
        int vingespenn;
    public:
        Fugl(){
            lesData();
        };
        void lesData(){
            vingespenn = lesInt("Vingespenn", 0, 100);
        };
        void skrivData(){
            cout << "Fugl:\n";
            DyrILuft::skrivData();
            cout << "Vingespenn: " << vingespenn << '\n';
        };
};

class Insekt : public DyrILuft{
    private:
        int antallBen;
    public:
        Insekt(){
            lesData();
        };
        void lesData(){
            antallBen = lesInt("Antall ben", 0, 100);
        };
        void skrivData(){
            cout << "Insekt:\n";
            DyrILuft::skrivData();
            cout << "AntallBen: " << antallBen << '\n';
        };
};

int main(){
    skrivMeny();
    char kommando = lesChar("Skriv en kommando");

    while (kommando!='Q'){
        switch (kommando){
        case 'F':{
            string navn;
            cout << "Navn: ";
            getline(cin, navn);
            if (navn.size() == 0){
                Fisk* fisk = new Fisk;
                fisk->skrivData();
                delete fisk;
            }
            else{
                Fisk* fisk = new Fisk(navn);
                fisk->skrivData();
                delete fisk;
            }
            break;
        }
        case 'I':{
            Insekt* insekt = new Insekt;
            insekt->skrivData();
            delete insekt;
            break;}
        case 'S':{
            Skalldyr* skalldyr = new Skalldyr;
            skalldyr->skrivData();
            delete skalldyr;
            break;}
        case 'U':{
            Fugl* fugl = new Fugl;
            fugl->skrivData();
            break;}
        default:{
            skrivMeny();
            break;}
        }
        kommando = lesChar("Skriv en kommando");
    }
}

void skrivMeny(){
    cout << "\tF: Fisk\n\
             \tI: Insekt\n\
             \tS: Skalldyr\n\
             \tU: Fugl\n\
             \tQ: Avslutt\n";
}