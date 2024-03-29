/** 
 *   Skjelett for obligatorisk oppgave nr 3 i PROG1003 - OOP.
 *
 *   Programmet inneholder en oversikt over studenter og ansatt p� en skole.
 *   Disse er identifisert via sitt UNIKE student-/ansattnummer,
 *   og alle ligger lagret i EN <map>. Brukeren/programmet kan:
 *       - se ALLE personene som er lagret i datastrukturen (map'en)
 *       - legge inn en ny student/ansatt
 *       - endre data om en gitt student/ansatt
 *       - HELE datastrukturen leses fra/skrives til fil
 *
 *   @file    oblig3.cpp
 *   @author  Gjermund H Pedersen
 */


#include <iostream>                //  cout, cin
#include <fstream>                 //  ifstream, ofstream
#include <string>
#include <map>
#include <algorithm>
#include "../LesData2.h"              //  Verkt�ykasse for lesing av diverse data
using namespace std;


/**
 *  Person (med navn).
 */
class Person {
  private:
      string navn;
  public:
      Person()  {  navn = "";  }
      Person(ifstream & inn);
      virtual void endreData() = 0;
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Student (med studieprogram/klasse og antall studiepoeng).
 */
class Student : public Person {
  private:
      string studieprogram;
      float  stp;
  public:
      Student()  {  studieprogram = "";  stp = 0.0F;  }
      Student(ifstream & inn);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


/**
 *  Ansatt (med rom-/kontornummer og �rsl�nn).
 */
class Ansatt : public Person {
  private:
      string rom;
      int    lonn;
  public:
      Ansatt()  {  rom = "";  lonn = 0;  }
      Ansatt(ifstream & inn);
      virtual void endreData();
      virtual void lesData();
      virtual void skrivData() const;
      virtual void skrivTilFil(ofstream & ut) const;
};


void endreEnPerson();
void lesFraFil();
void nyPerson();
void skrivAllePersoner();
void skrivMeny();
void skrivTilFil();


map <int, Person*> gPersoner;      ///<  Datastrukturen med alle personene.


/**
 *  Hovedprogrammet:
 */
int main(void)  {
    char kommando;

    lesFraFil();

    skrivMeny();
    kommando = lesChar("Kommando");

    while (kommando != 'Q') {
        switch (kommando) {
          case 'N':  nyPerson();               break;
          case 'A':  skrivAllePersoner();      break;
          case 'E':  endreEnPerson();          break;
          default:   skrivMeny();              break;
        }
        kommando = lesChar("Kommando");
    }

    skrivTilFil();

   return 0;
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV KLASSE-FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Leser navnet fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Person::Person(ifstream & inn) {
    getline(inn, navn);
}


/**
 *  Leser navnet fra brukeren/tastaturet.
 */
void Person::lesData() {
    cout << "Navn: ";
    getline(cin, navn);
}


/**
 *  Skriver ut navnet til/p� skjermen. 
 */
void Person::skrivData() const {
    cout << "Navn: " << navn << '\n';
}


/**
 *  Skriver ut navnet til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 */
void Person::skrivTilFil(ofstream & ut) const {
    ut << navn << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Leser studiepoeng og studieprogram/klasse fra fil.
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Student::Student(ifstream & inn) : Person(inn) {
    inn >> stp;
    inn.ignore();
    getline(inn, studieprogram);
}


/**
 *  Tilbyr brukren � endre p� alle egne data.
 *
 *  @see  skrivData()
 */
void Student::endreData() {
    char medlem = lesChar("Hva vil du endre? (S)tudieprogram, (P)oeng");
    switch (medlem) {
        case 'S':
            cout << "Studieprogram/klasse: ";
            getline(cin, studieprogram);
            break;
        case 'P':
            stp = lesFloat("Studiepoeng", 0, 100);
            break;
    }
    skrivData();
}


/**
 *  Leser baseklassens data, studieproram/klasse og studiepoeng fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Student::lesData() {
    Person::lesData();
    cout << "Studieprogram/klasse: ";
    getline(cin, studieprogram);
    stp = lesFloat("Studiepoeng", 0, 100);
}


/**
 *  Skriver baseklassens data, studieproram/klasse og studiepoeng til skjerm.
 *
 *  @see  Person::skrivData()
 */
void Student::skrivData() const {
    Person::skrivData();
    cout << "Studieprogram/klasse: " << studieprogram << '\n';
    cout << "Studiepoeng: " << stp << "\n\n";
}


/**
 *  Skriver 'S', baseklassens data, studiepoeng og studieprogram til fil.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Student::skrivTilFil(ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << stp << ' ' << studieprogram << '\n';
}


// ---------------------------------------------------------------------------

/**
 *  Leser �rsl�nn og rom/kontor fra fil. 
 *
 *  @param   inn  - Filobjektet egne data leses inn fra
 */
Ansatt::Ansatt(ifstream & inn) : Person(inn) {
    inn >> lonn;
    inn.ignore();
    getline(inn, rom);
}


/**
 *  Tilbyr brukren � endre p� alle egne data.
 *
 *  @see  skrivData()
 */
void Ansatt::endreData() {
    char medlem = lesChar("Hva vil du endre? (R)om, (L)ønn");
    switch (medlem) {
        case 'R':
            cout << "Rom/kontor: ";
            getline(cin, rom);
            break;
        case 'L':
            lonn = lesInt("Lønn", 0, 1000000);
            break;
    }
    skrivData();
}


/**
 *  Leser baseklassens data, rom/kontor og �rsl�nn fra brukeren.
 *
 *  @see   Person::lesData()
 */
void Ansatt::lesData() {
    Person::lesData();
    cout << "Rom/kontor: ";
    getline(cin, rom);
    lonn = lesInt("Lønn", 0, 1000000);
}


/**
 *  Skriver baseklassens data, rom/kontor og �rsl�nn til/p� skjermen.
 *
 *  @see  Person::skrivData()
 */
void Ansatt::skrivData() const {
    Person::skrivData();
    cout << "Rom/kontor: " << rom << '\n';
    cout << "Årslønn: " << lonn << "\n\n";
}


/**
 *  Skriver 'A', baseklassens data, �rsl�nn og rom/kontor.
 *
 *  @param   ut  - Filobjektet egne data skrives ut til
 *  @see     Person::skrivTilTil(...)
 */
void Ansatt::skrivTilFil(ofstream & ut) const {
    Person::skrivTilFil(ut);
    ut << lonn << ' ' << rom << '\n';
}


// ---------------------------------------------------------------------------
//                       DEFINISJON AV ANDRE FUNKSJONER:
// ---------------------------------------------------------------------------

/**
 *  Lar brukeren (om mulig) endre dataene for et avledet objekt (subklasse).
 *
 *  @see   virtual Person::endreData()
 */
void endreEnPerson() {
    int svar;
    while (true){
        svar = lesInt("Hvem sin data vil du endre", 1, 100000);
        if (gPersoner.find(svar) != gPersoner.end()){
            break; // Looper til brukeren skriver inn et gyldig id
        }
        cout << "Fant ikke personen\n";
    }
    gPersoner.find(svar)->second->endreData();
}


/**
 *  Leser ALLE personer inn fra fil, og legger de inn i 'gPersoner'.
 */
void lesFraFil() {
    ifstream innfil = ifstream("oblig3.dta");

    if (innfil){
        int id;
        innfil >> id;
        while (!innfil.eof()){
            char type;
            innfil >> type;
            innfil.ignore(); // Ignorer mellomrom
            if (type == 'S'){
                gPersoner.insert({id, new Student(innfil)});
            } else {
                gPersoner.insert({id, new Ansatt(innfil)});
            }
            innfil >> id;
        }
    }
    else{
        cout << "Fant ikke filen\n";
    }
    innfil.close();
}


/**
 *  Legger inn (om mulig) en ny person.
 *
 *  @see   virtual Person::lesData()
 */
void nyPerson() {
    char svar = lesChar("S - Student, A - Ansatt");
    Person* person;
    int id;

    if (svar == 'S') {
        do{
            id = lesInt("IdNr", 1001, 100000);
            // Sjekker om brukeren allerede finnes
        }while (gPersoner.find(id) != gPersoner.end());
        gPersoner.insert({id, new Student}); 
        gPersoner.at(id)->lesData(); // Get the data from the user
    } 
    else if (svar == 'A') {
        do{
            id = lesInt("IdNr", 1, 1000);
        }while (gPersoner.find(id) != gPersoner.end());
        gPersoner.insert({id, new Ansatt});
        gPersoner.at(id)->lesData();
    }
    else {
        cout << "Ugyldig valg\n";
    }
}


/**
 *  Skriver alle dataene om alle personene ut p� skjermen.
 *
 *  @see   virtual Person::skrivData()
 */
void skrivAllePersoner() {
    for (const auto & val : gPersoner){
        cout << "IdNr: " << val.first << ":\n";
        val.second->skrivData();
    }
}


/**
 *  Skriver programmets menyvalg/muligheter p� skjermen.
 */
void skrivMeny() {
    cout << "\nF�lgende kommandoer er tilgjengelig:\n"
         << "\tN - Ny person (student eller ansatt)\n"
         << "\tA - skriv Alle personer\n"
         << "\tE - Endre EN gitt person\n"
         << "\tQ - Quit / avslutt\n\n";
}


/**
 *  Skriver hele datastrukturen til fil.
 *
 *  @see   virtual Person::skrivTilFil(...)
 */
void skrivTilFil() {
    ofstream utfil = ofstream("oblig3.dta");
    for (const auto & val : gPersoner){
        // Skriv ut id og om det er en ansatt eller student
        utfil << val.first << ' ' << (val.first<1001 ? 'A' : 'S') << ' ';
        val.second->skrivTilFil(utfil);
    }
    utfil.close();
}