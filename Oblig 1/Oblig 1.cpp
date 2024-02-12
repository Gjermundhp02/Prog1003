 /**
  *  Program som holder oversikt over besøkte resturanter og omtalelser
  * 
  *   @file     Oblig 1.CPP      (basert noe på Program 7-9 og 7-10 i læreboka)
  *   @author   Gjermund Pedersen
  */
#include <string>
#include <vector>
#include "../LesData2.h"
using namespace std;

struct Restaurant {
    string navn,
    adresse, // Gateadresse i en og samme by
    type, // Indisk, japansk, thai, italiensk, gresk, ....
    omtale; // Lengre evaluering/bekrivelse/vurdering
    int terningkast; // Verdien 1 - 6
};

vector <Restaurant*> gRestauranter;

void nyRestaurant();
void restaurantLesData(Restaurant & restaurant);
void restaurantSkrivData(const Restaurant* restaurant);
void skrivAlleRestauranter();
void skrivMeny();
void slettAlt();

int main(){
    skrivMeny();
    char kommando = lesChar("Skriv en kommando");

    while (kommando!='Q'){
        switch (kommando){
        case 'N':
            nyRestaurant();
            break;
        case 'S':
            skrivAlleRestauranter();
            break;
        default:
            skrivMeny();
            break;
        }
        kommando = lesChar("Skriv en kommando");
    }
    slettAlt();
}

/**
 * @brief Legger inn en ny restaurant og omtale
*/
void nyRestaurant(){
    gRestauranter.push_back(new Restaurant);
    restaurantLesData(*gRestauranter.back());
}

/**
 * @brief Leser inn dataen om restauranten
 * 
 * @param restaurant - Restauranten som dataen skal leses inn i
*/
void restaurantLesData(Restaurant & restaurant){
    cout << "\tHva heter resturanten: ";
    getline(cin, restaurant.navn);
    cout << "\tHva er adressen: ";
    getline(cin, restaurant.adresse);
    cout << "\tHva er typen: ";
    getline(cin, restaurant.type);
    cout << "\tHar du en omtale: ";
    getline(cin, restaurant.omtale);
    restaurant.terningkast = lesInt("Hva er terningkastet", 1, 6);
    cout << "\n";
}

/**
 * @brief Skriver ut alle de lagrede restaurantene
*/
void skrivAlleRestauranter(){
    for(Restaurant* res : gRestauranter){
        restaurantSkrivData(res);
    }
}

/**
 * @brief Skriver ut dataen til den medsendte restauranten
 * 
 * @param restaurant - Restauranten som skal skal skrives ut
*/
void restaurantSkrivData(const Restaurant* restaurant){
    cout << "\tNavn: " << setw(20) << restaurant->navn << "\n"
         << "\tAdressse: " << setw(16) << restaurant->adresse << "\n"
         << "\tType: " << setw(20) << restaurant->type << "\n"
         << "\tOmtale: " << setw(18) << restaurant->omtale << "\n"
         << "\tTerningkast: " << setw(13) << restaurant->terningkast << "\n\n";
}

/**
 * @brief Skriver ut menyen med kommandoene
*/
void skrivMeny(){
    cout << "Her kan du legge til og andmelde restauranter du har vert på. \n"
            "Komandoer:\n"
            "N - Legg til en ny restaurant\n"
            "S - Skriv ut alle restaurantene\n"
            "Q - Avslutt programmet\n\n";
}

/**
 * @brief Sletter alle de lagrede dataene
*/
void slettAlt(){
    for(Restaurant* &res : gRestauranter){
        delete res;
    }
    gRestauranter.clear();
}