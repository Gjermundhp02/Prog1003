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

void nyRestaurant(){
    gRestauranter.push_back(new Restaurant);
    restaurantLesData(*gRestauranter.back());
}

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

void skrivAlleRestauranter(){
    for(Restaurant* res : gRestauranter){
        restaurantSkrivData(res);
    }
}

void restaurantSkrivData(const Restaurant* restaurant){
    cout << "\tNavn: " << restaurant->navn << "\n"
         << "\tAdressse: " << restaurant->adresse << "\n"
         << "\tType: " << restaurant->type << "\n"
         << "\tOmtale: " << restaurant->omtale << "\n"
         << "\tTerningkast: " << restaurant->terningkast << "\n\n";
}

void skrivMeny(){
    cout << "Her kan du legge til og andmelde restauranter du har vert på. \n"
            "Komandoer:\n"
            "N - Legg til en ny restaurant\n"
            "S - Skriv ut alle restaurantene\n"
            "Q - Avslutt programmet\n\n";
}

void slettAlt(){
    for(Restaurant* &res : gRestauranter){
        delete res;
    }
    gRestauranter.clear();
}