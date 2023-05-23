// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
// This is free software that is intended for research and educational purposes only.
#include "config.h"

void DEFAULT() {
    cout<< "  ~~~~ ____   |~~~~~~~~~~~~~~~~~~~~| \n"
        << " Y_,___|[]|   | SCAM TRAIN POOGERS | \n"
        << "{|_|_|_|PU|_,_|____________________| \n"
        << "//oo---OO=OO   OOO     OOO      OOO  \n";
}
void MENU() {
    cout << "\n Vyber predmet:\n"
        << " 0- ukoncenie programu\n"
        << " 1- RAL\n"
        << " 2- ZKRY1\n"
        << " 3- ZKRY2 + RT2020\n"
        << " 4- NKS\n";
}
void MENU_RAL() {
    cout << "\n RAL funkcie\n"
        << "  0- navrat do menu.\n"
        << "  1- ord_Zp\n"                  //video 1 , https://primefan.tripod.com/Phi500.html values phi func
        << "  2- INV_Zp, 5- INV_Zp[x]\n"    //video 2,4
        << "  3- is poly A irred mod M\n"   //video 3
        << "  4- factor poly A mod M\n"     //video 6,7,8,9
        << "  6- CRT_Zp, 7- CRT_Zp[x]\n"    //video 10,11
        << "  8- DFT_Zp,\n"                 //video 16
        << "  9- kvadraticke_sito\n"        //video 22
        << " 10- berlekamp\n"               //video 18
        << " 11- sqrt\n";                   //video 19,20
}
void MENU_ZKRY1() {
    cout << "\n ZKRY zapocet1 funkcie\n"
        << " 0- navrat do menu.\n"
        << " 1- pre vsetky X={1..p-1} vypis vsetky A pre ktore plati ze X^2 = A mod P (mnozina kvadratickych zvyskov modulo P)\n"
        << " 2- Jakobi bez postupu, iba rovno vysledok (zisti ci x^2 = a mod p ma riesenie)\n"
        << " 3- vypis vsetky x pre x^2 = a mod p\n"
        << " 4- Jakobi s postupom pre a mod p\n"
        << " 5- list indeponentov modulo p\n"
        << " 6- my CRT test\n"
        << " 7- zjednodus vyraz X^n modulo p\n";
        //<< " 8- Ax + b = c modulo p\n";
}
void MENU_ZKRY2() {
    cout << "\n ZKRY zapocet2 funkcie\n"
        << " 0- navrat do menu.\n"
        << " 1- sifrovanie   (ecb, cbc, cfb, ofb, ctr)\n"
        << " 2- desifrovanie (ecb, cbc, cfb, ofb, ctr)\n"
        << " ZKRY RT2020 funkcie\n"
        << " 3- RSA\n"
        << " 4- El gamal\n"
        << " 5- epilepticke krivky\n"
        << " 6- Gordon Helman Bach\n"
        << " Ostatne funkcie\n"
        << " 7- RSA sifrovanie\n"
        << " 8- RSA desifrovanie\n";
}
void MENU_NKS() {
    cout << "\n NKS funkcie\n"
        << " 0- navrat do menu.\n"
        << " 1- Sbox\n"
        << " 2- AES\n";
}
void WRONG_INPUT() {
    cout << "\n!!!NEPLATNY VSTUP!!!\n";
}
void KONIEC_VYPOCTU() {
    cout << "########## Koniec vypoctu ##########\n";
}

int main() {
    DEFAULT();
    //list_of_cyklo_poly();

    while (1) {
        MENU();
        int predmet;
        cin >> predmet;
        cin.clear(0);

        if (predmet < 0 || predmet > 4) {
            WRONG_INPUT();
            continue;
        }
        else if (predmet == 0) return 0;
        else if (predmet == 1) MENU_RAL();
        else if (predmet == 2) MENU_ZKRY1();
        else if (predmet == 3) MENU_ZKRY2();
        else if (predmet == 4) MENU_NKS();

        while(1){
            int funkcia;
            cin >> funkcia;
            cin.clear(0);
            if ( (funkcia < 0) || (predmet==1 && funkcia>11) || (predmet==2 && funkcia>8) || (predmet==3 && funkcia>8) || (predmet == 4 && funkcia > 2)) {
                WRONG_INPUT();
                continue;
            }
            else if (funkcia == 0) break;
            else if (predmet == 1) RAL  [funkcia - 1]();
            else if (predmet == 2) ZKRY1[funkcia - 1]();
            else if (predmet == 3) ZKRY2[funkcia - 1]();
            else if (predmet == 4) NKS  [funkcia - 1]();

            KONIEC_VYPOCTU();
        }

        printf("\033c");//printf("\033[H\033[J");
    }
}