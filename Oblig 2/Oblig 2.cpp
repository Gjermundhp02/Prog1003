/**
 * Et program som oppretter objektene for ulike typer dyr og leser og 
 * skriver ut dataene til disse.
 * 
 * @file Oblig 2.cpp
 * @author your name (you@domain.com) 
 */

#include <string>
#include <iostream>
#include "../LesData2.h"
using namespace std;

void skrivMeny();

/**
 * Dyr (med navn - ABSTRAKT baseklasse for 'DyrIVann' og 'DyrILuft')
 */
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
            cout << "\tNavn: ";
            getline(cin, navn);
        };
        void skrivData(){
            cout << "\tNavn: " << navn << '\n';
        };
};

/**
 * Dyrene i vann (med vekt - ABSTRAKT klasse for 'Fisk' og 'Skalldyr')
 */
class DyrIVann : public Dyr{
    private:
        int vekt;
    public:
        DyrIVann(){
            lesData();
        };
        DyrIVann(string navn) : Dyr(navn){
            lesData();
        };
        void lesData(){
            cout << "\tVekt: ";
            vekt = lesInt("Vekt", 0, 1000);
        };
        void skrivData(){
            Dyr::skrivData();
            cout << "\tVekt: " << vekt << '\n';
        };
};

/**
 * Fisk (med farge)
 * 
 */
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
            cout << "\tFarge: ";
            getline(cin, farge);
        };
        void skrivData(){
            cout << "Fisk:\n";
            DyrIVann::skrivData();
            cout << "\tFarge: " << farge << '\n';
        };
};

/**
 * Skalldyr (med område du finner den)
 */
class Skalldyr : public DyrIVann{
    private:
        string omraade;
    public:
        Skalldyr(){
            lesData();
        };
        void lesData(){
            cout << "\tOmråde den finnes: ";
            getline(cin, omraade);
        };
        void skrivData(){
            cout << "Skalldyr:\n";
            DyrIVann::skrivData();
            cout << "\tOmråde den finnes: " << omraade << '\n';
        };
};

/**
 * Dyr i luft (med migrerer - ABSTRAKT klasse for 'Fugl' og 'Insekt')
 */
class DyrILuft : public Dyr{
    private:
        bool migrerer;
    public:
        DyrILuft(){
            lesData();
        };
        void lesData(){
            char temp;
            temp = lesChar("\tMigrerer (y/n)");
            migrerer = (temp == 'Y');
        };
        void skrivData(){
            Dyr::skrivData();
            cout << "\tMigerer: " << (migrerer ? "ja" : "nei") << '\n';
        };
};

/**
 * Fugl (med vingespenn)
 */
class Fugl : public DyrILuft{
    private:
        int vingespenn;
    public:
        Fugl(){
            lesData();
        };
        void lesData(){
            vingespenn = lesInt("\tVingespenn", 0, 100);
        };
        void skrivData(){
            cout << "Fugl:\n";
            DyrILuft::skrivData();
            cout << "\tVingespenn: " << vingespenn << '\n';
        };
};

/**
 * Insekt (med antall ben)
 */
class Insekt : public DyrILuft{
    private:
        int antallBen;
    public:
        Insekt(){
            lesData();
        };
        void lesData(){
            antallBen = lesInt("\tAntall ben", 0, 100);
        };
        void skrivData(){
            cout << "Insekt:\n";
            DyrILuft::skrivData();
            cout << "\tAntallBen: " << antallBen << '\n';
        };
};

/**
 * Hovedprogrammet: 
 */
int main(){
    skrivMeny();
    char kommando = lesChar("Skriv en kommando");

    while (kommando!='Q'){
        switch (kommando){
        case 'F':{
            string navn;
            cout << "\tNavn: ";
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
            break;
        }
        case 'S':{
            Skalldyr* skalldyr = new Skalldyr;
            skalldyr->skrivData();
            delete skalldyr;
            break;
        }
        case 'U':{
            Fugl* fugl = new Fugl;
            fugl->skrivData();
            break;
        }
        default:{
            skrivMeny();
            break;
        }}
        kommando = lesChar("Skriv en kommando");
    }
}

/**
 * Sriver ut menyen
 */
void skrivMeny(){
    cout << "\tF: Fisk\n"
         << "\tI: Insekt\n"
         << "\tS: Skalldyr\n"
         << "\tU: Fugl\n"
         << "\tQ: Avslutt\n";
}