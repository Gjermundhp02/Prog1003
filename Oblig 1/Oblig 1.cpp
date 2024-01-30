#include <string>
#include <vector>
#include <LesData2.h>
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
    cout << "Hva heter resturanten: ";
    getline(cin, restaurant.navn);
    cout << "\nHva er adressen: ";
    getline(cin, restaurant.adresse);
    cout << "\nHva er typen: ";
    getline(cin, restaurant.type);
    cout << "\nHar du en omtale: ";
    getline(cin, restaurant.omtale);
    restaurant.terningkast = lesInt("\nHva er terningkastet", 1, 6);
    cout << "\n\n";
}

void slettAlt(){
    for(Restaurant* &res : gRestauranter){
        delete res;
        res = nullptr;
    }
}