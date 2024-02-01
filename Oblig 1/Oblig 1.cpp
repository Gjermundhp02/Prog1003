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
 * Lager en ny restaurant
 */
void nyRestaurant(){
    gRestauranter.push_back(new Restaurant);
    restaurantLesData(*gRestauranter.back());
}

/**
 * Ber brukeren om dataen for en restaurant og lagrer det
 * 
 * @param restaurant - Restauranen som skal fylles inn info for
 */
void restaurantLesData(Restaurant & restaurant){
    cout << "\tHva heter resturanten: ";
    getline(cin, restaurant.navn);
    cout << "\tHva er adressen:       ";
    getline(cin, restaurant.adresse);
    cout << "\tHva er typen:          ";
    getline(cin, restaurant.type);
    cout << "\tHar du en omtale:      ";
    getline(cin, restaurant.omtale);
    restaurant.terningkast = lesInt("Hva er terningkastet", 1, 6);
    cout << "\n";
}

/**
 * Skriver ut alle de lagrede restaurantene
 */
void skrivAlleRestauranter(){
    for(Restaurant* res : gRestauranter){
        restaurantSkrivData(res);
    }
}

/**
 * Skriver ut dataen til den medsendte restauranten
 * 
 * @param restaurant 
 */
void restaurantSkrivData(const Restaurant* restaurant){
    cout << "\tNavn:        " << restaurant->navn << "\n"
         << "\tAdressse:    " << restaurant->adresse << "\n"
         << "\tType:        " << restaurant->type << "\n"
         << "\tOmtale:      " << restaurant->omtale << "\n"
         << "\tTerningkast: " << restaurant->terningkast << "\n\n";
}

/**
 * Skriver ut menyen med kommandoene
 */
void skrivMeny(){
    cout << "Her kan du legge til og andmelde restauranter du har vert på. \n"
            "\tKomandoer:\n"
            "\tN - Legg til en ny restaurant\n"
            "\tS - Skriv ut alle restaurantene\n"
            "\tQ - Avslutt programmet\n\n";
}


/**
 * Sletter alle resurentene
 */
void slettAlt(){
    for(Restaurant* &res : gRestauranter){
        delete res;
    }
    gRestauranter.clear();
}